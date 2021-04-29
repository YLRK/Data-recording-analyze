/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-06 22:30:35
 * @LastEditTime: 2021-04-07 17:14:05
 */
#ifndef __PROGRESS_WIN_H__
#define __PROGRESS_WIN_H__
#include "sys.h"
#include "lvgl.h"



typedef struct
{
	uint8_t Hours;
	uint8_t Minutes;
	uint8_t Seconds;
}Clock_time;


//º¯ÊýÉêÃ÷
void progress_win_create(lv_obj_t * parent);





#endif

