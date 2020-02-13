


#include "uart2.h"

#define uint unsigned int
#define uchar unsigned char

uint8 temp;

/****************************************************************
串口发送字符串函数				
****************************************************************/
void UartTX_Send_String(uchar *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}
/*******************************************************************************
串口发送一个字节函数			
*******************************************************************************/
void Uart2_Send_char(uint8 Data)
{
	//U0CSR &= ~0x40;      //禁止接收
	U0DBUF = Data;
	while(UTX0IF == 0);
	UTX0IF = 0;
	//U0CSR |= 0x40;      //允许接收
}
void Uart2_Send_int(uint16 Data)
{
	//U0CSR &= ~0x40;      //禁止接收
	U0DBUF = (Data>>8)&0xff;
	while(UTX0IF == 0);
	UTX0IF = 0;
	U0DBUF = Data&0xff;
	while(UTX0IF == 0);
	UTX0IF = 0;	
	//U0CSR |= 0x40;      //允许接收
}
 
/****************************************************************
初始化串口0函数					
****************************************************************/
void initUART0(void)
{
    CLKCONCMD &= ~0x40;                         //设置系统时钟源为32MHZ晶振
    while(CLKCONSTA & 0x40);                    //等待晶振稳定
    CLKCONCMD &= ~0x47;                         //设置系统主时钟频率为32MHZ
    PERCFG = 0x00;				//位置1 P0口
    P0SEL = 0x0c;				//P0用作串口
    P2DIR &= ~0XC0;                             //P0优先作为UART0    
    U0CSR |= 0x80;				//串口设置为UART方式
    U0GCR |= 11;				
    U0BAUD |= 216;				//波特率设为115200
    UTX0IF = 1;                                 //UART0 TX中断标志初始置位1 
    U0CSR |= 0X40;				//允许接收
    IEN0 |= 0x84;				//开总中断，接收中断
}
/****************************************************************
串口接收一个字符:一旦有数据从串口传至CC2530,则进入中断，将接收到的数据赋值给变量temp.
****************************************************************/
#pragma vector = URX0_VECTOR
 __interrupt void UART0_ISR(void)
 {
 	URX0IF = 0;				//清中断标志
	temp = U0DBUF;                          
 }
