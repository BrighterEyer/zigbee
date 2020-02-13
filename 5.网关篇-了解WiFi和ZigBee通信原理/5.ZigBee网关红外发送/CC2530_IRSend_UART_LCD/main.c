/****************************************************************************
* 文 件 名: main.c
* 作    者: 创思通信
* 修    订: 2015-06-08
* 版    本: V1.0
* 描    述: 主程序
****************************************************************************/

#include "uart2.h"
#include "lcd12864.h"
#include "IRSend.h"
#include <stdio.h>


#define KEY1 P0_1      //KEY1为P0.1口控制
#define KEY2 P2_0      //KEY2为P2.0口控制

uint8  Recdata[30]="红外解码测试\r\n";
uint16 stringlen;

extern uint16 HWSendAddcode;//红外发送地址码
//extern uint16 HWdat[66];
/****************************
延时函数
*****************************/
void Delayms(uint16 xms)   //i=xms 即延时i毫秒
{
 uint16 i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}

/****************************
     按键初始化函数
*****************************/
void InitKey()
{
  P0SEL &= ~0X2;    //设置P01为普通IO口  
  P0DIR &= ~0X2;   //按键在P01 口，设置为输入模式 
  P0INP &=  ~0x2;   //打开P01上拉电阻,不影响
  
  P2SEL &= ~0X01;    //设置P20为普通IO口  
  P2DIR &= ~0X01;   //按键在P20 口，设置为输入模式 
  P2INP &=  ~0x01;   //打开P20上拉电阻,不影响  
  
}
/****************************
     按键检测函数
*****************************/
uint8 KeyScan(void)
{
  if(KEY1==0)		//如果KEY是低电平
  {
    Delayms(10);	//延时消抖 
    if(KEY1==0)		//如果KEY还是低电平
    {
      while(!KEY1);  //等待高电平
      return 1;      //返回按钮数  有按键按下
    }
  }
  if(KEY2==0)		//同上，按键不一样而已
  {
    Delayms(10);
    if(KEY2==0)
    {
      while(!KEY2);
      return 2;    
    }
  }  
  return 0;          
}
/****************************************************************
主函数							
****************************************************************/
void main(void)
{	
	unsigned char str[40];	
	uint8 key=0;
	P1DIR = 0x03; 			//P1控制LED
	LED1 = 1;				//开LED1
	LED2 = 0;				//开LED2
    LED3 = 1;				//关LED3
	initUART0();			//串口初始化
    stringlen = strlen((char *)Recdata);//获得字符串长度
	UartTX_Send_String(Recdata,stringlen);//发送字符串
	
	LCD_Init();				//oled 初始化  
    LCD_CLS();				//屏全亮 
    LCD_welcome();			//显示初始化字符
	Uart2_Send_char(0x11);	//串口测试
	
	IRSendInit();
	
	sprintf((char *)str, "0x%04X", HWSendAddcode);//把地址码转成字符串
	LCD_P8x16Str(80, 2, str);				//显示地址码
				
	while(1)
	{
		key = KeyScan();		//按键扫描
		if(key==1)
		{
			IR_Sending(0xEA15);		//发送红外 只输入指令码就可以了，地址码本遥控器都是0xff00
			sprintf((char *)str, "0x%04X", 0xEA15);//把指令码转成字符串
			LCD_P8x16Str(80, 4, str);				//显示指令码
			LCD_P8x16Str(80, 6, "VOL+ ");			//显示指令名称
			stringlen = strlen("SendIR：0xEA15 VOL+ \r\n");
			UartTX_Send_String("SendIR：0xEA15 VOL+ \r\n",stringlen);//串口输出
		}
		else if(key==2)
		{
			IR_Sending(0xF807);		//发送红外 只输入指令码就可以了，地址码本遥控器都是0xff00
			sprintf((char *)str, "0x%04X", 0xF807);//把指令码转成字符串
			LCD_P8x16Str(80, 4, str);				//显示指令码
			LCD_P8x16Str(80, 6, "VOL- ");			//显示指令名称
			stringlen = strlen("SendIR：0xF807 VOL- \r\n");
			UartTX_Send_String("SendIR：0xF807 VOL- \r\n",stringlen);//串口输出			
			
		}
	}
}
