#include <reg51.h>

void delay_ms() {
    unsigned int i, j;
    for(i = 0; i < 500; i++)
        for(j = 0; j < 120; j++);
}

// �ⲿ�ж�0������
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
    IT0 = 0;    // �����ⲿ�ж�0Ϊ��ƽ����
    EX0 = 1;    // �����ⲿ�ж�0
    EA = 1;     // �������ж�
    P1 = 0x00;  // P1�ڳ�ʼ����LEDȫ��

    while(1);   // ��ѭ���ȴ��ж�
}

