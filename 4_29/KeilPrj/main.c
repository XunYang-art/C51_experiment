#include <reg51.h>


sbit P1_0 = P1^0;   // 定义P1.0引脚

void Timer() interrupt 3 {
    P1_0 = !P1_0;    // 翻转电平状态
    
    if (P1_0 == 0) 
    {
        TH1 = 0x00;    
        TL1 = 0x00;
    } 
    else 
    {
        TH1 = 0x00;  
        TL1 = 0x00;
    }
    
    TF1 = 0;         // 清除中断标志
}

void main(void) 
{
    TMOD = 0x10;     // 设置T1为模式1
    TH1 = 0x00;      
    TL1 = 0x00;
    ET1 = 1;         // 允许T1中断
    EA = 1;          // 全局中断使能
    TR1 = 1;         // 启动定时器
    P1_0 = 1;        // 初始输出高电平
    
    while(1);        // 主循环等待
}


