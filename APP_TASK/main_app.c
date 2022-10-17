#include "main_app.h"
#include   "eth_ring_com.h"
#include "ether_hal.h"
#include  "stdio.h"
#include  "string.h"
#include "key_hal.h"
#include  "alarm_led.h"
extern uint8_t   dev_buffer[4]; //设备号
extern uint8_t product_key[30];//一定要初始化，要不写读会发生问题
extern ETH_ring_TYPE eth_ring;
 uint8_t eth_ack_flag=0;
 uint8_t runing_flag=0;
  uint32_t runing_count=0;
//typedef enum
//{
//  GPIO_PIN_RESET = 0U,
//  GPIO_PIN_SET
//} GPIO_PinState;
typedef enum{
	 Access_request=0U,
	 Access_request_ack,
	 State_net,
	 State_net_ack,
	 Equipment_report,
	 Equipment_report_ack
}net_in_flow;

//初始化设备IP地址 

void init_dev_eth()
{
	
	    if(ether_st.RX_flag==1)
			{
	         if(ether_st.RX_pData[2]==0x03)
									 {										
										switch(ether_st.RX_pData[3])
												 {												
																 //设置本机IP地址
														case 0x03 :
														       	printf("设置本地IP地址\r\n");
															     memset(local_eth_ip, 0, sizeof(local_eth_ip));	
																	  for(uint8_t i=0;i<4;i++)
																	 {
																		  
																		 local_eth_ip[i]= ether_st.RX_pData[4+i];
																	 }
															printf("本地ip:%d.%d.%d.%d\r\n",local_eth_ip[0],local_eth_ip[1],local_eth_ip[2],local_eth_ip[3]);		 
//																	 u8_ip_to_u32_ip(local_eth_ip,u32_local_eth_ip);
//                             STMFLASH_Write (  0x800f428, (uint32_t* )u32_local_eth_ip, 1)	; //写本机地址																	 
//																      data_wifi_pa=1;
//				                      wifi_connect_pin_pack(dev_num,0x02,0x03,&data_wifi_pa,1,product_key);
//												 send_string_to_eth(wifiTXbuffer,wifi_connect_pin_pack(dev_num,0x02,0x03,&data_wifi_pa,1,product_key));			            
                            	 send_string_to_eth(ether_st.RX_pData,ether_st.RX_Size);																 
														break;
																	 //设置远程IP地址
													case 0x04 :
																printf("设置远程IP地址\r\n");
															     memset(Remote_eth_ip, 0, sizeof(Remote_eth_ip));	
																	  for(uint8_t i=0;i<4;i++)
																	 {
																		  
																		 Remote_eth_ip[i]= ether_st.RX_pData[4+i];
																	 }
																	 	printf("远程ip:%d.%d.%d.%d\r\n",Remote_eth_ip[0],Remote_eth_ip[1],Remote_eth_ip[2],Remote_eth_ip[3]);		
//																	 u8_ip_to_u32_ip(Remote_eth_ip,u32_Remote_eth_ip);
//                             STMFLASH_Write (  0x800f448, (uint32_t* )u32_Remote_eth_ip, 1)	; //写远程IP地址																	 
//                                        		      data_wifi_pa=1;
//				                      wifi_connect_pin_pack(dev_num,0x02,0x04,&data_wifi_pa,1,product_key);
//												 send_string_to_eth(wifiTXbuffer,wifi_connect_pin_pack(dev_num,0x02,0x04,&data_wifi_pa,1,product_key));		
																	 	 send_string_to_eth(ether_st.RX_pData,ether_st.RX_Size);
														break;
																	 //设置远程端口
					                	case 0x05 :
																printf("设置远程IP端口\r\n");
															     memset(Remote_eth_port, 0, sizeof(Remote_eth_port));	
																	  for(uint8_t i=0;i<4;i++)
																	 {
																		  
																		 Remote_eth_port[i]= ether_st.RX_pData[4+i];
																	 }
																printf("设置远程IP端口:%d.%d.%d.%d\r\n",Remote_eth_port[0],Remote_eth_port[1],Remote_eth_port[2],Remote_eth_port[3]);	
//																	 u8_ip_to_u32_ip(Remote_eth_port,u32_Remote_eth_port);
//                             STMFLASH_Write (  0x800f468, (uint32_t* )u32_Remote_eth_port, 1)	; //写远程端口地址																	 
//														                       	chuchang_flag=3; //设置成功
//														         STMFLASH_Write (  0x800f510, (uint32_t* )&chuchang_flag, 1)	;
//																	 		      data_wifi_pa=1;
//				                      wifi_connect_pin_pack(dev_num,0x02,0x05,&data_wifi_pa,1,product_key);
//												 send_string_to_eth(wifiTXbuffer,wifi_connect_pin_pack(dev_num,0x02,0x05,&data_wifi_pa,1,product_key));		
																	 send_string_to_eth(ether_st.RX_pData,ether_st.RX_Size);
																	        HAL_Delay(100);
														             HAL_NVIC_SystemReset(); //复位重启
																	 																	 
																	 //设置产品密钥
																break;	 
																	  case 0x06 :
															    	printf("设置Productkey\r\n");
															     memset(product_key, 0, sizeof(product_key));	
																	  for(uint8_t i=0;i<8;i++)
																	 {
																		  
																		 product_key[i]= ether_st.RX_pData[4+i];
																		 printf("product_key[%d]=%d\r\n",i,product_key[i]);
						         						    }
																	 
//																	 u8_ip_to_u32_ip(product_key,u32_product_key);
//																	 u8_ip_to_u32_ip_more(product_key,u32_product_key,2);
//                                  STMFLASH_Write ( 0x800f500, (uint32_t* )u32_product_key, 2)	; //写序列号		
//   																STMFLASH_Read (  0x800f500, (uint32_t* )u32_product_key, 2)	; //读
//                               	u32_ip_to_u8_ip(product_key,u32_product_key,2);
																		
//                for(uint8_t i=0;i<8;i++)
//         	{
//		           printf("%c",product_key[i]);
//		
//	          }			
//																	 		      data_wifi_pa=1;
//				                      wifi_connect_pin_pack(dev_num,0x02,0x06,&data_wifi_pa,1,product_key);
//												 send_string_to_eth(wifiTXbuffer,wifi_connect_pin_pack(dev_num,0x02,0x06,&data_wifi_pa,1,product_key));		
				                          send_string_to_eth(ether_st.RX_pData,ether_st.RX_Size);    
														break;
															 
																							
												}
								
											
								}		
									   memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));	
									       ether_st.RX_flag=0;
							}
}

