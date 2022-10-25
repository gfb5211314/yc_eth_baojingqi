#include "ether_hal.h"
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "usart.h"
#include "u_flash.h"
#define  eth_RST_L        HAL_GPIO_WritePin(eth_rst_GPIO_Port, eth_rst_Pin, GPIO_PIN_RESET);
#define  eth_RST_H        HAL_GPIO_WritePin(eth_rst_GPIO_Port, eth_rst_Pin, GPIO_PIN_SET);


ETH_TYPE  ether_st;

//uint8_t  local_eth_ip[40]="at+LANIp=192.168.1.90\r\n";
////uint8_t   local_eth_port[30]="at+NRPort0=6962\r\n";
//uint8_t  Remote_eth_ip[40]="at+NDomain0=192.168.1.203\r\n";
//uint8_t  Remote_eth_port[30]="at+NRPort0=6962\r\n";


//ģ������
void ETH_Rst ( void )
{
		 eth_RST_H;
	HAL_Delay(1000);
	 eth_RST_L;
	 HAL_Delay( 2000 ); 
	 eth_RST_H;
	HAL_Delay(2000);
	HAL_Delay(2000);
  HAL_Delay(2000);
}
//����1�ֽڵ�WIFIģ��
void send_byte_to_eth(uint8_t p)
{

    HAL_UART_Transmit(&eth_usart, (uint8_t*)&p,1, 0xffff);

}
//����һ���ַ���wifiģ��,���ܷ�������0
void eth_send_string(uint8_t *p) {

    while(*p!= '\0') {

        send_byte_to_eth(*p);
        p++;
    }
//	length=sizeof(data)/sizeof(data[0])
}

void send_string_to_eth(uint8_t *p,uint16_t plen)
{
	 HAL_UART_Transmit(&eth_usart, p,plen, 0xffffffff);
	
}
//ֻ��������AT����ͣ��ַ�Ϊ0��û������! �����������㶼����
uint8_t atk_eth_send_cmd(uint8_t *cmd,uint8_t *ack,uint32_t waittime)
{
	     uint8_t sucess_state=0;
	    static  uint8_t reset_count=0; 
	    static  uint8_t comumtate=0; 
	    static  uint32_t eth_wait_tim_sta=0; 
	    static  uint32_t eth_wait_tim_end=0; 
	   switch(comumtate)
		 {
			 //���뷢��״̬
			 case 0 : 
				            eth_send_string(cmd);
//		  __HAL_UART_ENABLE_IT(&eth_usart, UART_IT_IDLE);
		  HAL_UART_Receive_DMA(&eth_usart,(uint8_t *)ether_st.RX_pData, 50);//�����������
			                    comumtate=1; 
			                    eth_wait_tim_sta=HAL_GetTick();
			              printf("wait_tim_sta=%d\r\n",eth_wait_tim_sta);
//			                   HAL_Delay(1000);
			                  reset_count++;
			                    if(reset_count>10)
													{
													HAL_NVIC_SystemReset();

														
													}
			               break;
			 //����ack״̬
			 case 1 :  if(ether_st.RX_flag==1)
			         {
			                 
				           printf("ack:%s\r\n",(uint8_t*)ether_st.RX_pData);
				           if(strstr((const char*)ether_st.RX_pData,(const char*)ack))
			            {
										      reset_count=0;
								          ether_st.RX_flag=0;
								        	ether_st.RX_Size=0;
								           sucess_state=1;
								             comumtate=0;
                      memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));					        
				           }
									    ether_st.RX_flag=0;
								     ether_st.RX_Size=0;
                      memset(ether_st.RX_pData, 0, sizeof(ether_st.RX_pData));	
			         }
							 else
							 {
								         eth_wait_tim_end=HAL_GetTick();
//								       printf("wait_tim_end=%d\r\n",wait_tim_end);
								         if((eth_wait_tim_end-eth_wait_tim_sta)>waittime)
												 {
													 
													    comumtate=0;
													   
												 }								 
							 }
							 break;			 
		 }
              return sucess_state;
} 
/*****************************************************************
                       *����HAL*
******************************************************************/
//����DMA���տ����ж�
void  ETH_DMA_START()
{
	   __HAL_UART_ENABLE_IT(&eth_usart, UART_IT_IDLE);
   HAL_UART_Receive_DMA(&eth_usart,(uint8_t *)ether_st.RX_pData, 100);  //����������

}
//�������տ����ж�
void  ETH_UsartReceive_IDLE()
{
    uint32_t temp=0;
    if((__HAL_UART_GET_FLAG(&eth_usart,UART_FLAG_IDLE) != RESET))
    {
			  
        __HAL_UART_CLEAR_IDLEFLAG(&eth_usart);
        HAL_UART_DMAStop(&eth_usart);
        temp = eth_usart.hdmarx->Instance->CNDTR;//	
          ether_st.RX_Size = data_len - temp;
        ether_st.RX_flag=1;
       HAL_UART_Receive_DMA(&eth_usart,(uint8_t *)ether_st.RX_pData, data_len);
    }
}

