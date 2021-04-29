#include "main_win.h"
#include "app.h"
#include "calendar_win.h"
#include "chart_win.h"
#include "gauge_win.h"
#include "login_win.h"
#include "progress_win.h"
#include "cpu_usage.h"
#include "file_win.h"

//申明图片
LV_IMG_DECLARE(logo_img);
LV_IMG_DECLARE(date_img);
LV_IMG_DECLARE(chart_img);
LV_IMG_DECLARE(gauge_img);
LV_IMG_DECLARE(progress_img);
LV_IMG_DECLARE(file_img);
//变量定义
#define TABLE_COL_CNT 3		 //表格的列数
#define TABLE_ROW_CNT 4		 //表格的宽度
#define SPLIT_LINE_WIDTH 200 //水平分割线的宽度
const lv_point_t SPLIT_LINE_POINTS[2] = {{0, 0}, {SPLIT_LINE_WIDTH, 0}};
const char *const MBOX_MAP[] = {"Yes", "No", ""};
//定义表格每一行的内容
const char *const TABLE_CELL_VALUE[TABLE_ROW_CNT][TABLE_COL_CNT] = {
	{"Name", "Sex", "Age"}, //第一行,作为标题行
	{"XYL", "Man", "20"},
	{"ZWH", "Man", "22"},
	{"CL", "Man", "20"}};

lv_obj_t *clock_time;
lv_obj_t *cpu_load;
lv_obj_t *main_win;
static lv_obj_t *quit_btn;
static lv_obj_t *quit_mbox = NULL;
static lv_obj_t *calendar_item_btn, *progress_item_btn, *chart_item_btn, *gauge_item_btn, *file_item_btn;
static lv_obj_t *header;
static lv_task_t *task = NULL;
extern u8 Time[40];
float load = 0;
//函数申明
void quit_mbox_create(lv_obj_t *parent);
static void header_create(void);

/**
 * @brief: 按钮事件回调函数
 * @version: 1.0
 * @Date: 2021-04-23 17:35:02
 * @param {lv_obj_t} *obj
 * @param {lv_event_t} event
 */
static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	uint16_t btn_id;
	if (obj == quit_btn)
	{
		if (event == LV_EVENT_RELEASED)
		{
			quit_mbox_create(lv_obj_get_parent(obj)); //是否退出?
		}
	}
	else if (obj == quit_mbox)
	{
		if (event == LV_EVENT_VALUE_CHANGED)
		{
			lv_obj_del(quit_mbox); //关闭退出对话框
			quit_mbox = NULL;
			btn_id = *((uint16_t *)lv_event_get_data()); //获取退出对话框中的按钮id
			if (btn_id == 0)							 //点击了Yes按钮
			{
				lv_obj_del(main_win);			//删除主界面
				login_win_create(lv_scr_act()); //返回到登录界面
			}
		}
	}
	else if (obj == calendar_item_btn)
	{
		//当列表出现滚轮时,用LV_EVENT_CLICKED来处理松手事件会比LV_EVENT_RELEASED好一些,
		//因为滑动列表时,LV_EVENT_CLICKED事件不会出现误触发,而LV_EVENT_RELEASED会误触发
		if (event == LV_EVENT_CLICKED)
			calendar_win_create(lv_scr_act()); //跳转到calendar窗体
	}
	else if (obj == progress_item_btn)
	{
		if (event == LV_EVENT_CLICKED)
			progress_win_create(lv_scr_act()); //跳转到progress窗体
	}
	else if (obj == chart_item_btn)
	{
		if (event == LV_EVENT_CLICKED)
			chart_win_create(lv_scr_act()); //跳转到chart窗体
	}
	else if (obj == gauge_item_btn)
	{
		if (event == LV_EVENT_CLICKED)
			gauge_win_create(lv_scr_act()); //跳转到gauge窗体
	}
	else if (obj == file_item_btn)
	{
		if (event == LV_EVENT_CLICKED)
			file_win_create(lv_scr_act()); //跳转到gauge窗体
	}
}

/**
 * @brief: 创建退出确认的消息对话框
 * @version: 1.0
 * @Date: 2021-04-23 17:34:52
 * @param {lv_obj_t} *parent
 */
