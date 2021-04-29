#include "rtc.h"

RTC_HandleTypeDef RTC_Handler; //RTC句柄
extern Clock_time RTC_time;
//RTC时间设置
//hour,min,sec:小时,分钟,秒钟
//ampm:@RTC_AM_PM_Definitions:RTC_HOURFORMAT12_AM/RTC_HOURFORMAT12_PM
//返回值:SUCEE(1),成功
//       ERROR(0),进入初始化模式失败
HAL_StatusTypeDef RTC_Set_Time(u8 hour, u8 min, u8 sec, u8 ampm)
{
    RTC_TimeTypeDef RTC_TimeStructure;

    RTC_TimeStructure.Hours = hour;
    RTC_TimeStructure.Minutes = min;
    RTC_TimeStructure.Seconds = sec;
    RTC_TimeStructure.TimeFormat = ampm;
    RTC_TimeStructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    RTC_TimeStructure.StoreOperation = RTC_STOREOPERATION_RESET;
    return HAL_RTC_SetTime(&RTC_Handler, &RTC_TimeStructure, RTC_FORMAT_BIN);
}

//RTC日期设置
//year,month,date:年(0~99),月(1~12),日(0~31)
//week:星期(1~7,0,非法!)
//返回值:SUCEE(1),成功
//       ERROR(0),进入初始化模式失败
HAL_StatusTypeDef RTC_Set_Date(u8 year, u8 month, u8 date, u8 week)
{
    RTC_DateTypeDef RTC_DateStructure;

    RTC_DateStructure.Date = date;
    RTC_DateStructure.Month = month;
    RTC_DateStructure.WeekDay = week;
    RTC_DateStructure.Year = year;
    return HAL_RTC_SetDate(&RTC_Handler, &RTC_DateStructure, RTC_FORMAT_BIN);
}

//RTC底层驱动，时钟配置
//此函数会被HAL_RTC_Init()调用
//hrtc:RTC句柄
void HAL_RTC_MspInit(RTC_HandleTypeDef *hrtc)
{
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    __HAL_RCC_PWR_CLK_ENABLE(); //使能电源时钟PWR
    HAL_PWR_EnableBkUpAccess(); //取消备份区域写保护

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE; //LSE配置
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON; //RTC使用LSE
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC; //外设为RTC
    PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSE; //RTC时钟源为LSE
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    __HAL_RCC_RTC_ENABLE();                            //RTC时钟使能
    RTC_Set_WakeUp(RTC_WAKEUPCLOCK_CK_SPRE_16BITS, 0); //配置WAKE UP中断,1秒钟中断一次
}

//设置闹钟时间(按星期闹铃,24小时制)
//week:星期几(1~7) @ref  RTC_WeekDay_Definitions
//hour,min,sec:小时,分钟,秒钟
void RTC_Set_AlarmA(u8 week, u8 hour, u8 min, u8 sec)
{
    RTC_AlarmTypeDef RTC_AlarmSturuct;

    RTC_AlarmSturuct.AlarmTime.Hours = hour;  //小时
    RTC_AlarmSturuct.AlarmTime.Minutes = min; //分钟
    RTC_AlarmSturuct.AlarmTime.Seconds = sec; //秒
    RTC_AlarmSturuct.AlarmTime.SubSeconds = 0;
    RTC_AlarmSturuct.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;

    RTC_AlarmSturuct.AlarmMask = RTC_ALARMMASK_NONE; //精确匹配星期，时分秒
    RTC_AlarmSturuct.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
    RTC_AlarmSturuct.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_WEEKDAY; //按星期
    RTC_AlarmSturuct.AlarmDateWeekDay = week;                               //星期
    RTC_AlarmSturuct.Alarm = RTC_ALARM_A;                                   //闹钟A
    HAL_RTC_SetAlarm_IT(&RTC_Handler, &RTC_AlarmSturuct, RTC_FORMAT_BIN);

    HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0x01, 0x02); //抢占优先级1,子优先级2
    HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
}

