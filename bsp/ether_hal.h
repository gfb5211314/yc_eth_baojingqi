#ifndef __ETHER_HAL_H__
#define __ETHER_HAL_H__


#include "main.h"


#define  data_len 800

typedef struct
{
    uint8_t  RX_flag;        //IDLE receive flag
    uint16_t RX_Size;          //receive length
	  uint16_t count;
    uint16_t tem_RX_Size;          //receive length
    uint8_t  RX_pData[data_len];
    uint8_t  tem_RX_pData[data_len];
    uint8_t  TX_pData[data_len];
}ETH_TYPE;
#define  eth_usart        huart2

extern uint8_t  local_eth_ip[40];
//uint8_t   local_eth_port[30]="at+NRPort0=6962\r\n";
extern uint8_t  Remote_eth_ip[40];
extern uint8_t  Remote_eth_port[30];
void send_string_to_eth(uint8_t *p,uint16_t plen);
uint8_t eth_init(void);
void ETH_Rst ( void );
 void  ETH_DMA_START(void);
void eth_at_open(void); 
extern ETH_TYPE  ether_st;
void ETH_Rst ( void );
void eth_at_open(void);
#endif
