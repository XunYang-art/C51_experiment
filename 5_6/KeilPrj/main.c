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



void main(void)
{
    unsigned int i;
    TMOD=0X06;
    TH0=0XF6;
    TL0=0XF6;
    TR0=1;
    
    while(1)
    {
        if(TF0)
        {
            TF0=0;
            delay_ms(100);
        }
        i=TL0;
        i=i-0XF6;
        P1=i;
    }
}
