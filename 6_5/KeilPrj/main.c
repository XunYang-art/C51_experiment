#include <reg51.h>
#include <intrins.h>

#define uchar unsigned char
    
sbit    EN = P1^5;
sbit    RW = P1^6;
sbit    RS = P1^7;
sbit    DOUT = P3^0;
sbit    SCLK = P3^1;
sbit    CS = P3^2;
sbit    SHDN = P3^4;

uchar buff1[] = {"current adc1241:"};
uchar buff2[12];

void fbusy(void)
{
    P2 = 0XFF;
    RS = 0;
    RW = 1;
    EN = 1;
    EN = 0;
    while((P2 & 0X80))
    {
        EN = 0;
        EN = 1;
    }
}

void wc51r(uchar j)
{
    fbusy();
    EN = 0;
    RS = 0;
    RW = 0;
    EN = 1;
    P2 = j;
    EN = 0;
}


void wc51ddr(uchar j)
{
    fbusy();
    EN = 0;
    RS = 1;
    RW = 0;
    EN = 1;
    P2 = j;
    EN = 0;
}

void init(void)
{
    wc51r(0x01);
    wc51r(0x38);
    wc51r(0x0c);
    wc51r(0x06);
}

void adc(void)
{
    uchar i ;
    SHDN = 1;
    SCLK = 0;
    CS = 0;
    while(!DOUT)
    {
        ;
    }
    SCLK = 1;
    for(i = 0;i < 12; i++)
    {
        SCLK = 0;
        _nop_();
        SCLK = 1;
        if(DOUT)
        {
            buff2[i] = 0x31;
        }
        else
        {
            buff2[i] = 0x30;
        }
    }
    
    CS = 1;
    SHDN = 0;
}

void main(void)
{
    uchar k;
    SP = 0X50;
    EA = 0;
    init();
    wc51r(0x80);
    
    for(k = 0; k < 16; k++)
    {
        wc51ddr(buff1[k]);
    }
    
    
    while(1)
    {
        adc();
        wc51r(0xc2);
        
        for(k = 0; k < 12;k++)
        {
            wc51ddr(buff2[k]);
        }
        
    }
}