//
void USART2_IRQHandler(void)
{
    /* USER CODE BEGIN USART3_IRQn 0 */
      ETH_UsartReceive_IDLE();

    /* USER CODE END USART3_IRQn 0 */
      HAL_UART_IRQHandler(&eth_usart);
    /* USER CODE BEGIN USART3_IRQn 1 */
	
    /* USER CODE END USART3_IRQn 1 */
}
//
void eth_at_open()
{
		HAL_GPIO_WritePin(eth_at_GPIO_Port, eth_at_Pin, GPIO_PIN_SET);
  	 HAL_Delay(1000);
	  HAL_GPIO_WritePin(eth_at_GPIO_Port, eth_at_Pin, GPIO_PIN_RESET);
	  HAL_Delay(1000);
		 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);

	  HAL_GPIO_WritePin(eth_at_GPIO_Port, eth_at_Pin, GPIO_PIN_SET);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);


	
}
//�ָ���������
void reset_ethdevinit()
{
    	HAL_GPIO_WritePin(eth_at_GPIO_Port, eth_at_Pin, GPIO_PIN_SET);
  	 HAL_Delay(1000);
	  HAL_GPIO_WritePin(eth_at_GPIO_Port, eth_at_Pin, GPIO_PIN_RESET);
	  HAL_Delay(1000);
		 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
		 HAL_Delay(1000);
	  HAL_GPIO_WritePin(eth_at_GPIO_Port, eth_at_Pin, GPIO_PIN_SET);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	 HAL_Delay(1000);
	
	
	
}