//入网请求	
//入网请求	
uint8_t  eth_ring_net_in()
{
	    uint8_t  net_ta=0;
   static net_in_flow  net_in=Access_request;
	 switch(net_in)
	 {		 
		   case Access_request : 
				              eth_ring.dev_pData_len=1;
			                eth_ring.dev_pData[0]=0x00;
				 eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,Access_request_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key);
	    send_string_to_eth(eth_ring.TX_pData,eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,Access_request_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key));
			                          eth_ack_flag=1;
			                          ether_st.RX_flag=0;
			                          ether_st.RX_Size=0;
			                      //  memset(ether_st.TX_pData, 0, sizeof(ether_st.TX_pData));	
			                        net_in=Access_request_ack;
				 break;		 
		 	 case Access_request_ack : 
				 //重发
				              if(eth_ack_flag==2)
						 {
							  net_in=Access_request;
							 
						 }  
               if(ether_st.RX_flag==1)
							 {

								 	 	for(uint16_t i=0;i<ether_st.RX_Size-20;i++)
									{
										
										ether_st.RX_pData[i]=ether_st.RX_pData[i+20];
											 printf("ether_st.RX_pData[%d]=%02x.",i,	ether_st.RX_pData[i]);
										
									}
//									send_string_to_eth(ether_st.RX_pData,ether_st.RX_Size);
								 //有线报警器的信息
								     if(ether_st.RX_pData[4]==device_type)
									   {
											 
										     switch(ether_st.RX_pData[5])
												 {												
													  case 0x01 :  
                                        
//				                      HAL_Delay(500);  //延迟播放音乐
																
														   dev_buffer[0]=ether_st.RX_pData[6]; 
													     dev_buffer[1]=ether_st.RX_pData[7];
														 	 printf("get dev id %02x-%02x\r\n", dev_buffer[0],dev_buffer[1]);
								                    eth_ack_flag=0;
																		net_in =State_net; break;
												}
											}
										 			 ether_st.RX_flag=0;
										
			                          ether_st.RX_Size=0;
											  memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));	
							  }
			 break;
		 	 case State_net :  
		                   eth_ring.dev_pData_len=1;
			                eth_ring.dev_pData[0]=0x01;
				 eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,State_net_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key);
	 send_string_to_eth(eth_ring.TX_pData,eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,State_net_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key));
			                         eth_ack_flag=1;
			                           ether_st.RX_flag=0;
			                          ether_st.RX_Size=0;
			                        net_in=State_net_ack;

			 break;
		 	 case State_net_ack :  
                       if(eth_ack_flag==2)
						 {
							  net_in=State_net;
							 
						 }  
               if(ether_st.RX_flag==1)
							 {
								  
								 	 	for(uint8_t i=0;i<ether_st.RX_Size-20;i++)
									{
										
										ether_st.RX_pData[i]=ether_st.RX_pData[i+20];
									}
								 //有线报警器的信息
								     if(ether_st.RX_pData[4]==device_type)
									   {
										     switch(ether_st.RX_pData[5])
												 {												
													  case State_net_function :  
                                     
																	 printf("get dev id\r\n");
														     
								                    eth_ack_flag=0;
																		net_in =Equipment_report;
														       break;
												}
											}
										 ether_st.RX_flag=0;
												  ether_st.RX_flag=0;
			                          ether_st.RX_Size=0;
											  memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));	
								
							   }

			 break;
		 	 case Equipment_report :
				               eth_ring.dev_pData_len=2;
			                 eth_ring.dev_pData[0]=dev_buffer[0];
			                 eth_ring.dev_pData[1]=dev_buffer[1];
				 eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,Equipment_report_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key);
	 send_string_to_eth(eth_ring.TX_pData,eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,Equipment_report_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key));
			                         eth_ack_flag=1;
			                           ether_st.RX_flag=0;
			                          ether_st.RX_Size=0;
			                        net_in=Equipment_report_ack;
				         
				 break;
		 	 case Equipment_report_ack : 
                      if(eth_ack_flag==2)
						 {
							  net_in=Equipment_report;
							 
						 }  
               if(ether_st.RX_flag==1)
							 {
								  
								 	 	for(uint8_t i=0;i<ether_st.RX_Size-20;i++)
									{
										
										ether_st.RX_pData[i]=ether_st.RX_pData[i+20];
									}
								 //有线报警器的信息
								     if(ether_st.RX_pData[4]==device_type)
									   {
										     switch(ether_st.RX_pData[5])
												 {												
													  case Equipment_report_function :   
                                     //版本号
															
														send_string_to_eth((uint8_t*)ETH_BAOJINGQI_VERSION,sizeof(ETH_BAOJINGQI_VERSION));
														           
								                    eth_ack_flag=0;
//																		net_in =Equipment_report;
														        net_ta=1;
													     	return  net_ta;
														       break;
												} 
											}
										 ether_st.RX_flag=0;
											
			                          ether_st.RX_Size=0;
											  memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));									
							   }
			 break;
		 
		 
		 default :    break;		  
	 }
	        return net_ta;
}

	
 uint8_t	rang_state=0;
   uint8_t ring_flag=0;
