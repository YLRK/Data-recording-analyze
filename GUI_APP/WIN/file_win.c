/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-23 17:41:58
 * @LastEditTime: 2021-04-24 17:06:36
 */
#include "file_win.h"
#include <dfs_posix.h> /* 当需要使用文件操作时，需要包含这个头文件 */
#include "app.h"
DIR *dirp;
struct dirent *dp;
static lv_task_t * task = NULL;
static 	lv_obj_t *item_label;
static lv_obj_t *file_btn; //时间日期设置roller
char path[100];
static void dirn_win_create(lv_obj_t * parent);
static void text_win_create(lv_obj_t * parent);
static void event_handler(lv_obj_t * obj,lv_event_t event)
{
	if(event==USER_EVENT_BACK)//窗体返回事件,点击左上角的"< Back"按钮会触发此事件
	{
		if(task)//删除掉任务
		{
			lv_task_del(task);
			task = NULL;
		}
	}
	if(event==LV_EVENT_CLICKED) 
	{ 
		sprintf(path,"/sdcard/%s",lv_list_get_btn_text(obj));
		dirp = opendir(path);
		dirn_win_create(lv_scr_act());
	}
}

static void event_handler1(lv_obj_t * obj,lv_event_t event)
{
	if(event==USER_EVENT_BACK)//窗体返回事件,点击左上角的"< Back"按钮会触发此事件
	{
		if(task)//删除掉任务
		{
			lv_task_del(task);
			task = NULL;
		}
	}
	if(event==LV_EVENT_CLICKED) 
	{ 
		sprintf(path,"%s/%s",path,lv_list_get_btn_text(obj));
		text_win_create(lv_scr_act());
	}
}

static void event_handler2(lv_obj_t * obj,lv_event_t event)
{
	if(event==USER_EVENT_BACK)//窗体返回事件,点击左上角的"< Back"按钮会触发此事件
	{
		if(task)//删除掉任务
		{
			lv_task_del(task);
			task = NULL;
		}
	}
}

/**
 * @brief: 文件夹列表创建
 * @version: 1.0
 * @Date: 2021-04-24 13:16:13
 * @param {lv_obj_t} *
 */
void file_win_create(lv_obj_t * parent)
{
    dirp = opendir("/sdcard");
	//创建列表
    lv_obj_t *win = general_win_create(parent, "Folder1");
	lv_obj_t *list = lv_list_create(win, NULL);
	lv_obj_set_size(list, lv_obj_get_width(parent)*0.9f , lv_obj_get_height(parent) - 40);
	lv_obj_align(list, NULL, LV_ALIGN_CENTER, 0, 15);
	lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
    for (dp = readdir(dirp); dp != RT_NULL; dp = readdir(dirp))
    {		
		file_btn = lv_list_add_btn(list, NULL, dp->d_name);
		item_label = lv_list_get_btn_label(file_btn);
		lv_label_set_recolor(item_label, true);
		lv_obj_set_event_cb(file_btn, event_handler); //设置事件回调函数
    }
	rt_kprintf("closedir\n");
	closedir(dirp);
}

/**
 * @brief: 子文件夹列表创建
 * @version: 1.0
 * @Date: 2021-04-24 13:16:36
 * @param {lv_obj_t} *
 */
static void dirn_win_create(lv_obj_t * parent)
{
    lv_obj_t *win = general_win_create(parent, "Folder2");
	lv_obj_t *list = lv_list_create(win, NULL);
	lv_obj_set_size(list, lv_obj_get_width(parent)*0.9f , lv_obj_get_height(parent) - 40);
	lv_obj_align(list, NULL, LV_ALIGN_CENTER, 0, 15);
	lv_list_set_sb_mode(list, LV_SB_MODE_AUTO);
    for (dp = readdir(dirp); dp != RT_NULL; dp = readdir(dirp))
    {		
		file_btn = lv_list_add_btn(list, NULL, dp->d_name);
		item_label = lv_list_get_btn_label(file_btn);
		lv_label_set_recolor(item_label, true);
		lv_obj_set_event_cb(file_btn, event_handler1); //设置事件回调函数
    }
	rt_kprintf("closedirn\n");
	closedir(dirp);
}

/**
 * @brief: 文件列表创建
 * @version: 1.0
 * @Date: 2021-04-24 13:16:47
 * @param {lv_obj_t} *
 */
static void text_win_create(lv_obj_t * parent) 
{ 
	int fd,size;
	static int writebuffer[1024];
    lv_obj_t *win = general_win_create(parent, "text");

	fd = open(path,O_RDONLY);
	size = read(fd, writebuffer, sizeof(writebuffer));
	close(fd);
	//1.创建文本域对象
	lv_obj_t *ta1 = lv_ta_create(win,NULL); 
	lv_obj_set_size(ta1,lv_obj_get_width(parent)*0.8f , lv_obj_get_height(parent) - 60);//设置文本域的大小
	lv_obj_align(ta1,NULL,LV_ALIGN_CENTER,0,0);//与屏幕居中对齐

	lv_ta_set_text(ta1,(char*)writebuffer);//设置文本内容
	
	//设置文本居左对齐 ,默认就是居左对齐
	lv_ta_set_text_align(ta1,LV_LABEL_ALIGN_LEFT); 
	lv_obj_set_event_cb(ta1,event_handler2);//设置事件回调函数
}




