/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-03 22:42:18
 * @LastEditTime: 2021-04-22 21:08:32
 */
#ifndef __RTC_H
#define __RTC_H
#include "main.h"
#include "app.h"
#include "calendar_win.h"
#include "progress_win.h"

extern RTC_HandleTypeDef RTC_Handler;  //RTC句柄


int RTC_Init(void);              		//RTC初始化
HAL_StatusTypeDef RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm);      //RTC时间设置
HAL_StatusTypeDef RTC_Set_Date(u8 year,u8 month,u8 date,u8 week);	//RTC日期设置
void RTC_Set_AlarmA(u8 week,u8 hour,u8 min,u8 sec); //设置闹钟时间(按星期闹铃,24小时制)
void RTC_Set_WakeUp(u32 wksel,u16 cnt);             //周期性唤醒定时器设置
void rtc_read(void);
#endif
