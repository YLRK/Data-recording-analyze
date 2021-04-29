#include "login_win.h"
#include "app.h"
#include "main_win.h"
#include <string.h>

//宏定义
#define LOGIN_PHONE "123"	//登录手机号
#define LOGIN_PASSWORD "a" //登录密码

//变量定义
static lv_obj_t *login_win = NULL;
static lv_obj_t *phone_ta = NULL;
static lv_obj_t *password_ta = NULL;
static lv_obj_t *kb = NULL;
static lv_obj_t *login_btn = NULL;

//申明
LV_IMG_DECLARE(weixin_img); //图片申明
void kb_create(lv_obj_t *bind_ta);

/**
 * @brief: 事件回调函数
 * @version: 1.0
 * @Date: 2021-04-24 17:05:26
 * @param {lv_obj_t} *obj
 * @param {lv_event_t} event
 */
static void event_handler(lv_obj_t *obj, lv_event_t event)
{
	if (obj == phone_ta || obj == password_ta)
	{
		if (event == LV_EVENT_RELEASED) //松手事件
		{
			lv_ta_set_cursor_type(phone_ta, LV_CURSOR_LINE | LV_CURSOR_HIDDEN);	   //先隐藏光标
			lv_ta_set_cursor_type(password_ta, LV_CURSOR_LINE | LV_CURSOR_HIDDEN); //先隐藏光标
			kb_create(obj);														   //弹出键盘
		}
	}
	else if (obj == kb)
	{
		lv_kb_def_event_cb(kb, event);							 //调用键盘的默认事件回调函数
		if (event == LV_EVENT_APPLY || event == LV_EVENT_CANCEL) //点击了键盘上的√或者×按键
		{
			lv_obj_del(kb); //删除键盘
			kb = NULL;
		}
	}
	else if (obj == login_btn)
	{
		if (event == LV_EVENT_RELEASED)
		{
			const char *phone = lv_ta_get_text(phone_ta);		//获取输入的电话号码
			const char *password = lv_ta_get_text(password_ta); //获取输入的密码
			if ((strcmp(phone, LOGIN_PHONE) == 0) && (strcmp(password, LOGIN_PASSWORD) == 0))
			{
				//验证成功
				lv_obj_del(login_win); //删除整个登录窗体
				login_win = NULL;
				kb = NULL;
				main_win_create(lv_scr_act()); //跳转到主界面
			}
			else
			{
				//验证失败,弹出提示
				toast("#FF0000 Tip#\nPhone:" LOGIN_PHONE "\nPassword:" LOGIN_PASSWORD, 3000);
			}
		}
	}
}

/**
 * @brief: 创建键盘
 * @version: 1.0
 * @Date: 2021-04-24 17:05:35
 * @param {lv_obj_t} *bind_ta
 */
void kb_create(lv_obj_t *bind_ta)
{
	if (kb == NULL) //如果键盘不存在,则先创建键盘
	{
		kb = lv_kb_create(login_win, NULL);
		lv_kb_set_cursor_manage(kb, true);		//对光标进行管理
		lv_obj_set_event_cb(kb, event_handler); //设置事件回调函数
	}
	lv_kb_set_mode(kb, bind_ta == phone_ta ? LV_KB_MODE_NUM : LV_KB_MODE_TEXT); //如果绑定的是电话输入框,则弹出数字键盘,否则弹出文本键盘
	lv_kb_set_ta(kb, bind_ta);													//绑定输入框
}

/**
 * @brief: 创建登录窗体
 * @version: 1.0
 * @Date: 2021-04-24 17:05:40
 * @param {lv_obj_t} *parent
 */
void login_win_create(lv_obj_t *parent)
{
	uint16_t parent_width, parent_height;
	//获取父对象的宽和高
	parent_width = lv_obj_get_width(parent);
	parent_height = lv_obj_get_height(parent);

	login_win = lv_page_create(parent, NULL);				 //用容器来模拟窗体
	lv_obj_set_size(login_win, parent_width, parent_height); //设置窗体的大小
	lv_page_set_sb_mode(login_win, LV_SB_MODE_AUTO);				 //设置滚动条的模式为自动
	lv_page_set_edge_flash(login_win, true);						 //使能边缘半圆弧动画效果
	lv_page_set_style(login_win, LV_PAGE_STYLE_SCRL, &lv_style_transp_tight);		   //设置scrl容器的样式为透明

	//创建一个标题
	lv_obj_t *title_label = lv_label_create(login_win, NULL);
	lv_label_set_recolor(title_label, true);							//使能文本重绘色功能
	lv_label_set_text(title_label, "#ff0000 Lo##0000ff g##00ff00 in#"); //设置"Login"标题
	lv_obj_align(title_label, NULL, LV_ALIGN_IN_TOP_MID, 0, 10);		//设置对齐方式
	//创建一个logo图片
	lv_obj_t *logo_img = lv_img_create(login_win, NULL);
	lv_img_set_src(logo_img, &weixin_img);								 //设置图片源
	lv_obj_align(logo_img, title_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20); //设置对齐方式
	//创建一个手机号输入框
	phone_ta = lv_ta_create(login_win, NULL);
	lv_obj_set_size(phone_ta, parent_width * 0.7f, 30);				  //设置大小
	lv_obj_align(phone_ta, logo_img, LV_ALIGN_OUT_BOTTOM_MID, 0, 20); //设置对齐方式
	lv_ta_set_text(phone_ta, "");									  //清空默认的文本内容
	lv_ta_set_placeholder_text(phone_ta, "Input phone");			  //设置placeholder提示文本
	lv_ta_set_one_line(phone_ta, true);								  //使能单行模式
	lv_obj_set_event_cb(phone_ta, event_handler);					  //设置事件回调函数
	//创建一个密码输入框
	password_ta = lv_ta_create(login_win, phone_ta); //从phone_ta上进行拷贝
	lv_ta_set_pwd_mode(password_ta, true);			 //使能密码保护模式
	lv_obj_align(password_ta, phone_ta, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
	lv_ta_set_cursor_type(password_ta, LV_CURSOR_LINE | LV_CURSOR_HIDDEN); //先隐藏光标
	lv_ta_set_placeholder_text(password_ta, "Input password");			   //设置placeholder提示文本
	//创建一个登陆按钮
	login_btn = lv_btn_create(login_win, NULL);
	lv_obj_set_size(login_btn, parent_width * 0.7f, 40);				  //设置大小
	lv_obj_align(login_btn, password_ta, LV_ALIGN_OUT_BOTTOM_MID, 0, 20); //设置对齐方式
	
	lv_obj_t *btn_label = lv_label_create(login_btn, NULL);
	lv_label_set_text(btn_label, "login");		   //设置按钮上的标题
	lv_obj_set_event_cb(login_btn, event_handler); //设置事件回调函数
}
