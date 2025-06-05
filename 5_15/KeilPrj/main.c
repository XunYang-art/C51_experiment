#include <reg51.h>   

sbit START_SW = P3^0;  // ��������(P3.0)
sbit FAULT_SW = P3^2;  // ���Ͽ���(P3.2)
sbit ALARM_OUT = P3^7; // �������(P3.7)
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

// ����������
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
    
    IT0 = 0;// �����ⲿ�ж�0Ϊ��ƽ����
    EX0 = 1;    // �����ⲿ�ж�0
    EA = 1;// �������ж�
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

        // ��λ����ʼ״̬
        P1 = 0xFF;
    }
}
