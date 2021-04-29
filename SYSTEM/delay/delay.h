/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-02 23:43:58
 * @LastEditTime: 2021-04-08 11:42:32
 */
#ifndef _DELAY_H
#define _DELAY_H
#include <sys.h>	  

void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
#endif

