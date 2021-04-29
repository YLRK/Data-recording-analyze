/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-05 21:47:48
 * @LastEditTime: 2021-04-05 21:50:42
 */
#ifndef _APP_H
#define _APP_H

#include "lvgl.h"
#include "lv_ex_conf.h"
#include "main.h"


//窗体返回事件,这是我们自己定义的一个事件,所定义的值只要不和littleVGL自带的事件值冲突即可
//LV_EVENT_DELETE是在littleVGL中排最后面的一个事件,加10是为了留点余量
#define USER_EVENT_BACK		(LV_EVENT_DELETE+10)  

//函数申明
void gui_app_start(void);
void toast(const char * msg,uint16_t time);
lv_obj_t * general_win_create(lv_obj_t * parent,const char * title);

#endif

