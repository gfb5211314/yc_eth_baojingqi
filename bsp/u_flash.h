#ifndef  __U_FLASH_H_
#define  __U_FLASH_H_
#include "main.h"


#define U_FLASH_PAGE_SIZE                                           (2*1024)
#define U_PAGE_NUM                                             16  //16个扇区

#define FLASH_BASE_ADDR                                         0X08000000
#define SN_ADDR_FLASH                                          (FLASH_BASE_ADDR+(U_PAGE_NUM-1)*U_FLASH_PAGE_SIZE)   //15
#define FLASH_WAITETIME                                         1000

//工厂模式
#define FACTORY_ADDR_FLASH                                      (FLASH_BASE_ADDR+(U_PAGE_NUM-2)*U_FLASH_PAGE_SIZE) //14

//stm32g030有16个扇区  一个扇区2K         P6F6  32k/2 扇区
#define FLASH_SECTOR14_START                      0x08007000
#define FLASH_SECTOR14_END                        0x080077FF
#define FLASH_SECTOR15_START                      0x08007800
#define FLASH_SECTOR15_END                        0x08007FFF
// 
#define FLASH_DATA_ADDR_MIN                         FLASH_SECTOR14_START
#define FLASH_DATA_ADDR_MAX                         FLASH_SECTOR15_END
// 



#define SN_CODE                  "ycsyq0112345"    //

extern void STMFLASH_Write(uint32_t WriteAddr, uint32_t *pBuffer, uint32_t NumToWrite)	;
extern void Flash_Write_Num_Word(uint32_t WriteAddr, uint32_t * pBuffer, uint32_t NumToWrite );

/**
  * 函数功能: 读取指定地址的半字(16位数据)
  * 输入参数: faddr:读地址(此地址必须为2的倍数!!)
  * 返 回 值: 返回值:对应数据.
  * 说    明：无
  */
extern uint32_t STMFLASH_ReadWord ( uint32_t faddr );

/**
  * 函数功能: 从指定地址开始读出指定长度的数据
  * 输入参数: ReadAddr:起始地址
  *           pBuffer:数据指针
  *           NumToRead:半字(16位)数
  * 返 回 值: 无
  * 说    明：无
  */
extern void Flash_Read_Word( uint32_t ReadAddr, uint32_t *pBuffer, uint32_t NumToRead )  ; 	

#endif