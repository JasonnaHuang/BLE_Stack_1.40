#include "zlgAtCmd.h"
#include "npi.h"
#include "hal_gpio.h"
#include "OSAL.h"

#define CFG_CMD_NONVOLATILE     {0XAB,0XBC,0XCD}
#define CFG_CMD_VOLATILE        {0XDE,0XDF,0XEF}

#include "bcomdef.h"

const unsigned char broadcastAddr[2] = {0xff,0xff};
static unsigned char wbuf[255],rbuf[255];

/*enum nvparamoptcmd{
    enReadLoacalCfg = 0xd1,
    enSetChannelNv = 0xd2,
    enSearchNode = 0xd4,
    enGetRemoteInfo = 0xd5,
    enModifyCfg = 0xd6,
    enResetNode = 0xd9,
    enResetCfg = 0xda
};


enum temporaryparamoptcmd{
    enSetChannel = 0xd1,
    enSetDestAddr = 0xd2,
    enShowSrcAddr = 0xd3,
    enSetIoDirection = 0xd4,
    enReadIoStatus = 0xd5,
    enSetIoStatus = 0xd6,
    enReadAdcValue = 0xd7,
    enEnterSleepMode = 0xd8,
    enSetUnicastOrBroadcast = 0xd9,
    enReadNodeRssi = 0xda
};*/

/*struct dev_info{
    unsigned char devName[16];
    unsigned char devPwd[16];
    unsigned char devMode;
    unsigned char devChannel;
    unsigned char devPanid[2];
    unsigned char devLoacalNetAddr[2];
    unsigned char devLoacalIEEEAddr[8];
    unsigned char devDestNetAddr[2];
    unsigned char devDestIEEEAddr[8];
    unsigned char devReserve1;
    unsigned char devPowerLevel;
    unsigned char devRetryNum;
    unsigned char devTranTimeout;       // *10ms
    unsigned char devSerialRate;
    unsigned char devSerialDataB;
    unsigned char devSerialStopB;
    unsigned char devSerialParityB;
    unsigned char devReserve2;
};*/

struct dev_info stDevInfo;
#define UART_WRITE_BUF_LEN      100
#define UART_READ_BUF_LEN      100
//static unsigned char wbuf[100], rbuf[100];

void init_zigbee_zm516x(uint8 task_id, uint8 event)
{
        HalGpioSet(HAL_GPIO_ZM516X_ALL,1);
        HalGpioSet(HAL_GPIO_ZM516X_DEF,0);
        HalGpioSet(HAL_GPIO_ZM516X_RESET,0);
        osal_start_timerEx( task_id, event, 100 );
}

void read_local_cfg(void)
{
    wbuf[0] = 0xab;
    wbuf[1] = 0xbc;
    wbuf[2] = 0xcd;
    wbuf[3] = enReadLoacalCfg;
    wbuf[4] = wbuf[0] + wbuf[1] + wbuf[2] + wbuf[3];
    NPI_WriteTransport(wbuf, 5);
}

void write_local_cfg(void)
{
#if 0
    int i,len = 0;
    unsigned char sum = 0;
    unsigned char buf[100],responsebuf[10];

    buf[0] = 0xab;
    buf[1] = 0xbc;
    buf[2] = 0xcd;
    buf[3] = enModifyCfg;
    buf[4] = stDevInfo.devLoacalNetAddr[0];
    buf[5] = stDevInfo.devLoacalNetAddr[1];
    memset(stDevInfo.devLoacalNetAddr,0,2);
    stDevInfo.devChannel = 0x19;
    stDevInfo.devPanid[0] = 0x10;
    stDevInfo.devPanid[1] = 0x01;
    memcpy(&buf[6],&stDevInfo,65);

    for(i = 0;i < (6 + 65);i++)
    {
        sum += buf[i];
    }
    buf[6 + 65] = sum;

    while(len != 7)
    {
        WriteComPort(buf, 6 + 65 + 1);
        usleep(10000);
        len = ReadComPort(responsebuf,10);
    }
    usleep(100000);
    reset_zm516x();
    usleep(100000);
    printf("write local config sucesuss\r\n");
#endif
}

void send_data_to_remote_node(unsigned char *destAddr,unsigned char *data,int len)
{
#if 0
    unsigned char responslen = 0;
    unsigned char buf[10],responsebuf[10];

    if(memcmp(destAddr,broadcastAddr,2) == 0)
    {
        buf[0] = 0xde;
        buf[1] = 0xdf;
        buf[2] = 0xef;
        buf[3] = enSetUnicastOrBroadcast;
        buf[4] = 0x01;
        printf("Send broadcast\r\n");
        while(responslen != 7)
        {
            WriteComPort(buf, 5);
            usleep(10000);
            responslen = ReadComPort(responsebuf,10);

        }
    }
    else
    {
        buf[0] = 0xde;
        buf[1] = 0xdf;
        buf[2] = 0xef;
        buf[3] = enSetDestAddr;
        memcpy(&buf[4],destAddr,2);
        printf("Send unicast\r\n");
        while(responslen != 5)
        {
            WriteComPort(buf,6);
            usleep(10000);
            responslen = ReadComPort(responsebuf,10);
        }
    }
    WriteComPort(data, len);
    printf("Send over \r\n");
#endif
}

void UartReceiveData(uint8 port, uint8 event)
{
    VOID    port;
    uint8 temp;
/*
    if(event & HAL_UART_RX_TIMEOUT)    //接收完成事件
    {
        temp = NPI_RxBufLen();
        if(temp)
        {
            NPI_ReadTransport(uartbuf, temp);
            NPI_WriteTransport(uartbuf, temp);
            osal_memset(uartbuf, 0, sizeof(uartbuf));
        }
    }*/
    
    VOID  event;
    temp = NPI_RxBufLen();
    if(temp)
    {
        NPI_ReadTransport(rbuf, temp);
    }
}