void run_system_task()
{
	
	
	
		if(get_key1()==0)
{
	  	
	   switch(rang_state)
	 {
		 case 0 :
			          printf("一键启动报警\r\n");					
		                  rang_state=1;
		                    ring_flag=1;
		                 break;
		 case 1 :    
			                      //写上声光报警代码
		                           led_on;
			                      eth_ring.dev_pData[0]=0x01;   
                            eth_ring.dev_pData_len=1;	 
			               		 eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,alarm_report_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key);
	               send_string_to_eth(eth_ring.TX_pData,eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,alarm_report_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key)); 
		                                     ether_st.RX_flag=0;
			                                  ether_st.RX_Size=0;
		                                   eth_ack_flag=1;//
		                                   rang_state=2;
		                   break;
		     //应答
		 case 2:   
                  if(eth_ack_flag==2)
						      {
							    rang_state=1;							 
						      }  
               if(ether_st.RX_flag==1)
							 {
								
								 	 	for(uint8_t i=0;i<ether_st.RX_Size-8;i++)
									{
										
										 ether_st.RX_pData[i]=ether_st.RX_pData[i+8];
											 printf("ether_st.RX_pData[%d]=%02x.",i,	ether_st.RX_pData[i]);
									}
									
								 //有线报警器的信息
								     if(ether_st.RX_pData[4]==device_type)
									   {
										     switch(ether_st.RX_pData[5])
												 {			
													 
													 //后台收到报警指令，取消重发
													  case 0x12 :  
                                        
				             					   eth_ack_flag=0; //	 										
//													       rang_state=0;//
														break;
														 
												}
											}
										 			 ether_st.RX_flag=0;
												      ether_st.RX_flag=0;
			                          ether_st.RX_Size=0;
											  memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));	
							  }
			 break;			 
			  
         	 
			 
					                  
	   			            	       		      
	 }
}
else
{
	       
	          if(ring_flag==1)
		        {
							                  led_off;
			                     eth_ring.dev_pData[0]=0x01;   
                            eth_ring.dev_pData_len=1;	 
			               		 eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,Manual_away_p_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key);
            	 send_string_to_eth(eth_ring.TX_pData,eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,Manual_away_p_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key));  
							                 ether_st.RX_flag=0;
			                          ether_st.RX_Size=0;
							              eth_ack_flag=1;//启动重发机制
			                      rang_state=0;
			                       ring_flag=2;
		       }
						if(ring_flag==2)
						{
							 if(eth_ack_flag==2)
						      {
							    ring_flag=1;							 
						      }  
							
							 if(ether_st.RX_flag==1)
							 {
								
								 	 	for(uint8_t i=0;i<ether_st.RX_Size-8;i++)
									{
										
										 ether_st.RX_pData[i]=ether_st.RX_pData[i+8];
											 printf("ether_st.RX_pData[%d]=%02x.",i,	ether_st.RX_pData[i]);
									}
									
								 //有线报警器的信息
								     if(ether_st.RX_pData[4]==device_type)
									   {
										     switch(ether_st.RX_pData[5])
												 {			
													 
													 //后台收到消警指令，取消重发
													  case 0x14 :  
                                        
				             					   eth_ack_flag=0; //	 										
                                 ring_flag=0;
														break;
														 
												}
											}
										 			 ether_st.RX_flag=0;
												   ether_st.RX_flag=0;
			                          ether_st.RX_Size=0;
											  memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));	
							  }
						}
//	   printf("ring close\r\n");
}
	
	
	//send xintiao  bao
  if( runing_flag==2)
	{
		                        eth_ring.dev_pData[0]=0x01;   
                            eth_ring.dev_pData_len=1;	 
			               		 eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,Equipment_run_state_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key);
	 send_string_to_eth(eth_ring.TX_pData,eth_ring_com_pack(eth_ring.TX_pData,dev_buffer,Equipment_run_state_function,eth_ring.dev_pData,eth_ring.dev_pData_len,product_key)); ;
		                    ether_st.RX_flag=0;
			                          ether_st.RX_Size=0;
		             runing_flag=1;
	}
	//接受后台消息
	if(ether_st.RX_flag==1)
	{
		ether_st.RX_flag=0;
		   
		printf("rec_xinxi\r\n");
	}
}