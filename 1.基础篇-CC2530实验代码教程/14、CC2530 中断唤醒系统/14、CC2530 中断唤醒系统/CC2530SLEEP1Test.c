#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char
#define DELAY 15000

#define LED1 P1_0
#define LED2 P1_1       //LED灯控制IO口定义

void Delay(void);
void Init_IO_AND_LED(void);
void SysPowerMode(uchar sel);

/****************************************************************
    延时函数	
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
系统工作模式选择函数											
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
    SLEEPCMD |= i;       //设置系统睡眠模式
    for(j=0;j<4;j++);
    {
      PCON = 0x01;         //进入睡眠模式
    }
  }
  else
  {
    PCON = 0x00;             //系统唤醒
  }
}

/****************************************************************
      LED控制IO口初始化函数			
****************************************************************/
void Init_IO_AND_LED(void)
{
    P1DIR = 0X03;
    LED1 = 1;
    LED2 = 1;
    //P0SEL &= ~0X32;
    //P0DIR &= ~0X32;
    P0INP  &= ~0X32;   //设置P0口输入电路模式为上拉/下拉
    P2INP &= ~0X20;    //选择上拉
    P0IEN |= 0X32;     //P01设置为中断方式
    PICTL |= 0X01;     //下降沿触发
    EA = 1;
    IEN1 |= 0X20;      // 开P0口总中断
    P0IFG |= 0x00;     //清中断标志
};
/****************************************************************
    主函数	
****************************************************************/
void main()
{
  uchar count = 0;
  Init_IO_AND_LED();
  LED1 = 0 ;       //开LED1，系统工作指示
  Delay();         //延时	
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
      //3次闪烁后进入睡眠状态PM3
    }
    //Delay();
    Delay();
    //延时函数无形参，只能通过改变系统时钟频率或DEALY的宏定义
    //来改变小灯的闪烁频率
  };
}
/*****************************************
    中断处理函数-系统唤醒
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
