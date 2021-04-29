/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-04 17:30:36
 * @LastEditTime: 2021-04-24 17:10:20
 */
#include "timerout.h"
#include "lvgl.h"
#include "usmart.h"
#define LED1_PIN    GET_PIN(F, 10)
/* 定时器的控制块 */
static struct rt_timer timer1;
static struct rt_timer timer2;

/**
 * @brief: 定时器 1 超时函数 提供usmart 100ms扫描
 * @version: 1.0
 * @Date: 2021-04-24 17:09:56
 */
static void timeout1(void* parameter)
{
	usmart_dev.scan();	//执行usmart扫描
}

/**
 * @brief: 提供lvgl的心跳 1ms
 * @version: 1.0
 * @Date: 2021-04-24 17:09:46
 */
static void lv_tack(void* parameter)
{
	lv_tick_inc(1);//lvgl的 1ms心跳
}

/**
 * @brief: 软件定时器初始化
 * @version: 1.0
 * @Date: 2021-04-24 17:09:24
 */
int timer_static_sample(void)
{
	
    // rt_pin_mode(LED1_PIN,PIN_MODE_OUTPUT);
    /* 初始化定时器 */
    rt_timer_init(&timer1, "timerout",  
                    timeout1, /* 超时时回调的处理函数 */
                    RT_NULL, /* 超时函数的入口参数 */
                    100, /* 定时长度，以 OS Tick 为单位 */
                    RT_TIMER_FLAG_PERIODIC); /* 周期性定时器 */
	
    rt_timer_init(&timer2, "lv_tack",  
                    lv_tack, /* 超时时回调的处理函数 */
                    RT_NULL, /* 超时函数的入口参数 */
                    1, /* 定时长度，以 OS Tick 为单位 */
                    RT_TIMER_FLAG_PERIODIC); /* 周期性定时器 */
	
    /* 启动定时器 */
    rt_timer_start(&timer1);
	rt_timer_start(&timer2);
    return 0;
}

INIT_APP_EXPORT(timer_static_sample);



