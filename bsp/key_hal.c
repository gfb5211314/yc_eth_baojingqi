#include "key_hal.h"
#include "main.h"
//��ֲֻ��Ҫ���ĺ궨��GPIO�˿ں�����
//#define   key1_port    key1_GPIO_Port
//#define   key1_pin       key1_Pin

//#define   key2_port    key2_GPIO_Port
//#define   key2_pin       key2_Pin

//#define   key3_port    key3_GPIO_Port
//#define   key3_pin       key3_Pin

//#define   rang_key_port    rang_key_GPIO_Port
//#define   rang_Pin       rang_key_Pin

//#define   FANGCHAI_key_Port    FANGCHAI_GPIO_Port
//#define   fangchai_key_pin       FANGCHAI_Pin
//uint8_t key_state_value=0;
//uint8_t init_key_flag=0;
// extern uint8_t  scan_key_flag;
//  extern uint8_t  runing_state_flag;
//	  extern uint8_t  rang_key_flag;
//		  extern uint8_t  fangchai_flag;
//			  extern uint8_t  sleep_flag;
//  extern		uint8_t password_key;  //��������־
//	extern uint8_t password_key_value;
//				uint8_t xingling_flag=0;
//		uint8_t  reset_rang_flag=0;
//		uint8_t  reset_rang_key=0;
////HAL�ӿڲ㺯��
////���key1��ֵ
//uint8_t get_key1()
//{
//	return  HAL_GPIO_ReadPin(key1_port, key1_pin);
//}
////���key2��ֵ
//uint8_t get_key2()
//{
//	return  HAL_GPIO_ReadPin(key2_port, key2_Pin);
//}
////���key3��ֵ
//uint8_t get_key3()
//{
//	return  HAL_GPIO_ReadPin(key3_port, key3_Pin);
//}

////���rang��ֵ
//uint8_t get_rang_key()
//{
//		return  HAL_GPIO_ReadPin(rang_key_port, rang_Pin);
//	
//	
//}

////ɨ�谴��������
//uint8_t  scan_key()
//{
//	  
//	  switch(key_state_value)
//		{
//       case 1 :  
//               key_state_value=0;		 
//              return 1;
//			 break;
//       case 2 :   key_state_value=0;	  
//              return 2;
//			 break;
//			 case 3 :  key_state_value=0;	   
//              return 3;
//			 break;



//		}			

//}
//void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
//{
//   
//     HAL_Delay(10);/* ��ʱһС��ʱ�䣬�������� */
//	if((scan_key_flag==1)||(runing_state_flag==1))
//	{
//     if(GPIO_Pin==key1_Pin)
//    {
//	   
//    HAL_Delay(10);/* ��ʱһС��ʱ�䣬�������� */
//    if(HAL_GPIO_ReadPin(key1_GPIO_Port,key1_Pin)==0)
//    {
//			    printf("1");
//	        password_key=1;
//          key_state_value=1;
//	
//		  
//    }

//    }
// 

//}
////
uint8_t get_key1()
{
	 if( HAL_GPIO_ReadPin(ring_key_GPIO_Port, ring_key_Pin)==0)
	 {
		   HAL_Delay(10);
		 
		 	 if( HAL_GPIO_ReadPin(ring_key_GPIO_Port, ring_key_Pin)==0)
			 {
				 	return  HAL_GPIO_ReadPin(ring_key_GPIO_Port, ring_key_Pin);
			 }
	 }

}
