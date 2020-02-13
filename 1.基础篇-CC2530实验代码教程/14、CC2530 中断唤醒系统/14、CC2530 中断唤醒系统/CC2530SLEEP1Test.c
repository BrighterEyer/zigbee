#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char
#define DELAY 15000

#define LED1 P1_0
#define LED2 P1_1       //LED�ƿ���IO�ڶ���

void Delay(void);
void Init_IO_AND_LED(void);
void SysPowerMode(uchar sel);

/****************************************************************
    ��ʱ����	
****************************************************************/
void Delay(void)
{
	uint i;
	for(i = 0;i<DELAY;i++);
	for(i = 0;i<DELAY;i++);
	for(i = 0;i<DELAY;i++);
	for(i = 0;i<DELAY;i++);
	for(i = 0;i<DELAY;i++);
	for(i = 0;i<DELAY;i++);
	for(i = 0;i<DELAY;i++);
	for(i = 0;i<DELAY;i++);
	for(i = 0;i<DELAY;i++);
	for(i = 0;i<DELAY;i++);
}

/****************************************************************
ϵͳ����ģʽѡ����											
* para1  0 	1	2	3									
* mode 	PM0	PM1	PM2	PM3													
****************************************************************/
void SysPowerMode(uchar mode)
{
  uchar i,j;
  i = mode;
  if(mode<4)
  {
    SLEEPCMD &= 0xFC;     
    SLEEPCMD |= i;       //����ϵͳ˯��ģʽ
    for(j=0;j<4;j++);
    {
      PCON = 0x01;         //����˯��ģʽ
    }
  }
  else
  {
    PCON = 0x00;             //ϵͳ����
  }
}

/****************************************************************
      LED����IO�ڳ�ʼ������			
****************************************************************/
void Init_IO_AND_LED(void)
{
    P1DIR = 0X03;
    LED1 = 1;
    LED2 = 1;
    //P0SEL &= ~0X32;
    //P0DIR &= ~0X32;
    P0INP  &= ~0X32;   //����P0�������·ģʽΪ����/����
    P2INP &= ~0X20;    //ѡ������
    P0IEN |= 0X32;     //P01����Ϊ�жϷ�ʽ
    PICTL |= 0X01;     //�½��ش���
    EA = 1;
    IEN1 |= 0X20;      // ��P0�����ж�
    P0IFG |= 0x00;     //���жϱ�־
};
/****************************************************************
    ������	
****************************************************************/
void main()
{
  uchar count = 0;
  Init_IO_AND_LED();
  LED1 = 0 ;       //��LED1��ϵͳ����ָʾ
  Delay();         //��ʱ	
  while(1)
  {
    LED2 = !LED2;
    LED1 = 0;
    count++;
    if(count >= 6)
    {
      count = 0;     
      LED1 = 1;
      SysPowerMode(3);
      //3����˸�����˯��״̬PM3
    }
    //Delay();
    Delay();
    //��ʱ�������βΣ�ֻ��ͨ���ı�ϵͳʱ��Ƶ�ʻ�DEALY�ĺ궨��
    //���ı�С�Ƶ���˸Ƶ��
  };
}
/*****************************************
    �жϴ�����-ϵͳ����
*****************************************/
#pragma vector = P0INT_VECTOR
 __interrupt void P0_ISR(void)
 {
  if(P0IFG>0)
  {
     P0IFG = 0;
  }
  
  P0IF = 0;
  SysPowerMode(4);
 }