uint8_t  local_eth_ip[40]="at+WANIp=192.168.1.68\r\n";
uint8_t  local_eth_WANIpMask[30]="at+WANIpMask=255.255.255.0\r\n";
uint8_t  local_eth_WANIpM_gate[30]="at+SGw=192.168.1.250\r\n";
uint8_t  Remote_eth_ip[40]="at+NDomain0=192.168.3.87\r\n";
uint8_t  Remote_eth_port[30]="at+NRPort0=6962\r\n";
uint8_t eth_init()
{

	  uint8_t sucess_stetc=0;
	   static uint8_t wifi_state_num=0;
	   switch(wifi_state_num)
		  {
	
			                  
			  case 0 : 
				                if(atk_eth_send_cmd((uint8_t *)"at+Netmode=0\r\n",(uint8_t *)"at+RNetmode=1",5000)==1)  //����Ϊģʽ1
											  {
												  wifi_state_num=1;											 
											  }
			   break;
		
											 
			 	 case 1 :           printf("DHCP�������ر�\r\n");
					        if(atk_eth_send_cmd((uint8_t *)"at+Dhcpd=0\r\n",(uint8_t *)"at+RDhcpd",5000)==1)
											 {
						                wifi_state_num=2;											 
											 }
			   break; 
											 									 
			 	 case 2 :           printf("���þ�̬IP\r\n");
					          if(atk_eth_send_cmd((uint8_t *)"at+Dhcpc=0\r\n",(uint8_t *)"at+RDhcpc",5000)==1)
											 {
						           wifi_state_num=3;											 
											 }
			   break; 
		    case 3:        printf("���ñ���IP��ַ\r\n");
					 if(atk_eth_send_cmd((uint8_t *)local_eth_ip,(uint8_t *)"at+RWANIp",5000)==1)
											 {
							  wifi_state_num=4;											 
											 }
			   break; 
				case 4:        printf("���ñ���MASK��ַ\r\n");
					 if(atk_eth_send_cmd((uint8_t *)local_eth_WANIpMask,(uint8_t *)"at+RWANIpMask",5000)==1)
											 {
							  wifi_state_num=5;											 
											 }
			   break; 
											 
				 case 5:        printf("���ñ���gate��ַ\r\n");
					 if(atk_eth_send_cmd((uint8_t *)local_eth_WANIpM_gate,(uint8_t *)"at+RSGw",5000)==1)
											 {
							  wifi_state_num=6;											 
											 }
			   break; 
				 case 6 :  
		
				                    printf("����ģʽ\r\n");
				 if(atk_eth_send_cmd((uint8_t *)"at+NProType0=2\r\n",(uint8_t *)"at+RNProType0",5000)==1)  //ѡ��	tcp client
											 {
												  wifi_state_num=7;											 
											 }
			   break;    												 
			  case 7 :        printf("123\r\n");
						 if(atk_eth_send_cmd((uint8_t *)Remote_eth_ip,(uint8_t *)"at+RNDomain0",5000)==1)
											 {
							  wifi_state_num=8;											 
											 }
    		break; 
			  case 8 :    
						               printf("����IP��ַ\r\n");
						 if(atk_eth_send_cmd((uint8_t *)Remote_eth_port,(uint8_t *)"at+RNRPort0",5000)==1)
											 {
							     wifi_state_num=9;											 
											 }
			   break; 
			  	   case 9 :         if(atk_eth_send_cmd((uint8_t *)"at+NLPort0=8888\r\n",(uint8_t *)"at+RNLPort0",5000)==1)
											    {
							               wifi_state_num=10;											 
											    }
			   break; 
           case 10 :         if(atk_eth_send_cmd((uint8_t *)"at+Save=1\r\n",(uint8_t *)"at+RSave=1",5000)==1)
											    {
							               wifi_state_num=11;											 
											    }
			      break; 
				case 11 :         if(atk_eth_send_cmd((uint8_t *)"at+Apply=1\r\n",(uint8_t *)"at+RApply=1",5000)==1)
											    {
							               wifi_state_num=12;											 
											    }
			      break; 
		     case 12 :         atk_eth_send_cmd((uint8_t *)"at+Reboot=1\r\n",(uint8_t *)"at+Reboot",1000);
											    
							               wifi_state_num=13;		                              												
											       HAL_Delay(1000);
			      break; 									 
				 
			   	case 13 :        
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);	
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);	
                           HAL_Delay(1000);
                           HAL_Delay(1000);
                           HAL_Delay(1000);						 
								 			  	 wifi_state_num=14;				
            					
			     break; 
             case 14 : 			
				                    printf("suceess");
                          sucess_stetc=1;
                   break;						 
		 }
	     return  sucess_stetc;
}

extern uint8_t sn_code[12];
 uint8_t sn_codeq[12];
 uint32_t factory;
void process_usart_data()
{
	
	if(ether_st.RX_flag==1)
	{
		 if(ether_st.RX_Size>100)
		 {
			 ether_st.RX_flag=0;
			 ether_st.RX_Size=0;
		 }
		//send_string_to_eth(ether_st.RX_pData,ether_st.RX_Size);
		if(strncmp((char *)ether_st.RX_pData,"sn:",3)==0)
		{
			
			
			for(uint16_t i=0;i<12;i++)
			{
			  //printf("sn=%c",ether_st.RX_pData[i+3]) ; 
				sn_code[i]=ether_st.RX_pData[i+3];
			}		
        
    	 STMFLASH_Write(SN_ADDR_FLASH,   (uint32_t *)sn_code,3 );
	     Flash_Read_Word( SN_ADDR_FLASH, (uint32_t *)sn_code,3 ) ;
			
//			for(uint16_t i=0;i<12;i++)
//			{
//			  printf("sn=%c",sn_code[i]) ; 
//			
//			}	
			send_string_to_eth(sn_code,12);
		}
			else	if(strncmp((char *)ether_st.RX_pData, "exit factory",4)==0)
		{
			
           factory=1;			
			STMFLASH_Write(FACTORY_ADDR_FLASH,(uint32_t *) &factory, 1 );
  
		
			send_string_to_eth(ether_st.RX_pData,ether_st.RX_Size);
	
		}
		ether_st.RX_flag=0;
	  ether_st.RX_Size=0;
	}
}
