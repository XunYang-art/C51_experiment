#include <reg51.h>
#include <key.h>

#define uchar unsigned char
    
uchar key;
uchar rrr=0xff;
uchar alldata[12]={0};
uchar love[14];
uchar exit=0,yes=0,kind=0,fu=0,pfu=0,position1=0,position2=0;
unsigned long  data1=0,data2=0,data3=0,ddata=0;

uchar Calcdone_flag = 0;

uchar keyscan(void);
void  display(uchar);
void  prodis(void);
void  clear(void);
void  datapc(void);
void remove0(void);
void  data3dis(void);

void main()
{
    init();
    while(1)
    {
        key=keyscan();
        delay();
        if(exit==1)
        {
            display(key);
        }
    }
}
////扫描键盘子程序/////
uchar keyscan()
{
uchar i=0,j=0;
P0=0xf0;
if(((~P0) & 0xf0)!=0)
{
 delay();
  if(((~P0) & 0xf0)!=0)
  {
    exit=1;
    P0=0xfe;
    while(((~P0) & 0x0f)!=0) 
   {
      if(((~P0) & 0xf0)!=0) 
      {
        switch((~P0) & 0xf0)
          {
          case 0x10:
          j=0;break;
          case 0x20:
          j=1;break;
          case 0x40:
          j=2;break;
          case 0x80:
          j=3;break;
          }
          
        return(4*i+j);
      }
      else
      {  
       P0=P0<<1;
       i++;
      }
   }
  }
}
    exit=0;
    return(key);
}

////送液晶屏显示子程序/////
void display(uchar C)
{
   if(Calcdone_flag==1 && C!=2) // 等号键除外
  {
    clear();
    Calcdone_flag = 0; // 重置标志 
  } 

    switch(C)
    {
    case 0:
        clear();
    break;
    case 1:
        prodis();
        alldata[rrr]=0;
        wrdata('0');
        break;
    case 2:
        prodis();
        wrdata('=');       /////////////////
        kind=kind+10;
        position2=rrr;
        datapc();
        remove0();
        data3dis();
    
        Calcdone_flag = 1;
    
        break;
    case 3:
        prodis();
        kind=kind+1;             /////////加法运算， kind=1
        position1=rrr;
        wrdata('+');
        break;
    case 4:
        prodis();
        alldata[rrr]=1;
        wrdata('1');
        break;
    case 5:
        prodis();
        alldata[rrr]=2;
        wrdata('2');
        break;
    case 6:
        prodis();
        alldata[rrr]=3;
        wrdata('3');
    break;
    case 7:
        prodis();
        kind=kind+5;             ////////////减法运算， kind=5
        position1=rrr;
        wrdata('-');
    break;
    case 8:
        prodis();
        alldata[rrr]=4;
        wrdata('4');
    break;
    case 9:
        prodis();
        alldata[rrr]=5;
        wrdata('5');
    break;
    case 10:
        prodis();
        alldata[rrr]=6;
        wrdata('6');
    break;
    case 11:
        prodis();
        kind=kind+25;             /////////////乘法运算， kind=25
        position1=rrr;
        wrdata('*');
    break;
    case 12:
        prodis();
        alldata[rrr]=7;
        wrdata('7');
    break;
    case 13:
        prodis();
        alldata[rrr]=8;
        wrdata('8');
    break;
    case 14:
        prodis();
        alldata[rrr]=9;
        wrdata('9'); 
    break;
    case 15:
        prodis();
        kind=kind+125;              ///////////////除法运算， kind=125
        position1=rrr;
        wrdata('/');   
    break;
    default:
        break;
 }
}
void datapc(void)
{
uchar k;
if((position1==0) || (position2==(position1+1)))
yes=1;
else
{
  for(k=0;k<position1;k++)
  {
    ddata=shi(position1-1-k);
    data1=data1+(alldata[k])*ddata;  
  }

  for(k=position1+1;k<position2;k++)
  {
    ddata=shi(position2-1-k);
    data2=data2+(alldata[k])*ddata;  
  }
  if((data1 > 50000) || (data2 > 50000))
    {yes=2;}
  else
  {
    switch (kind)
    {
        case 11:  data3=data1+data2;  yes=0;break;
        case 15: 
        if(data1<data2)
        {ddata=data1;data1=data2;data2=ddata;fu=1;}
        data3=data1-data2;  yes=0;break;
        case 35: data3=data1*data2;  yes=0;break;
        case 135:data3=data1/data2;  yes=0;break;
        default:                     yes=1;
    }
  }
}
 if(yes==0)
 {
    love[0]=data3 / 1000000000;
    love[1]=data3 / 100000000-love[0]*10;
    love[2]=data3 / 10000000- love[0]*100-    love[1]*10;
    love[3]=data3 / 1000000-  love[0]*1000-   love[1]*100- love[2]*10;
    love[4]=data3 / 100000-   love[0]*10000-  love[1]*1000-love[2]*100-love[3]*10;
    love[5]=data3 / 10000-    love[0]*100000- love[1]*10000-love[2]*1000-love[3]*100-love[4]*10;
    love[6]=(data3 % 10000)/1000;
    love[7]=(data3 % 1000)/100;
    love[8]=(data3 % 100)/10;
    love[9]= data3 % 10;
 }
 if(kind==135)
 {
    love[10]=0xfe;
    love[11]=((data1 % data2)*10)/data2;
    love[12]=((((data1 % data2)*10)%data2)*10)/data2;
    love[13]=((((((data1 % data2)*10)%data2)*10)%data2)*10)/data2;
 }
}

void remove0(void)
{
    uchar k=0;
    while((love[k]==0) && (k<=8))
    {
    love[k]=0xf0;
    k++;
    }
    pfu=k;
}

void data3dis(void)
{
    uchar k;
    if(yes==0)
    {
        if(kind==135)
        {
            for(k=0;k<=13;k++)
            {
                wrcmd(0xc2+k);
                wrdata(love[k]+0x30);
                delay();
            }
        }     
        else
        {
            for(k=0;k<=9;k++)
            {
                wrcmd(0xc6+k);
                wrdata(love[k]+0x30);
                delay();
            }
            if(fu==1)
            {
                wrcmd(0xc5+pfu);wrdata('-');delay();
            }
        }
    }
    else if(yes==1)
        error();
    else if(yes==2)
        out();
}

void clear(void)
{
    uchar k;
    
    while(((~P0) & 0xf0)!=0);
    for(k=0;k<=15;k++)
    {
        wrcmd(k+0x80);
        delay();
        wrdata(' ');
    }
    
    for(k=0;k<=15;k++)
    {
        wrcmd(k+0xc0);
        delay();
        wrdata(' ');
    }
    
    rrr=0xff;
    kind=yes=position1=position2=0;                  ///////////清运算类型标志
    fu=pfu=0;
    data1=data2=0;                                   ///////////清数据
    data3=0;
    Calcdone_flag = 0; // 重置计算完成标志
}

void prodis(void)
{
    rrr++;
    if(rrr==16)
    {rrr=0x40;}
    wrcmd(rrr+0x80);
    delay();
    while(((~P0) & 0xf0)!=0);
}