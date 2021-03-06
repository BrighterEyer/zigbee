#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制LED灯的端口
#define LED1 P1_0	//LED1为P1.0口控制
#define KEY1 P0_1      //KEY1为P0.1口控制

//函数声明
void Delayms(uint);		//延时函数
void InitLed(void);		//初始化LED1
void KeyInit();                 //按键初始化
uchar KeyScan();                //按键扫描程序

/****************************
延时函数
*****************************/
void Delayms(uint xms)   //i=xms 即延时i毫秒
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}

/****************************
      LED初始化函数
*****************************/
void InitLed(void)
{
    P1DIR |= 0x01;  //P1_0定义为输出
    LED1 = 1;       //LED1灯熄灭     
}

/****************************
     按键初始化函数
*****************************/
void InitKey()
{
  P0SEL &= ~0X2;    //设置P01为普通IO口  
  P0DIR &= ~0X2;   //按键在P01 口，设置为输入模式 
  P0INP &=  ~0x2;   //打开P01上拉电阻,不影响
}

/****************************
     按键检测函数
*****************************/
uchar KeyScan(void)
{
  if(KEY1==0)
  {
    Delayms(10);
    if(KEY1==0)
    {
      while(!KEY1);  //松手检测
      return 1;      //有按键按下
    }
  }
  return 0;           //无按键按下
}

/***************************
      主函数
***************************/
void main(void)
{
  InitLed();		//调用初始化函数
  InitKey();
  while(1)
  {
   if(KeyScan())       //按键改变LED状态
     LED1=~LED1;       
  }
}
