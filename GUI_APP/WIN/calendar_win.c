/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-06 22:30:35
 * @LastEditTime: 2021-04-24 17:05:16
 */
#include "calendar_win.h"
#include "app.h"
#include "rtc.h"
//周日,周一,周二,...,周六
const char *const day_names[7] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
//一月,二月,...,十二月
const char *const month_names[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
static const char roller_string[] = 
{
	"00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n\
24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n\
48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59"
};
lv_calendar_date_t today;
static lv_obj_t *calendar1;
static lv_obj_t *date_roller[3]; //日期设置roller
static lv_obj_t *date_Hline_label[3];		//日期的20 和 - lable
static lv_obj_t *enter_btn;		//确认按键
extern u8 Date[40];

/**
 * @brief: 事件回调函数
 * @version: 1.0
 * @Date: 2021-04-24 17:05:08
 * @param {lv_obj_t} *obj
 * @param {lv_event_t} event
 */
static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	RTC_DateTypeDef RTC_DateStructure;
	if (obj == calendar1)
	{
		if (event == LV_EVENT_CLICKED)
		{
			lv_calendar_date_t *selected_date = lv_calendar_get_pressed_date(obj); //获取被按下的日期
			if (selected_date && (selected_date->year != 0))
			{
				lv_calendar_set_today_date(obj, selected_date);						 //将用户选择的日期设置为今天的日期,即TODAY日期
				lv_calendar_set_showed_date(obj, selected_date);					 //跳转到这个日期所在的界面
			}
		}
	}
	else if (obj == enter_btn)
	{
		if (event == LV_EVENT_RELEASED)
		{
			HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);    
			RTC_DateStructure.Year = lv_roller_get_selected(date_roller[0]) ;    
			RTC_DateStructure.Month = lv_roller_get_selected(date_roller[1]) + 1;
			RTC_DateStructure.Date = lv_roller_get_selected(date_roller[2]) + 1;
			HAL_RTC_SetDate(&RTC_Handler, &RTC_DateStructure, RTC_FORMAT_BIN);
		}
	}
}

/**
 * @brief: 创建日历和修改日期
 * @version: 1.0
 * @Date: 2021-04-23 10:10:53
 */
void calendar_win_create(lv_obj_t *parent)
{
	lv_obj_t *win = general_win_create(parent, "Calendar");
	uint8_t i;
	//创建日期
	calendar1 = lv_calendar_create(win, NULL);
	lv_obj_set_size(calendar1, 220, 220);					   //设置大小
	lv_obj_align(calendar1, NULL, LV_ALIGN_IN_TOP_MID, 0, 40); //设置对齐方式
	lv_obj_set_event_cb(calendar1, event_handler);			   //设置事件回调函数

	lv_calendar_set_today_date(calendar1, &today);																							   //设置TODAY日期
	lv_calendar_set_showed_date(calendar1, &today);																							   //跳转到TODAY日期所在的界面
	lv_calendar_set_day_names(calendar1, (const char **)day_names);																			   //设置星期信息行的标题
	lv_calendar_set_month_names(calendar1, (const char **)month_names);																		   //设置月份的标题

	//创建滚轮
	//年
	date_roller[0] = lv_roller_create(win, NULL);
	lv_roller_set_options(date_roller[0], roller_string, LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_selected(date_roller[0], today.year - 2000, LV_ANIM_OFF);	  //设置默认值
	lv_roller_set_fix_width(date_roller[0], 40);							  //设置固定宽度
	lv_roller_set_visible_row_count(date_roller[0], 1);					  //设置可见的行数
	lv_obj_align(date_roller[0], calendar1,LV_ALIGN_OUT_BOTTOM_LEFT, 50, 15); //设置对齐方式

	//月
	date_roller[1] = lv_roller_create(win, NULL);
	lv_roller_set_options(date_roller[1], "01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12", LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_selected(date_roller[1], today.month -1, LV_ANIM_OFF);	  //设置默认值
	lv_roller_set_fix_width(date_roller[1], 40);							  //设置固定宽度
	lv_roller_set_visible_row_count(date_roller[1], 1);					  //设置可见的行数
	lv_obj_align(date_roller[1], calendar1,LV_ALIGN_OUT_BOTTOM_LEFT, 100, 15); //设置对齐方式

	//日
	date_roller[2] = lv_roller_create(win, NULL);
	lv_roller_set_options(date_roller[2], "01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31", LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_selected(date_roller[2], today.day-1, LV_ANIM_OFF);	  //设置默认值
	lv_roller_set_fix_width(date_roller[2], 40);							  //设置固定宽度
	lv_roller_set_visible_row_count(date_roller[2], 1);					  //设置可见的行数
	lv_obj_align(date_roller[2], calendar1, LV_ALIGN_OUT_BOTTOM_LEFT, 150, 15); //设置对齐方式

	for(i = 0; i < 3; i++)	//创建日期的 年20 和 - lable
	{
		date_Hline_label[i] = lv_label_create(win, NULL);		//创建日期的 年20 和 - lable
		lv_label_set_text(date_Hline_label[i], i ? "-" : "20");
		lv_obj_align(date_Hline_label[i], date_roller[i], LV_ALIGN_OUT_LEFT_MID, i ? -4 : 0, 0);
	}

	enter_btn = lv_btn_create(win, NULL);
	lv_obj_set_size(enter_btn,60, 40);		//设置按钮大小
	lv_obj_align(enter_btn, win, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);		//设置按钮对齐

	lv_obj_t *enter_btn_lable = lv_label_create(enter_btn, NULL);		//创建按钮label
	lv_label_set_text(enter_btn_lable, "Enter"); 
	lv_obj_align(enter_btn_lable, enter_btn, LV_ALIGN_CENTER, 0, 0);		//设置按钮文本对齐
	lv_obj_set_event_cb(enter_btn, event_handler); //设置事件回调函数
}
