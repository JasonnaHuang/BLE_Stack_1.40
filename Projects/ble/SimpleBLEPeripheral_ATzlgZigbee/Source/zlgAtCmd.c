#include "zlgAtCmd.h"
#include "npi.h"
#include "hal_gpio.h"
#include "OSAL.h"

#define CFG_CMD_NONVOLATILE     {0XAB,0XBC,0XCD}
#define CFG_CMD_VOLATILE        {0XDE,0XDF,0XEF}

#include "bcomdef.h"

#define UART_WRITE_BUF_LEN      100
#define UART_READ_BUF_LEN      100

const unsigned char broadcastAddr[2] = {0xff,0xff};
static unsigned char wbuf[UART_WRITE_BUF_LEN],rbuf[UART_READ_BUF_LEN];

struct dev_info stDevInfo;

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
    uint8   len;
/*
    if(event & UART_RECEIVE_EVT)    //接收完成事件
    {
        len = NPI_RxBufLen();
        osal_memset(rbuf,0,UART_READ_BUF_LEN);
        if(len)
        {
            NPI_ReadTransport(rbuf, len);
        }
    }*/
    len = NPI_RxBufLen();
    osal_memset(rbuf,0,UART_READ_BUF_LEN);
    if(len)
    {
        NPI_ReadTransport(rbuf, len);
    }
}
