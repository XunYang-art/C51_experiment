#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
//�ٶ�ĳ1λ�������Ĺ����ǣ���16�������ֱ�����ַ�0~9��A~F����������Ϊ�ַ�7��ϵͳ�ϵ��LED���𣨴�����������
//�������ʾ��˸��8����Լ1s���Ϊ��-��������״̬��������������ʾ����һλ���룬������������ȷ������ʾ��P����LED����������������
//����Լ3s���Զ��������״̬����ʾ�����Զ���������������ʾ��E����LED�Ʊ��ֵ��𣨱�ʾ�������󣩣�����Լ3s���Զ��������״̬����˷�������ѭ����



sbit LED = P3^0;

// ����ܶ��� (������)��0-9, A-F, '-', 'P', 'E', '8'
uchar code seg_code[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F, // 9
    0x77, // A
    0x7C, // b
    0x39, // C
    0x5E, // d
    0x79, // E
    0x71, // F
    0x40, // '-' (λ��16)
    0x73, // P (λ��17)
    0x79  // E (λ��18)
};

// ��ʱ������ms��
void delay_ms(uint ms) 
{
    uint i, j;
    for(i=0; i<ms; i++)
    {
        for(j=0; j<123; j++);
    }
}

// �������ʾ
void display(uchar index) 
{
    P0 = seg_code[index];
}


// �������ɨ��
uchar key_scan() 
{
    uchar row, col, key_val;
    P2 = 0xF0; // �иߵ�ƽ���е͵�ƽ
    if ((P2 & 0xF0) != 0xF0) 
    {
        delay_ms(20); // ����
        
        if ((P2 & 0xF0) != 0xF0) 
        {
            row = P2 & 0xF0;
            P2 = 0x0F; // �иߵ�ƽ���е͵�ƽ
            col = P2 & 0x0F;

            key_val = row | col;

            switch (key_val) 
            {
                case 0xEE: return 0;  // 0
                case 0xDE: return 1;  // 1
                case 0xBE: return 2;  // 2
                case 0x7E: return 3;  // 3
                case 0xED: return 4;  // 4
                case 0xDD: return 5;  // 5
                case 0xBD: return 6;  // 6
                case 0x7D: return 7;  // 7 (����)
                case 0xEB: return 8;  // 8
                case 0xDB: return 9;  // 9
                case 0xBB: return 10; // A
                case 0x7B: return 11; // B
                case 0xE7: return 12; // C
                case 0xD7: return 13; // D
                case 0xB7: return 14; // E
                case 0x77: return 15; // F
                default: return 255;
            }
        }
    }
    return 255; // �ް���
}

void main() {
    uchar key;
    P0 = 0x00;  // ���������
    LED = 1;    // ��������״̬

    while (1) {
        // �ϵ���ʾ��8����˸
        display(8); // '8'
        delay_ms(500);
        display(16); // '-'
        delay_ms(500);

        // ��ʾ����״̬ '-'
        display(16);

        // �ȴ�����
        while ((key = key_scan()) == 255);

        if (key == 7) 
        {
            // ��ȷ���롰7��
            display(17); // 'P'
            LED = 0; // ����
            delay_ms(3000);
        } 
        else 
        {
            // ��������
            display(18); // 'E'
            LED = 1; // ����
            delay_ms(3000);
        }

        // �ָ�����
        display(16);
        LED = 1;
    }
}
