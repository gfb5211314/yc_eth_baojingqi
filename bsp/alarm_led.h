#ifndef  __ALARM_LED__H__
#define  __ALARM_LED__H__


#include "main.h"


#define  led_on             HAL_GPIO_WritePin(BELL_EN_GPIO_Port, BELL_EN_Pin, GPIO_PIN_SET);
#define  led_off            HAL_GPIO_WritePin(BELL_EN_GPIO_Port, BELL_EN_Pin, GPIO_PIN_RESET);


#endif