//周期性唤醒定时器设置
/*wksel:  @ref RTCEx_Wakeup_Timer_Definitions
#define RTC_WAKEUPCLOCK_RTCCLK_DIV16        ((uint32_t)0x00000000)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV8         ((uint32_t)0x00000001)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV4         ((uint32_t)0x00000002)
#define RTC_WAKEUPCLOCK_RTCCLK_DIV2         ((uint32_t)0x00000003)
#define RTC_WAKEUPCLOCK_CK_SPRE_16BITS      ((uint32_t)0x00000004)
#define RTC_WAKEUPCLOCK_CK_SPRE_17BITS      ((uint32_t)0x00000006)
*/
//cnt:自动重装载值.减到0,产生中断.
void RTC_Set_WakeUp(u32 wksel, u16 cnt)
{
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&RTC_Handler, RTC_FLAG_WUTF); //清除RTC WAKE UP的标志

    HAL_RTCEx_SetWakeUpTimer_IT(&RTC_Handler, cnt, wksel); //设置重装载值和时钟

    HAL_NVIC_SetPriority(RTC_WKUP_IRQn, 0x02, 0x02); //抢占优先级1,子优先级2
    HAL_NVIC_EnableIRQ(RTC_WKUP_IRQn);
}

//RTC闹钟中断服务函数
void RTC_Alarm_IRQHandler(void)
{
    HAL_RTC_AlarmIRQHandler(&RTC_Handler);
}

//RTC闹钟A中断处理回调函数
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    rt_kprintf("ALARM A!\r\n");
}

//RTC WAKE UP中断服务函数
void RTC_WKUP_IRQHandler(void)
{
    HAL_RTCEx_WakeUpTimerIRQHandler(&RTC_Handler);
}

//RTC WAKE UP中断处理
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
    //    LED1=!LED1;
}

u8 Time[40];
u8 Date[40];

extern lv_calendar_date_t today;
/**
 * @brief: 读取时间和日期
 * @version: 1.0
 * @Date: 2021-04-26 09:13:22
 */
void rtc_read(void)
{
    RTC_TimeTypeDef RTC_TimeStruct;
    RTC_DateTypeDef RTC_DateStruct;

    HAL_RTC_GetTime(&RTC_Handler, &RTC_TimeStruct, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&RTC_Handler, &RTC_DateStruct, RTC_FORMAT_BIN);
    RTC_time.Hours = RTC_TimeStruct.Hours;
    RTC_time.Minutes = RTC_TimeStruct.Minutes;
    RTC_time.Seconds = RTC_TimeStruct.Seconds;
    today.year = RTC_DateStruct.Year + 2000;
    today.month = RTC_DateStruct.Month;
    today.day = RTC_DateStruct.Date;

    sprintf((char *)Time, "%02d:%02d:%02d", RTC_time.Hours, RTC_time.Minutes, RTC_time.Seconds);

}

/**
 * @brief: RTC初始化
 * @version: 1.0
 * @Date: 2021-04-24 17:10:35
 */
int RTC_Init(void)
{
    RTC_Handler.Instance = RTC;
    RTC_Handler.Init.HourFormat = RTC_HOURFORMAT_24; //RTC设置为24小时格式
    RTC_Handler.Init.AsynchPrediv = 0X7F;            //RTC异步分频系数(1~0X7F)
    RTC_Handler.Init.SynchPrediv = 0XFF;             //RTC同步分频系数(0~7FFF)
    RTC_Handler.Init.OutPut = RTC_OUTPUT_DISABLE;
    RTC_Handler.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    RTC_Handler.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;

    if (HAL_RTC_Init(&RTC_Handler) != HAL_OK)
        return 2;

    if (HAL_RTCEx_BKUPRead(&RTC_Handler, RTC_BKP_DR0) != 0X5050) //是否第一次配置
    {
        RTC_Set_Time(16, 30, 0, RTC_HOURFORMAT12_PM);           //设置时间 ,根据实际时间修改
        RTC_Set_Date(21, 4, 24, 4);                              //设置日期
        HAL_RTCEx_BKUPWrite(&RTC_Handler, RTC_BKP_DR0, 0X5050); //标记已经初始化过了
    }

    return RT_EOK;
}

INIT_APP_EXPORT(RTC_Init);
