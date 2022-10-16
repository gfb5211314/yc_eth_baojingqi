#include "speak_hal.h"
#define sda_H        HAL_GPIO_WritePin(speak_data_GPIO_Port, speak_data_Pin, GPIO_PIN_SET);
#define sda_L        HAL_GPIO_WritePin(speak_data_GPIO_Port, speak_data_Pin, GPIO_PIN_RESET);

uint8_t read_music_pin()
{
	
	  return  HAL_GPIO_ReadPin(speak_busy_GPIO_Port, speak_busy_Pin);
}
void delay_2us(uint32_t i)
{
	
    uint32_t temp;
    SysTick->LOAD=9*i;         //������װ��ֵ, 72MHZʱ
    SysTick->CTRL=0X01;         //ʹ�ܣ����������޶����������ⲿʱ��Դ
    SysTick->VAL=0;                //���������
    do
    {
        temp=SysTick->CTRL;           //��ȡ��ǰ������ֵ
    }
    while((temp&0x01)&&(!(temp&(1<<16))));     //�ȴ�ʱ�䵽��
    SysTick->CTRL=0;    //�رռ�����
    SysTick->VAL=0;        //��ռ�����
}



void Line_1A_WT588S(uint8_t DDATA)
{
	 
//		uint8_t i; 
//		uint8_t B_DATA; 
//		uint8_t num_temp=0; 
//		uint16_t ddata_temp ,pdata_temp;
//		ddata_temp = USER_DATA;
//		pdata_temp = ddata_temp& 0X00FF;
//		ddata_temp>>= 8; 
//		pdata_temp<<= 8; 
//		ddata_temp |= pdata_temp;//�û����ݸ�ֵ
//		num_temp = 16; 
//		sda_L; 
//		HAL_Delay(5); //��ʱ 5MS 
//		B_DATA = (uint8_t)(ddata_temp&0X0001);
//		for(i=0;i<num_temp;i++)
//		{ 
//			if(i==8) 
//				 { 
//					sda_H;
//					HAL_Delay(2);
//					//��ʱ 2MS 
//					sda_L;
//					HAL_Delay(5); //��ʱ 5MS 
//					}
//		    	    sda_H; //�������ݴ����ߣ�׼���������� 
//					if(B_DATA==0) { 
//						/*��ʾ�߼���ƽ 0*/ 
//						delay_2us(100); // ��ʱ 200us
//               sda_L;
//						delay_2us(300); // ��ʱ 600us 
//						}else if(B_DATA==0x01)
//					{ /*��ʾ�߼���ƽ 1*/ 
//						delay_2us(300); // ��ʱ 600us 
//						sda_L;
//						delay_2us(100); // ��ʱ 200us 
//						}
//    	ddata_temp = ddata_temp>>1;
//	B_DATA = (uint8_t)(ddata_temp&0x0001);
//	} 
//		sda_H;
//	HAL_Delay(2);
 HAL_GPIO_WritePin(GPIOB,  BELL_EN_Pin|speak_data_Pin, GPIO_PIN_SET);  //
uint8_t S_DATA,j;
uint8_t B_DATA; 
S_DATA = DDATA;
sda_L;
HAL_Delay(5); //��ʱ 5ms 
B_DATA = S_DATA&0X01;
for(j=0;j<8;j++)
{ 
	if(B_DATA == 1)
		{
			sda_H
			delay_2us(600); //��ʱ 600us 
			sda_L
 delay_2us(200); //��ʱ 200us 
			}else { 
				sda_H
				delay_2us(200); //��ʱ 200us 
				sda_L
				delay_2us(600); //��ʱ 600us 
				}
S_DATA = S_DATA>>1;
B_DATA = S_DATA&0X01; 
}
sda_H
}
//void  wt588s_control(uint16_t cmd)
//{
//  uint8_t i,k = 2;
//  uint8_t data = 0;


//  {
//    while(k != 0)
//    {
//      //�ȸ�λ�ڵ�λ
//      if(k == 2)
//      {
//        data = cmd>>8;
//      }
//      else
//      {
//        data = cmd&0xFF;
//      }
//      k--;
//      
//       sda_L; 
//      HAL_Delay(5);
//      for(i=0;i<8;i++)
//      {
//        if((data&0x01) == 0x01)
//        {
//          sda_H;
//          delay_2us(300);
//            sda_L; 
//          delay_2us(100);
//        }
//        else
//        {
//           sda_H;
//          delay_2us(100);
//           sda_L; 
//          delay_2us(300);
//        }
//        data>>=1;
//      }
//          sda_H;
//      HAL_Delay(2);
//    }
//    
//  }
//   
//}
//��������
void play_music(uint8_t addr)
{  
//	sda_H
//	 sda_L
//HAL_Delay(10);                             /*>2ms*/
//for(uint8_t i=0;i<8;i++)
//{
//    sda_H
// 	if(addr&1)
//{
//     delay_us(2400);                         /*>2400us*/
//      sda_L
//    delay_us(800);                           /*>800us*/
//}
//else
//{
//    delay_us(800);                         /*>800us*/
//  sda_L
//    delay_us(2400);                         /*>2400us*/
//}
// addr>>=1;                             /*��ֵַ����һλ*/
//}
//sda_H
//HAL_Delay(100);  
}
uint8_t play_music_com(uint8_t addr)
{
	          uint8_t value=0;
	     static uint8_t start_music=0;
	  switch(start_music)
		{
			case 0 :  if(read_music_pin()==1)
		  	{
			start_music=1;
				value=0;
			  } 
		  break;
			case 1 :
				   Line_1A_WT588S(addr) ;
		
			      start_music=2;
			     	value=0;
			break;
			case 2 :   if(read_music_pin()==0)
			{
			
				 start_music=3;
					value=0;
			}break;
			case 3 : if(read_music_pin()==1)
			{
		
       start_music=0;
				value=1;
			}
				     
			break;
		}
    return	value;
	
}



