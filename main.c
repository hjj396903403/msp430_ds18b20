
#include <msp430x14x.h>
#include"cry1602.h"
#include"ds18b20.h"
#include"cry1602.c"
#include"ds18b20.c"
uchar d[7];
uchar s[]={"temperature is:"};
void main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  uchar i,j;
  uint temp1;
  
  BCSCTL1 &= ~XT2OFF;
  do
  {
    IFG1 &= ~OFIFG;
    for(i=0xff;i>0;i--);
  }
  while(IFG1 & OFIFG);
  BCSCTL2|=SELM_2+SELS;

  
  LcdReset();
  DispNChar(0,0,14,s);
 
  while(1)
  {
    
    temp1=(uint)((Do1Convert())*0.0625*100+0.05);
    d[0]=(uchar)(temp1/1000);
    d[1]=(uchar)(temp1%1000/100);
    d[2]=-2;
    d[3]=(uchar)(temp1%100/10);
    d[4]=temp1%10;
    for(j=0;j<7;j++)
    {
      Disp1Char(j,1,d[j]+48);
    }
  }
  
}

/**********************************************************************
�¶�ת��������

��tplsb��tpmsb����8λ�ĺϳ�һ��16λ���з�����tt;tempΪ������
t=tpmsb<<8;
t=t|tplsb;
if(t<0)                                //���¶�
 {
  temp=(~t+1)*0.0625*10+0.5;           //���¶�ʱ��ȡ����1�ٳ���0.0625��ʵ���¶ȣ���10+0.5��ʾС����һλ������������
 }
else
  temp=t*0.0625*10+0.5;                //���¶�
if(t<0) 
  bai='-';                             //���¶�ʱ��λ��ʾ����
 else
  bai=(const) temp/1000+0x30;          //��λ
 shi=((const) temp%1000)/100;          //ʮλ
 ge=((const) temp%1000)%100/10;        //��λ
 shifen=((const) temp%1000)%100%10;    //ʮ��λ
 ***********************************************************************/
