#include "spi.h"

SPI_HandleTypeDef SPI1_Handler;  //SPI1句柄

//以下是SPI模块的初始化代码，配置成主机模式
//SPI口初始化
//这里针是对SPI1的初始化
void SPI1_Init(void)
{
    SPI1_Handler.Instance = SPI1;                       //SPI1
    SPI1_Handler.Init.Mode = SPI_MODE_MASTER;           //设置SPI工作模式，设置为主模式
    SPI1_Handler.Init.Direction = SPI_DIRECTION_2LINES; //设置SPI单向或者双向的数据模式:SPI设置为双线模式
    SPI1_Handler.Init.DataSize = SPI_DATASIZE_8BIT;     //设置SPI的数据大小:SPI发送接收8位帧结构
    SPI1_Handler.Init.CLKPolarity = SPI_POLARITY_HIGH;  //串行同步时钟的空闲状态为高电平
    SPI1_Handler.Init.CLKPhase = SPI_PHASE_2EDGE;       //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
    SPI1_Handler.Init.NSS = SPI_NSS_SOFT;               //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
    SPI1_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256; //定义波特率预分频的值:波特率预分频值为256
    SPI1_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;      //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
    SPI1_Handler.Init.TIMode = SPI_TIMODE_DISABLE;      //关闭TI模式
    SPI1_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE; //关闭硬件CRC校验
    SPI1_Handler.Init.CRCPolynomial = 7;                //CRC值计算的多项式
    HAL_SPI_Init(&SPI1_Handler);//初始化

    __HAL_SPI_ENABLE(&SPI1_Handler);                    //使能SPI1

    SPI1_ReadWriteByte(0Xff);                           //启动传输
}

//SPI速度设置函数
//SPI速度=fAPB1/分频系数
//@ref SPI_BaudRate_Prescaler:SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
//fAPB1时钟一般为42Mhz：
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//判断有效性
    __HAL_SPI_DISABLE(&SPI1_Handler);            //关闭SPI
    SPI1_Handler.Instance->CR1 &= 0XFFC7;        //位3-5清零，用来设置波特率
    SPI1_Handler.Instance->CR1 |= SPI_BaudRatePrescaler; //设置SPI速度
    __HAL_SPI_ENABLE(&SPI1_Handler);             //使能SPI

}

//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 TxData)
{
    u8 Rxdata;
    HAL_SPI_TransmitReceive(&SPI1_Handler, &TxData, &Rxdata, 1, 1000);
    return Rxdata;          		    //返回收到的数据
}

