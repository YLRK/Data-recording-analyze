#include "sdio_sdcard.h"
#include "string.h"
#include <dfs_fs.h>
#include "drv_spi.h"
#include "spi_msd.h"
#include <dfs_posix.h> /* 当需要使用文件操作时，需要包含这个头文件 */
SD_HandleTypeDef        SDCARD_Handler;     //SD卡句柄
HAL_SD_CardInfoTypeDef  SDCardInfo;         //SD卡信息结构体
DMA_HandleTypeDef SDTxDMAHandler, SDRxDMAHandler;   //SD卡DMA发送和接收句柄

//SD_ReadDisk/SD_WriteDisk函数专用buf,当这两个函数的数据缓存区地址不是4字节对齐的时候,
//需要用到该数组,确保数据缓存区地址是4字节对齐的.
__align(4) u8 SDIO_DATA_BUFFER[512];

//得到卡信息
//cardinfo:卡信息存储区
//返回值:错误状态
u8 SD_GetCardInfo(HAL_SD_CardInfoTypeDef *cardinfo)
{
    u8 sta;
    sta = HAL_SD_GetCardInfo(&SDCARD_Handler, cardinfo);
    return sta;
}

//判断SD卡是否可以传输(读写)数据
//返回值:SD_TRANSFER_OK 传输完成，可以继续下一次传输
//		 SD_TRANSFER_BUSY SD卡正忙，不可以进行下一次传输
u8 SD_GetCardState(void)
{
    return((HAL_SD_GetCardState(&SDCARD_Handler) == HAL_SD_CARD_TRANSFER ) ? SD_TRANSFER_OK : SD_TRANSFER_BUSY);
}

//读SD卡
//buf:读数据缓存区
//sector:扇区地址
//cnt:扇区个数
//返回值:错误状态;0,正常;其他,错误代码;
u8 SD_ReadDisk(u8* buf, u32 sector, u32 cnt)
{
    u8 sta = HAL_OK;
    u32 timeout = SD_TIMEOUT;
    long long lsector = sector;
    INTX_DISABLE();//关闭总中断(POLLING模式,严禁中断打断SDIO读写操作!!!)
    sta = HAL_SD_ReadBlocks(&SDCARD_Handler, (uint8_t*)buf, lsector, cnt, SD_TIMEOUT); //多个sector的读操作

    //等待SD卡读完
    while(SD_GetCardState() != SD_TRANSFER_OK)
    {
        if(timeout-- == 0)
        {
            sta = SD_TRANSFER_BUSY;
        }
    }

    INTX_ENABLE();//开启总中断
    return sta;
}

//写SD卡
//buf:写数据缓存区
//sector:扇区地址
//cnt:扇区个数
//返回值:错误状态;0,正常;其他,错误代码;
u8 SD_WriteDisk(u8 *buf, u32 sector, u32 cnt)
{
    u8 sta = HAL_OK;
    u32 timeout = SD_TIMEOUT;
    long long lsector = sector;
    INTX_DISABLE();//关闭总中断(POLLING模式,严禁中断打断SDIO读写操作!!!)
    sta = HAL_SD_WriteBlocks(&SDCARD_Handler, (uint8_t*)buf, lsector, cnt, SD_TIMEOUT); //多个sector的写操作

    //等待SD卡写完
    while(SD_GetCardState() != SD_TRANSFER_OK)
    {
        if(timeout-- == 0)
        {
            sta = SD_TRANSFER_BUSY;
        }
    }

    INTX_ENABLE();//开启总中断
    return sta;
}

#define SDCARD_MOUNTPOINT "/sdcard"

/**
 * @brief: 挂载sd卡
 * @version: 1.0
 * @Date: 2021-04-24 17:07:41
 * @param {void} *parameter
 */
void sd_mount(void *parameter)
{
    int ret;
    ret = mkdir(SDCARD_MOUNTPOINT, 0x777);

    if(rt_device_find("sd0") != RT_NULL)
    {
        if (dfs_mount("sd0", SDCARD_MOUNTPOINT, "elm", 0, 0) == RT_EOK)
        {
            LOG_I("sd card mount success.\r\n");
        }
        else
        {
            LOG_W("sd card mount failed!\r\n");
        }
    }

    rt_thread_mdelay(500);
}

int stm32_sdcard_mount(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("sd_mount", sd_mount, RT_NULL,
                           1024, RT_THREAD_PRIORITY_MAX - 2, 20);

    if (tid != RT_NULL)
    {
        rt_thread_startup(tid);
    }
    else
    {
        LOG_E("create sd_mount thread err!");
    }

    return RT_EOK;
}
INIT_APP_EXPORT(stm32_sdcard_mount);
