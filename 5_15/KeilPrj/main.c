#include <reg51.h>   

sbit START_SW = P3^0;  // 启动开关(P3.0)
sbit FAULT_SW = P3^2;  // 故障开关(P3.2)
sbit ALARM_OUT = P3^7; // 报警输出(P3.7)
unsigned int i, j;

void delay() {
    unsigned int i, j;
    for(i = 0; i < 1000; i++) 
    {      
        for(j = 0; j < 125; j++) 
        { 
            
        }
    }
}

// 报警处理函数
void alarm_handler() interrupt 0
{
    P1 = 0xFF;          
    while(FAULT_SW == 0) 
    { 
        ALARM_OUT = ~ALARM_OUT; 
       
        
        for(i = 0; i < 1; i++) 
        {      
            for(j = 0; j < 125; j++) 
            { 
            
            }
        }
    }
    ALARM_OUT = 0;      
}



void main() {
    
    IT0 = 0;// 设置外部中断0为电平触发
    EX0 = 1;    // 允许外部中断0
    EA = 1;// 开启总中断
    P1 = 0xFF;
    ALARM_OUT = 0;       
    
    while(1) {
        
        if(START_SW == 0)
        {
            P1 = 0xFE;  
            delay();
           
            P1 = 0xFD; 
            delay();
            
            P1 = 0xFB;  
            delay();
           
            P1 = 0xF7; 
            delay();
            
            P1 = 0xEF;  
            delay();
            
            P1 = 0xDF;  
            delay();

            P1 = 0x0F;  
            delay();
        }

        // 复位到初始状态
        P1 = 0xFF;
    }
}
