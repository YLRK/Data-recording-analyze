/*
 * @Descripttion: 
 * @version: 1.0
 * @Author: YLDS
 * @Date: 2021-04-03 22:42:51
 * @LastEditTime: 2021-04-23 09:55:33
 */
#ifndef __DS18B20_H
#define __DS18B20_H
#include "main.h"

//IO方向设置
#define DHT11_IO_IN()  {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=0<<(9*2);}	//PG9输入模式
#define DHT11_IO_OUT() {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=1<<(9*2);} 	//PG9输出模式
 
////IO操作函数											   
#define	DHT11_DQ_OUT    PGout(9)//数据端口	PG9
#define	DHT11_DQ_IN     PGin(9) //数据端口	PG9 


typedef struct
{
	rt_uint8_t sensor_pause; 
	rt_uint8_t sensor_period;
	rt_uint8_t temp_lower;
	rt_uint8_t temp_upper;
	rt_uint8_t humi_lower;
	rt_uint8_t humi_upper;	
}LOGGER_ConfigTypeDef;

typedef struct
{
	rt_uint8_t temperature;
	rt_uint8_t humidity;
}SENSOR_DataTypeDef;

extern u8 temperature_H;
extern u8 temperature_L;
extern u8 humidity_H;
extern u8 humidity_L;

void Amplitude_setting(u8 temp_up, u8 temp_low, u8 humi_up, u8 humi_low);
int DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11  
void Warning(void);
#endif
