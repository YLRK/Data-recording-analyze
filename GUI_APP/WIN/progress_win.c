#include "progress_win.h"
#include "app.h"
#include "rtc.h"
static lv_obj_t *arc1;
static lv_obj_t *progress_label;
static lv_task_t *task = NULL;
uint8_t progress_val;
lv_style_t arc1_style;
lv_style_t arc2_style;
lv_style_t arc3_style;
lv_obj_t *arc1;
lv_obj_t *arc2;
lv_obj_t *arc3;
extern u8 Time[40];
static lv_obj_t *time_roller[3]; //日期设置roller
static lv_obj_t *time_point_label[2];		//时间的: label
static lv_obj_t *enter_btn;		//确认按键
extern Clock_time RTC_time;
RTC_TimeTypeDef RTC_TimeStruct;
Clock_time RTC_time;
static const char roller_string[] = 
{
	"00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n\
24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n\
48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59"
};

/**
 * @brief: 事件回调函数
 * @version: 1.0
 * @Date: 2021-04-24 17:06:40
 * @param {lv_obj_t} *obj
 * @param {lv_event_t} event
 */
static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	if (event == USER_EVENT_BACK) //窗体返回事件,点击左上角的"< Back"按钮会触发此事件
	{
		if (task) //删除掉任务
		{
			lv_task_del(task);
			task = NULL;
		}
	}
	else if (obj == enter_btn)
	{
		if (event == LV_EVENT_RELEASED)
		{
			HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);    
			RTC_Set_Time(lv_roller_get_selected(time_roller[0]), lv_roller_get_selected(time_roller[1]), lv_roller_get_selected(time_roller[2]), RTC_HOURFORMAT12_PM);  
		}
	}
}

/**
 * @brief: 设置进度值
 * @version: 1.0
 * @Date: 2021-04-24 17:06:47
 * @param {uint8_t} val 范围为[0,100]
 */
static void progress_set_val(uint8_t val)
{
	lv_arc_set_angles(arc1, 0, (uint16_t)(15 * RTC_time.Hours));
	lv_arc_set_angles(arc2, 0, (uint16_t)(6 * RTC_time.Minutes));
	lv_arc_set_angles(arc3, 0, (uint16_t)(6 * RTC_time.Seconds));

	lv_label_set_text(progress_label, (char *)Time);
	lv_obj_realign(progress_label);
}

/**
 * @brief: 任务回调函数
 * @version: 1.0
 * @Date: 2021-04-24 17:06:59
 * @param {lv_task_t} *t
 */
static void progress_task(lv_task_t *t)
{
	progress_set_val(progress_val);
}

/**
 * @brief: 创建窗体
 * @version: 1.0
 * @Date: 2021-04-24 17:07:07
 * @param {lv_obj_t} *parent
 */