void quit_mbox_create(lv_obj_t *parent)
{
	if (quit_mbox) //不要重复创建
		return;
	quit_mbox = lv_mbox_create(parent, NULL);
	lv_obj_set_size(quit_mbox, lv_obj_get_width(parent) * 0.7f, lv_obj_get_height(parent) / 2);
	lv_mbox_set_text(quit_mbox, "Tip\nAre you to quit?");
	lv_mbox_add_btns(quit_mbox, (const char **)MBOX_MAP);
	lv_obj_set_drag(quit_mbox, true); //设置对话框可以被拖拽
	lv_obj_align(quit_mbox, NULL, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_event_cb(quit_mbox, event_handler);
}

/**
 * @brief: 500ms任务回调函数:更新时间和占用率
 * @version: 1.0
 * @Date: 2021-04-23 17:34:33
 * @param {lv_task_t} *t
 */
static void progress_task(lv_task_t *t)
{
	char a[20];
	load = cpu_load_average();
	sprintf(a, "%.1f%%", load); 
	lv_label_set_text(clock_time, (char *)Time); //显示时间
	lv_label_set_text(cpu_load, (char *)a); //显示占用率
}

/**
 * @brief: 状态栏初始化:显示时间和CPU占用率
 * @version: 1.0
 * @Date: 2021-04-23 17:34:08
 */
static void header_create(void)
{
	header = lv_cont_create(lv_disp_get_scr_act(NULL), NULL);
	lv_obj_set_width(header, lv_disp_get_hor_res(NULL));

	lv_obj_t *sym = lv_label_create(header, NULL);
	lv_label_set_text(sym, LV_SYMBOL_GPS LV_SYMBOL_WIFI LV_SYMBOL_BLUETOOTH LV_SYMBOL_VOLUME_MAX);
	lv_obj_align(sym, NULL, LV_ALIGN_IN_RIGHT_MID, -LV_DPI / 10, 0);

	clock_time = lv_label_create(header, NULL);
	lv_label_set_text(clock_time, (char *)Time); //显示时间
	lv_obj_align(clock_time, NULL, LV_ALIGN_IN_LEFT_MID, LV_DPI / 10, 0);

	cpu_load = lv_label_create(header, NULL);
	lv_label_set_text(cpu_load, 0); //显示CPU使用率
	lv_obj_align(cpu_load, NULL, LV_ALIGN_CENTER, LV_DPI / 10 - 10, 0);

	lv_cont_set_fit2(header, LV_FIT_NONE, LV_FIT_TIGHT); /*Let the height set automatically*/
	lv_obj_set_pos(header, 0, 0);

	if (task == NULL)
		task = lv_task_create(progress_task, 500, LV_TASK_PRIO_HIGH, NULL);
}

/**
 * @brief: 首页选项卡初始化
 * @version: 1.0
 * @Date: 2021-04-23 17:33:18
 * @param {lv_obj_t} *parent
 */
void home_tab_init(lv_obj_t *parent)
{
	//创建列表
	lv_obj_t *list = lv_list_create(parent, NULL);
	lv_obj_set_size(list, lv_obj_get_width(parent) * 0.9f, lv_obj_get_height(parent) - 40);
	lv_obj_align(list, NULL, LV_ALIGN_CENTER, 0, 15);
	lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);

	//添加列表项1:日历
	calendar_item_btn = lv_list_add_btn(list, &date_img, "#FFFFFF Calendar#\n#666666 This is the date#");
	lv_obj_t *item_label = lv_list_get_btn_label(calendar_item_btn);
	lv_label_set_recolor(item_label, true);
	lv_obj_set_event_cb(calendar_item_btn, event_handler); //设置事件回调函数

	//添加列表项2:时钟
	progress_item_btn = lv_list_add_btn(list, &progress_img, "#FFFFFF Clock#\n#666666 This is the time#");
	item_label = lv_list_get_btn_label(progress_item_btn);
	lv_label_set_recolor(item_label, true);
	lv_obj_set_event_cb(progress_item_btn, event_handler); //设置事件回调函数

	//添加列表项3:图表
	chart_item_btn = lv_list_add_btn(list, &chart_img, "#FFFFFF Chart#\n#666666 This is the chart#");
	item_label = lv_list_get_btn_label(chart_item_btn);
	lv_label_set_recolor(item_label, true);
	lv_obj_set_event_cb(chart_item_btn, event_handler); //设置事件回调函数

	//添加列表项4:仪表
	gauge_item_btn = lv_list_add_btn(list, &gauge_img, "#FFFFFF Gauge#\n#666666 This is the Gauge#");
	item_label = lv_list_get_btn_label(gauge_item_btn);
	lv_label_set_recolor(item_label, true);
	lv_obj_set_event_cb(gauge_item_btn, event_handler); //设置事件回调函数

	//添加列表项5:文件
	file_item_btn = lv_list_add_btn(list, &file_img, "#FFFFFF File#\n#666666 This is the File#");
	item_label = lv_list_get_btn_label(file_item_btn);
	lv_label_set_recolor(item_label, true);
	lv_obj_set_event_cb(file_item_btn, event_handler); //设置事件回调函数
}

