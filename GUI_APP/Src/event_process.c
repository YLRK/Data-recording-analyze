/* 
 * Change Logs: 
 * Date           Author       	Notes 
 * 2021-04-04     yangyong      the first version 
 */
//#include "logger_config.h"
#include "event_process.h"

//#define THREAD_PRIORITY      18
//#define THREAD_TIMESLICE     5

//ALIGN(RT_ALIGN_SIZE)
//static char event_process_thread_stack[1024];
//static struct rt_thread event_process_thread;

//static void event_process_thread_entry(void *param)
//{
//    rt_uint32_t e;
//	rt_uint8_t data_count = 0;
//	rt_uint8_t *buffer_ptr;
//	LCD_MsgTypeDef lcdmsg;
//	FLASHMEM_MsgTypeDef fmmsg;
//	KEY_EventTypeDef keyevent;
//	LOGGER_ConfigTypeDef last_logger_conf, cur_logger_conf;
//	SENSOR_DataTypeDef sensordata;
//	
//	/*Gets the system configuration parameters*/
//	get_config(&last_logger_conf);
//	/*Request buffer*/
//	buffer_ptr = rt_mp_alloc(mempool, RT_WAITING_FOREVER);
//	
//	while(1){
//		if(rt_event_recv(&system_event, (EVENT_KEY | EVENT_SENSOR | EVENT_CONFIG),
//                         RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR,
//                         RT_WAITING_FOREVER, &e) == RT_EOK)
//		{
//			if(e & EVENT_KEY){
//				while(rt_mq_recv(key_mq, &keyevent, sizeof(keyevent), RT_WAITING_NO) == RT_EOK)
//				{
//					/*Use the key to control the LCD display content*/
//					lcdmsg.menu = keyevent.value;
//					lcdmsg.temperature = 66;
//					lcdmsg.humidity = 88;
//					rt_mq_send(lcd_mq, &lcdmsg, sizeof(lcdmsg));
//				}
//			}
//				
//			if(e & EVENT_SENSOR){
//				while(rt_mq_recv(sensor_mq, &sensordata, sizeof(sensordata), RT_WAITING_NO) == RT_EOK)
//				{
//					/*Determine whether the sensor data exceeds the upper and lower limits*/
//					if(sensordata.temperature>=last_logger_conf.temp_upper 
//						|| sensordata.temperature<=last_logger_conf.temp_lower
//						|| sensordata.humidity>=last_logger_conf.humi_upper 
//					    || sensordata.humidity<=last_logger_conf.humi_lower)
//					{
//						//turn on alarm
//					}else{
//						//turn off alarm
//					}
//					
//					/*collect sensor data and send sensor data buffer to flashmem_process task*/
//					if(data_count < 100){
//						buffer_ptr[data_count++] = sensordata.temperature;
//						buffer_ptr[data_count++] = sensordata.humidity;
//						if(data_count == 100){
//							fmmsg.operation = 1;//write data to FlashMemory
//							fmmsg.ptr = buffer_ptr;
//							fmmsg.size = 100;   //100 bytes
//							rt_mq_send(flashmem_mq, &fmmsg, sizeof(fmmsg));//send buffer to flashmem_process task
//							buffer_ptr = rt_mp_alloc(mempool, RT_WAITING_FOREVER);//Request buffer
//							data_count = 0;	
//						}
//					}
//					
//					/*send sensor data to lcd_process task*/
//					lcdmsg.menu = 3;
//					lcdmsg.temperature = sensordata.temperature;
//					lcdmsg.humidity = sensordata.humidity;
//					rt_mq_send(lcd_mq, &lcdmsg, sizeof(lcdmsg));
//				}	
//			}

//			if(e & EVENT_CONFIG){
//				/*Gets the system configuration parameters*/
//				get_config(&cur_logger_conf);
//				/*Determines whether to modify the sensor data reading cycle*/
//				if(cur_logger_conf.sensor_period != last_logger_conf.sensor_period){
//					rt_timer_stop(sensor_timer);
//					sensor_timer_init(cur_logger_conf.sensor_period); 
//					rt_timer_start(sensor_timer);
//				}
//				
//				/*Determines whether to start or pause the sensor data reading operation*/
//				if(cur_logger_conf.sensor_pause != last_logger_conf.sensor_pause){
//					if(cur_logger_conf.sensor_pause == 1){
//						rt_timer_start(sensor_timer);
//					}else{
//						rt_timer_stop(sensor_timer);
//					}
//				}
//				
//				last_logger_conf = cur_logger_conf;
//			}				
//		}
//	}//while(1)
//}

//int event_process_init(void)
//{
//    rt_thread_init(&event_process_thread,
//                   "EventProcess",
//                   event_process_thread_entry,
//                   RT_NULL,
//                   &event_process_thread_stack[0],
//                   sizeof(event_process_thread_stack),
//                   THREAD_PRIORITY - 1, THREAD_TIMESLICE);
//    rt_thread_startup(&event_process_thread);

//    return 0;
//}
