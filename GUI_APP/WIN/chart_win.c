/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-06 22:30:35
 * @LastEditTime: 2021-04-25 19:40:59
 */
#include "chart_win.h"
#include "app.h"
#include "dht11.h"
#define POINT_COUNT 40	   //数据线所具有的数据点个数
#define SLIDER_MAX_VAL 100 //滑块的最大值
static lv_coord_t series1_y[POINT_COUNT] = {0};
static lv_obj_t *chart1;
static lv_chart_series_t *series1;
static lv_chart_series_t *series2;
static lv_task_t *task = NULL;
static lv_obj_t * label1;
static lv_obj_t *temp[2]; //日期设置roller
static lv_obj_t *enter_btn;		//确认按键
extern u8 temperature[40];
extern u8 humidity[40];
u8 chart_flag;

/**
 * @brief: 任务回调函数
 * @version: 1.0
 * @Date: 2021-04-25 19:40:50
 * @param {lv_task_t} *t
 */
static void Temp_task(lv_task_t *t)
{
	uint8_t i;
	// char buff1[40];
	char buff[40];
	int16_t speed_val;
	speed_val = temperature[39];
	if (chart_flag == 1)
	{
		for (i = 0; i < POINT_COUNT; i++)
		{
			series1->points[i] = (lv_coord_t)(temperature[i]); //按照缩放系数,修改数据点的值
			series2->points[i] = (lv_coord_t)(humidity[i]);	   //按照缩放系数,修改数据点的值
		}
		lv_chart_refresh(chart1); //更新图表
		//把此速度显示在标签上,然后根据不同的数值显示出不同的颜色
		//绿色代表安全,黄色代表警告,红色代表危险  
		sprintf(buff,"#%s %d C#",speed_val<30?"00FF00":(speed_val<40?"FFFF00":"FF0000"),speed_val); 
		lv_label_set_text(label1,buff);
	}
}

/**
 * @brief: 事件回调函数
 * @version: 1.0
 * @Date: 2021-04-25 19:40:41
 * @param {lv_obj_t} *obj
 * @param {lv_event_t} event
 */
static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	if (obj == enter_btn)
	{
		if (event == LV_EVENT_RELEASED)
		{
			HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);    
			temperature_L = lv_roller_get_selected(temp[0]) ;
			temperature_H = lv_roller_get_selected(temp[1]) ;
		}
	}
}


/**
 * @brief: 创建图表用于显示温湿度和修改温度上下限
 * @version: 1.0
 * @Date: 2021-04-23 10:11:27
 * @param {lv_obj_t} *parent
 */
void chart_win_create(lv_obj_t *parent)
{
	lv_obj_t *win;
	win = general_win_create(parent, "Temp_Humi");

	//创建图表
	chart1 = lv_chart_create(win, NULL);
	lv_obj_set_size(chart1, 180, 200);									 //设置大小
	lv_obj_align(chart1, NULL, LV_ALIGN_IN_TOP_MID, 17, 40);			 //设置对齐方式
	lv_chart_set_type(chart1, LV_CHART_TYPE_POINT | LV_CHART_TYPE_LINE); //设置为散点和折线的组合
	lv_chart_set_series_opa(chart1, LV_OPA_80);							 //设置数据线的透明度
	lv_chart_set_series_width(chart1, 4);								 //设置数据线的宽度
	lv_chart_set_series_darking(chart1, LV_OPA_80);						 //设置数据线的黑阴影效果
	lv_chart_set_point_count(chart1, POINT_COUNT);						 //设置数据点的个数
	lv_chart_set_div_line_count(chart1, 4, 4);							 //设置水平和垂直分割线
	lv_chart_set_range(chart1, 0, 100);									 //设置y轴的数值范围
	lv_chart_set_y_tick_length(chart1, 10, 3);
	lv_chart_set_y_tick_texts(chart1, "100\n80\n60\n40\n20\n0", 2, LV_CHART_AXIS_DRAW_LAST_TICK);
	lv_chart_set_x_tick_length(chart1, 10, 3);
	lv_chart_set_x_tick_texts(chart1, "0\n\n\n\n\n40", 2, LV_CHART_AXIS_DRAW_LAST_TICK);
	lv_chart_set_margin(chart1, 40);

	//往图表中添加数据线
	series1 = lv_chart_add_series(chart1, LV_COLOR_RED);		   //指定为红色
	series2 = lv_chart_add_series(chart1, LV_COLOR_BLUE);		   //指定为红色
	lv_chart_set_points(chart1, series1, (lv_coord_t *)series1_y); //初始化数据点的值
	lv_chart_set_points(chart1, series2, (lv_coord_t *)series1_y); //初始化数据点的值	//创建滑块

	//显示温度
	label1 = lv_label_create(win,NULL);
	lv_label_set_long_mode(label1,LV_LABEL_LONG_BREAK);//设置长文本模式
	lv_obj_set_width(label1,40);//设置宽度
	lv_label_set_align(label1,LV_LABEL_ALIGN_CENTER);//设置文本居中对齐
	lv_label_set_body_draw(label1,true);//使能背景重绘
	lv_obj_align(label1,chart1,LV_ALIGN_OUT_BOTTOM_MID,-15,65);//设置对齐方式
	lv_label_set_text(label1,"0 °C");//设置文本
	lv_label_set_recolor(label1,true);//使能文本重绘色

	//温度下限
	temp[0] = lv_roller_create(win, NULL);
	lv_roller_set_options(temp[0], "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23", LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_selected(temp[0], temperature_L, LV_ANIM_OFF);	  //设置默认值
	lv_roller_set_fix_width(temp[0], 40);							  //设置固定宽度
	lv_roller_set_visible_row_count(temp[0], 1);					  //设置可见的行数
	lv_obj_align(temp[0], label1,LV_ALIGN_OUT_LEFT_MID, -20, 0); //设置对齐方式

	//温度上限
	temp[1] = lv_roller_create(win, NULL);
	lv_roller_set_options(temp[1], "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47", LV_ROLLER_MODE_INIFINITE);
	lv_roller_set_selected(temp[1], temperature_H, LV_ANIM_OFF);	  //设置默认值
	lv_roller_set_fix_width(temp[1], 40);							  //设置固定宽度
	lv_roller_set_visible_row_count(temp[1], 1);					  //设置可见的行数
	lv_obj_align(temp[1], label1,LV_ALIGN_OUT_RIGHT_MID, 20, 0); //设置对齐方式
	
	enter_btn = lv_btn_create(win, NULL);
	lv_obj_set_size(enter_btn,60, 40);		//设置按钮大小
	lv_obj_align(enter_btn, label1, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);		//设置按钮对齐

	lv_obj_t *enter_btn_lable = lv_label_create(enter_btn, NULL);		//创建按钮label
	lv_label_set_text(enter_btn_lable, "Enter"); 
	lv_obj_align(enter_btn_lable, enter_btn, LV_ALIGN_CENTER, 0, 0);		//设置按钮文本对齐
	lv_obj_set_event_cb(enter_btn, event_handler); //设置事件回调函数
	
	chart_flag = 1;
	if (task == NULL)
		task = lv_task_create(Temp_task, 500, LV_TASK_PRIO_LOW, NULL);
}
