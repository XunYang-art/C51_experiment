#include <reg51.h>

#define LED P1      // 定义P1口为LED口


void delay(void)
{
    int i,j;
    for(i=0;i<500;i++)
    {
        for(j=0;j<125;j++);
    }

}
// 串行初始化函数
void SerialInit() 
{
    TMOD = 0x20;     // 定时器1，工作在模式2（8位自动重载模式）
    TH1 = 0xFD;      // 设置波特率为9600
    TL1 = 0xFD;
    TR1 = 1;         // 启动定时器1
    SM0 = 0;
    SM1 = 1;         // 设置串行口为工作在模式1
    REN = 1;         // 使能串行接收
}

// 发送数据函数
void SerialSend(unsigned char i) 
{
    SBUF = i;    // 将数据加载到发送缓冲区
    while (TI == 0); // 等待发送完成
    TI = 0;          // 清除发送标志
}

// 接收数据函数
unsigned char SerialReceive() 
{
    while (RI == 0); // 等待接收完成
    RI = 0;          // 清除接收标志
    return SBUF;     // 返回接收到的数据
}

// 主函数
void main(void) 
{
    unsigned char receivedData;
    
    SerialInit();    // 初始化串行口

    while (1) 
    {
        // 接收来自单片机A的数据
        receivedData = SerialReceive();
        
        // 将接收到的数据显示在LED上
        LED = receivedData;
        
        // 如果接收到0x55，发送0x41回单片机A
        if (receivedData == 0x55) 
        {
            //delay();
            LED=0x41;
            SerialSend(0x41);
        }
    }
}


