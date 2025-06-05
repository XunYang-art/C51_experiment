#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
//假定某1位密码锁的功能是：用16个按键分别代表字符0~9和A~F，开锁密码为字符7；系统上电后LED灯灭（代表上锁），
//数码管显示闪烁“8”，约1s后改为“-”（待机状态）；单击按键表示输入一位密码，若密码输入正确，则显示“P”，LED灯亮（代表开锁），
//持续约3s后自动进入待机状态（表示过期自动上锁）；否则显示“E”，LED灯保持灯灭（表示开锁错误），持续约3s后自动进入待机状态。如此反复无限循环。



sbit LED = P3^0;

// 数码管段码 (共阴极)：0-9, A-F, '-', 'P', 'E', '8'
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
    0x40, // '-' (位置16)
    0x73, // P (位置17)
    0x79  // E (位置18)
};

// 延时函数（ms）
void delay_ms(uint ms) 
{
    uint i, j;
    for(i=0; i<ms; i++)
    {
        for(j=0; j<123; j++);
    }
}

// 数码管显示
void display(uchar index) 
{
    P0 = seg_code[index];
}


// 矩阵键盘扫描
uchar key_scan() 
{
    uchar row, col, key_val;
    P2 = 0xF0; // 列高电平，行低电平
    if ((P2 & 0xF0) != 0xF0) 
    {
        delay_ms(20); // 防抖
        
        if ((P2 & 0xF0) != 0xF0) 
        {
            row = P2 & 0xF0;
            P2 = 0x0F; // 行高电平，列低电平
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
                case 0x7D: return 7;  // 7 (开锁)
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
    return 255; // 无按键
}

void main() {
    uchar key;
    P0 = 0x00;  // 数码管清零
    LED = 1;    // 灯灭（上锁状态

    while (1) {
        // 上电显示“8”闪烁
        display(8); // '8'
        delay_ms(500);
        display(16); // '-'
        delay_ms(500);

        // 显示待机状态 '-'
        display(16);

        // 等待按键
        while ((key = key_scan()) == 255);

        if (key == 7) 
        {
            // 正确密码“7”
            display(17); // 'P'
            LED = 0; // 灯亮
            delay_ms(3000);
        } 
        else 
        {
            // 错误密码
            display(18); // 'E'
            LED = 1; // 灯灭
            delay_ms(3000);
        }

        // 恢复待机
        display(16);
        LED = 1;
    }
}
