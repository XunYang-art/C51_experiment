#include <reg51.h>



void delay_ms(unsigned int ms)
{
    unsigned int i,j;
    for(i=0;i<ms;i++)
    {
        for(j=0;j<125;j++)
        {
        
        
        }
    
    }
        
}

unsigned char LED_BUF[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void main(void)
{
    unsigned int i;
    while(1)
    {
        for(i=0;i<8;i++)
        {
            P0 = LED_BUF[i];
            delay_ms(1000);
        }
    }
}
