/**************************************/
/*描述：按键S1外部中断方式改变LED1状态
**************************************/
#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//定义控制LED灯的端口
#define LED1 P1_0	//定义LED1为P1.0口控制
#define KEY1 P0_1       //中断口
//函数声明
void Delayms(uint);		//延时函数
void InitLed(void);		//初始化P1口
void KeyInit();                 //按键初始化
uchar KeyValue=0;

/****************************
//延时函数
*****************************/
void Delayms(uint xms)   //i=xms 即延时i毫秒
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}
/****************************
LED初始化程序
*****************************/
void InitLed(void)
{
  P1DIR |= 0x01; //P1_0定义为输出
  LED1 = 1;       //LED1灯熄灭     
}

/****************************
KEY初始化程序--外部中断方式
*****************************/
void InitKey()
{
  P0IEN |= 0X2;  //P01设置为中断方式 
  PICTL |= 0X2; // 下降沿触发   
  IEN1 |= 0X20;   // 允许P0口中断; 
  P0IFG = 0x00;   // 初始化中断标志位
  EA = 1; 
}

/**************************** 
      中断处理函数 
*****************************/ 
#pragma vector = P0INT_VECTOR    //格式：#pragma vector = 中断向量，紧接着是中断处理程序
  __interrupt void P0_ISR(void) 
 { 
  Delayms(10);            //去除抖动
  LED1=~LED1;             //改变LED1状态
  P0IFG = 0;             //清中断标志 
  P0IF = 0;             //清中断标志 
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
        }
}