void progress_win_create(lv_obj_t *parent)
{
	lv_obj_t *win = general_win_create(parent, "Clock");
	lv_obj_set_event_cb(win, event_handler); //设置事件回调函数
	uint8_t i;

	//1.设置样式
	//时-外-粗-红
	lv_style_copy(&arc1_style, &lv_style_plain);
	arc1_style.line.color = LV_COLOR_RED; //弧形的颜色s
	arc1_style.line.width = 10;			  //弧形的厚度
	arc1_style.line.rounded = 1;		  //末端为圆角 ,如果为 0的话 ,则为直角

	//分-中-中-蓝
	lv_style_copy(&arc2_style, &lv_style_plain);
	arc2_style.line.color = LV_COLOR_BLUE; //弧形的颜色s
	arc2_style.line.width = 6;			   //弧形的厚度
	arc2_style.line.rounded = 1;		   //末端为圆角 ,如果为 0的话 ,则为直角

	//秒-内-细-绿
	lv_style_copy(&arc3_style, &lv_style_plain);
	arc3_style.line.color = LV_COLOR_GREEN; //弧形的颜色s
	arc3_style.line.width = 4;				//弧形的厚度
	arc3_style.line.rounded = 1;			//末端为圆角 ,如果为 0的话 ,则为直角

	//2.创建时
	arc1 = lv_arc_create(win, NULL);						//创建弧形对象
	lv_arc_set_style(arc1, LV_ARC_STYLE_MAIN, &arc1_style); //设置样式
	lv_obj_set_size(arc1, 150, 150);						//设置大小,设置的宽度和高度必须得相等,弧形半径等于宽度的一半
															// lv_obj_set_pos(arc1, 0, 0);                             //设置坐标
	lv_obj_align(arc1, NULL, LV_ALIGN_IN_TOP_MID, 0, 40);	//设置对齐方式

	//3.创建分
	arc2 = lv_arc_create(win, arc1);						//直接从arc1拷贝
	lv_arc_set_style(arc2, LV_ARC_STYLE_MAIN, &arc2_style); //设置样式
	lv_obj_set_size(arc2, 130, 130);						//设置大小,设置的宽度和高度必须得相等,弧形半径等于宽度的一半
	lv_obj_align(arc2, arc1, LV_ALIGN_CENTER, 0, 0);		//设置与arc1的对齐方式

	//4.创建秒
	arc3 = lv_arc_create(win, arc1);						//直接从arc1拷贝
	lv_arc_set_style(arc3, LV_ARC_STYLE_MAIN, &arc3_style); //设置样式
	lv_obj_set_size(arc3, 120, 120);						//设置大小,设置的宽度和高度必须得相等,弧形半径等于宽度的一半
	lv_obj_align(arc3, arc1, LV_ALIGN_CENTER, 0, 0);		//设置与arc1的对齐方式

	progress_label = lv_label_create(win, NULL);
	lv_obj_align(progress_label, arc1, LV_ALIGN_CENTER, 0, 0);

	//创建滚轮
	//时
	time_roller[0] = lv_roller_create(win, NULL);
	lv_roller_set_options(time_roller[0], "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23", LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_selected(time_roller[0], RTC_time.Hours, LV_ANIM_OFF);	  //设置默认值
	lv_roller_set_fix_width(time_roller[0], 40);							  //设置固定宽度
	lv_roller_set_visible_row_count(time_roller[0], 1);					  //设置可见的行数
	lv_obj_align(time_roller[0], win,LV_ALIGN_OUT_BOTTOM_MID, -50, -90); //设置对齐方式

	//分
	time_roller[1] = lv_roller_create(win, NULL);
	lv_roller_set_options(time_roller[1],roller_string, LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_selected(time_roller[1], RTC_time.Minutes, LV_ANIM_OFF);	  //设置默认值
	lv_roller_set_fix_width(time_roller[1], 40);							  //设置固定宽度
	lv_roller_set_visible_row_count(time_roller[1], 1);					  //设置可见的行数
	lv_obj_align(time_roller[1], win,LV_ALIGN_OUT_BOTTOM_MID, 0, -90); //设置对齐方式
	
	//秒
	time_roller[2] = lv_roller_create(win, NULL);
	lv_roller_set_options(time_roller[2],roller_string, LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_selected(time_roller[2], RTC_time.Seconds, LV_ANIM_OFF);	  //设置默认值
	lv_roller_set_fix_width(time_roller[2], 40);							  //设置固定宽度
	lv_roller_set_visible_row_count(time_roller[2], 1);					  //设置可见的行数
	lv_obj_align(time_roller[2], win,LV_ALIGN_OUT_BOTTOM_MID, 50, -90); //设置对齐方式

	for(i = 0; i < 2; i++)	
	{
		time_point_label[i] = lv_label_create(win, NULL);		//创建时间point lable
		lv_label_set_text(time_point_label[i], ":");
		lv_obj_align(time_point_label[i], time_roller[i], LV_ALIGN_OUT_RIGHT_MID, 5, 0);
	}

	enter_btn = lv_btn_create(win, NULL);
	lv_obj_set_size(enter_btn,60, 40);		//设置按钮大小
	lv_obj_align(enter_btn, win, LV_ALIGN_OUT_BOTTOM_MID, 0, -40);		//设置按钮对齐

	lv_obj_t *enter_btn_lable = lv_label_create(enter_btn, NULL);		//创建按钮label
	lv_label_set_text(enter_btn_lable, "Enter"); 
	lv_obj_align(enter_btn_lable, enter_btn, LV_ALIGN_CENTER, 0, 0);		//设置按钮文本对齐
	lv_obj_set_event_cb(enter_btn, event_handler); //设置事件回调函数

	//设置默认进度
	progress_set_val(progress_val);
	//创建一个任务来模拟进度的加载过程
	if (task == NULL)
		task = lv_task_create(progress_task, 200, LV_TASK_PRIO_MID, NULL);
}
