/*******************************************************************************
  Filename: 	time3.c
*******************************************************************************/
/*******************************INCLUDES***************************************/
#include "time3.h"
#include "uart2.h"

#define IRSendPin P0_7
unsigned int count = 0;
void InitTime3()
{
	P0DIR |= 0x80;           //P0.4定义为输出
	
	EA = 0;                  //开总中断
	T3CC1 = 0x40; //1S 的占空比   50 A0 198K方波  28 50 395k方波
	T3CC0 = 0x69; //1S的周期时钟    
	T3CCTL0 = 0x1c;  // 模式选择 
	T3CTL = 0x03; //0x03 62khz   250KHz  22 2分频  42 4分频 31.249k
	T3CTL |= 0x10; //启动
	T3CTL |= 0x08 ;          //开溢出中断     
    T3IE = 1;                //开总中断和T3中断
    EA = 1;                  //开总中断
}
#pragma vector = T3_VECTOR //定时器T3
 __interrupt void T3_ISR(void) 
{ 
	IRCON = 0x00;                  //清中断标志, 也可由硬件自动完成
	IRSendPin=~IRSendPin;  
}