/**
 * @brief: 设置选项卡初始化
 * @version: 1.0
 * @Date: 2021-04-23 17:33:41
 * @param {lv_obj_t} *parent
 */
void setting_tab_init(lv_obj_t *parent)
{
	uint16_t parent_width = lv_obj_get_width(parent); //获取父对象的宽度

	//创建一个表格
	lv_obj_t *table = lv_table_create(parent, NULL);
	lv_table_set_col_cnt(table, TABLE_COL_CNT); //设置列数
	lv_table_set_row_cnt(table, TABLE_ROW_CNT); //设置行数
	uint8_t row, col;
	for (col = 0; col < TABLE_COL_CNT; col++)
	{
		lv_table_set_col_width(table, col, parent_width * (0.8f / TABLE_COL_CNT)); //设置列的宽度
		lv_table_set_cell_align(table, 0, col, LV_LABEL_ALIGN_CENTER);			   //标题行的文本居中对齐
	}
	for (row = 0; row < TABLE_ROW_CNT; row++)
	{
		for (col = 0; col < TABLE_COL_CNT; col++)
			lv_table_set_cell_value(table, row, col, (const char *)TABLE_CELL_VALUE[row][col]); //设置每一个单元格的文本内容
	}
	lv_obj_align(table, NULL, LV_ALIGN_CENTER, 0, 10); //设置表格的对齐方式

	//显示标题
	static lv_style_t title_style;
	lv_obj_t *label1 = lv_label_create(parent,NULL);
	lv_label_set_long_mode(label1,LV_LABEL_LONG_BREAK);//设置长文本模式
	lv_obj_set_width(label1,239);//设置宽度
	lv_label_set_align(label1,LV_LABEL_ALIGN_CENTER);//设置文本居中对齐
	lv_label_set_body_draw(label1,true);//使能背景重绘
	lv_obj_align(label1,table,LV_ALIGN_OUT_TOP_MID,0,-20);//设置对齐方式

	lv_style_copy(&title_style, lv_obj_get_style(label1));	
	title_style.text.font = &lv_font_roboto_22;													//改变字体
	lv_label_set_style(label1, LV_LABEL_STYLE_MAIN, &title_style);	
	lv_label_set_text(label1,"#FFFF00 Data recording analyzer#");//设置文本
	lv_label_set_recolor(label1,true);//使能文本重绘色

	//创建一个退出按钮
	quit_btn = lv_btn_create(parent, NULL);
	lv_obj_set_width(quit_btn, parent_width / 2);
	lv_obj_align(quit_btn, table, LV_ALIGN_OUT_BOTTOM_MID, 0, 30);
	lv_obj_t *quit_label = lv_label_create(quit_btn, NULL);
	lv_label_set_recolor(quit_label, true);
	lv_label_set_text(quit_label, "#FF0000 Quit#");
	lv_obj_set_event_cb(quit_btn, event_handler);
}

/**
 * @brief: 创建主界面
 * @version: 1.0
 * @Date: 2021-04-23 17:33:58
 * @param {lv_obj_t} *parent
 */
void main_win_create(lv_obj_t *parent)
{
	//为了减少复杂性,我们这里就直接把tabview作为main_win窗体了

	main_win = lv_tabview_create(parent, NULL);
	lv_tabview_set_btns_pos(main_win, LV_TABVIEW_BTNS_POS_BOTTOM); //选项卡按钮位于底部
																   //添加tab1选项卡
	lv_obj_t *home_tab = lv_tabview_add_tab(main_win, LV_SYMBOL_HOME " Home");
	home_tab_init(home_tab);
	//添加tab1选项卡
	lv_obj_t *setting_tab = lv_tabview_add_tab(main_win, LV_SYMBOL_SETTINGS " Setting");
	setting_tab_init(setting_tab);
	header_create();
}
