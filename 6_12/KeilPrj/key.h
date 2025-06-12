#define uchar unsigned char
sbit E =P3^7;
sbit RW=P3^6;
sbit RS=P3^5;
void  wrcmd(uchar);
void  wrdata(uchar);
void init(void);
void delay(void);
void error(void);
unsigned long shi(uchar k);
void out(void);



void init(void)
{
wrcmd(0);
wrcmd(6);
wrcmd(0x0c);
wrcmd(0x38);
wrcmd(0x80);
}

void wrcmd(uchar A)
{
uchar m;
P3=0x1f;
E=1;
P1=A;
for(m=0;m<200;m++)
{;}
E=0;
}

void wrdata(uchar B)
{
    uchar m;
    P3=0x3f;
    E=1;
    P1=B;
    for(m=0;m<200;m++)
    {;}
    E=0;
}

void delay(void)
{
uchar m;
for(m=200;m>0;m--)
 {;}
}

void error(void)
{
uchar derror[8]="ERROR!!!";
uchar k;
for(k=0;k<=7;k++)
{
    wrcmd(0xc8+k);
    wrdata(derror[k]);
    delay();
}
}

void out(void)
{
    uchar k;
    uchar dout[12]="OUT OF RANGE";
    for(k=0;k<=11;k++)
    {
        wrcmd(0xc4+k);
        wrdata(dout[k]);
        delay();
    }
}

unsigned long shi(uchar n)
{
    int m=1;
    while(n!=0)
    {
        m=m*10;
        n--;
    }
    return(m);
}

