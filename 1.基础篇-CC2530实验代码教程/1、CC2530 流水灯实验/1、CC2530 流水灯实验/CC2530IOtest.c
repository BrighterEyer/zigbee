#include <ioCC2530.h>
#define uint  unsigned int
#define uchar unsigned char
//定义控制灯的端口
#define LED1 P1_0	//定义LED1为P10口控制
#define LED2 P1_1	//定义LED2为P11口控制
#define LED3 P0_4	//定义LED3为P04口控制
//函数声明
void Delay(uint);		//延时函数
void InitIO(void);		//初始化LED控制IO口函数
/****************************
//延时
*****************************/
void Delay(uint n)
{
  uint i;
  for(i = 0;i<n;i++);
  for(i = 0;i<n;i++);
  for(i = 0;i<n;i++);
  for(i = 0;i<n;i++);
  for(i = 0;i<n;i++);
}
/****************************
//初始化IO口程序
*****************************/
void InitIO(void)
{
  P1DIR |= 0x13;  //P10、P11定义为输出
  P0DIR |= 0x10;  //P04定义为输出
  LED1 = 1;
  LED2 = 1;
  LED3 = 1;	   //LED灯初始化为关
}
/***************************
//主函数
***************************/
void main(void)
{
  InitIO();		//初始化LED灯控制IO口	
  while(1)                //死循环
  {  
    LED1 = !LED1;           // LED1灯闪一次
    Delay(50000);           
    LED2 = !LED2;           // LED2灯闪一次
    Delay(50000);            
    LED3 = !LED3;           // LED3灯闪一次
    Delay(50000);
    
  }
}
