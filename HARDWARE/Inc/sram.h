/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-04 22:02:37
 * @LastEditTime: 2021-04-04 22:09:51
 */
#ifndef _SDRAM_H
#define _SDRAM_H
#include "main.h"

extern SRAM_HandleTypeDef SRAM_Handler;    //SRAM句柄

//使用NOR/SRAM的 Bank1.sector3,地址位HADDR[27,26]=10 
//对IS61LV25616/IS62WV25616,地址线范围为A0~A17 
//对IS61LV51216/IS62WV51216,地址线范围为A0~A18
#define Bank1_SRAM3_ADDR    ((u32)(0x68000000))	


int SRAM_Init(void);
void FSMC_SRAM_WriteBuffer(u8 *pBuffer,u32 WriteAddr,u32 n);
void FSMC_SRAM_ReadBuffer(u8 *pBuffer,u32 ReadAddr,u32 n);
#endif
