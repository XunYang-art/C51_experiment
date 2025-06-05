#include <reg51.h>

void delay_ms() {
    unsigned int i, j;
    for(i = 0; i < 500; i++)
        for(j = 0; j < 120; j++);
}

// 外部中断0服务函数
void exti0_function() interrupt 0 {
    unsigned char i;
    for(i = 0; i < 5; i++) 
    {
        P1 = 0xF0;
        delay_ms();
        P1 = 0x0F;
        delay_ms();
    }
    
    P1 = 0x00;     

}

void main() {
    IT0 = 0;    // 设置外部中断0为电平触发
    EX0 = 1;    // 允许外部中断0
    EA = 1;     // 开启总中断
    P1 = 0x00;  // P1口初始化，LED全亮

    while(1);   // 主循环等待中断
}

