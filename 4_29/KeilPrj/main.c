#include <reg51.h>


sbit P1_0 = P1^0;   // ����P1.0����

void Timer() interrupt 3 {
    P1_0 = !P1_0;    // ��ת��ƽ״̬
    
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
    
    TF1 = 0;         // ����жϱ�־
}

void main(void) 
{
    TMOD = 0x10;     // ����T1Ϊģʽ1
    TH1 = 0x00;      
    TL1 = 0x00;
    ET1 = 1;         // ����T1�ж�
    EA = 1;          // ȫ���ж�ʹ��
    TR1 = 1;         // ������ʱ��
    P1_0 = 1;        // ��ʼ����ߵ�ƽ
    
    while(1);        // ��ѭ���ȴ�
}


