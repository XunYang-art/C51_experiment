#include <reg51.h>

#define LED P1      // ����P1��ΪLED��


void delay(void)
{
    int i,j;
    for(i=0;i<500;i++)
    {
        for(j=0;j<125;j++);
    }

}
// ���г�ʼ������
void SerialInit() 
{
    TMOD = 0x20;     // ��ʱ��1��������ģʽ2��8λ�Զ�����ģʽ��
    TH1 = 0xFD;      // ���ò�����Ϊ9600
    TL1 = 0xFD;
    TR1 = 1;         // ������ʱ��1
    SM0 = 0;
    SM1 = 1;         // ���ô��п�Ϊ������ģʽ1
    REN = 1;         // ʹ�ܴ��н���
}

// �������ݺ���
void SerialSend(unsigned char i) 
{
    SBUF = i;    // �����ݼ��ص����ͻ�����
    while (TI == 0); // �ȴ��������
    TI = 0;          // ������ͱ�־
}

// �������ݺ���
unsigned char SerialReceive() 
{
    while (RI == 0); // �ȴ��������
    RI = 0;          // ������ձ�־
    return SBUF;     // ���ؽ��յ�������
}

// ������
void main(void) 
{
    unsigned char receivedData;
    
    SerialInit();    // ��ʼ�����п�

    while (1) 
    {
        // �������Ե�Ƭ��A������
        receivedData = SerialReceive();
        
        // �����յ���������ʾ��LED��
        LED = receivedData;
        
        // ������յ�0x55������0x41�ص�Ƭ��A
        if (receivedData == 0x55) 
        {
            //delay();
            LED=0x41;
            SerialSend(0x41);
        }
    }
}


