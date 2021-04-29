#ifndef __DHT22_H
#define __DHT22_H
 
#include "main.h"
#define DHT22_IO_IN()  {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=0<<(9*2);}	//PG9输入模式
#define DHT22_IO_OUT() {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=1<<(9*2);} 

//IO操作函数											   
#define	DHT22_DQ_OUT      PGout(9)//数据端口	PG9
#define	DHT22_DQ_IN   PGin(9) //数据端口	PG9 


// extern float temperature;
// extern float humidity;
extern float temperature_H;
extern float temperature_L;
extern float humidity_H;
extern float humidity_L;

int DHT22_Init(void); //Init DHT22
u8 DHT22_Read_Data(float *temperature,float *humidity); //Read DHT22 Value
u8 DHT22_Read_Byte(void);//Read One Byte
u8 DHT22_Read_Bit(void);//Read One Bit
u8 DHT22_Check(void);//Chack DHT22
void DHT22_Rst(void);//Reset DHT22    

void Warning(void);
void Amplitude_setting(u8 temp_up, u8 temp_low, u8 humi_up, u8 humi_low);

#endif


