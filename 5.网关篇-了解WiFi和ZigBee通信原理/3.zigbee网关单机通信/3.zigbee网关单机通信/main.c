#include <iocc2530.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "ds18b20.h"  

typedef unsigned char uchar;
typedef unsigned int  uint;

#define IGT P0_6       // P0.6口控制IGT
uint count;             //用于定时器计数
int g_timeout=0;
/////以下是温度相关
extern void Delay_ms(unsigned int k);//外部函数ms的声明
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr)[0])
#define FLOAT_TEMP
char strTemp[10];  //温度存放

//定义控制灯的端口
#define LED1 P1_0
#define LED2 P1_1
#define LED3 P0_4

void initUART0(void);
void InitialAD(void);
void UartTX_Send_String(uchar *Data,int len);

#define MAXCHAR 81
uchar  Recdata[MAXCHAR];

uchar RXTXflag = 1;
uchar tempRX;
uint  datanumber = 0;
uint  stringlen;
uint j = 0;
//外部函数
extern void DelayMS(unsigned int msec);

//发送GPRS数据
int  g_thread  = 0;
char g_data[50];
int Send_Wifi_DATA(char *str, int len);
//命令
#define AT_C     "AT\r\n"
#define MUX_C    "AT+CIPMUX=1\r\n"
#define SERVER_C "AT+CIPSERVER=1,5000\r\n"
#define RST_C "AT+RST\r\n"

//收到数据判断
#define Rev_F "ESP" 

#define Rev_D1G "ESPGLED1"
#define Rev_D1K "ESPKLED1"
#define Rev_D2G "ESPGLED2"
#define Rev_D2K "ESPKLED2"
#define Rev_D3G "ESPGLED3"
#define Rev_D3K "ESPKLED3"

#define Rev_TUL "UNLINX"
#define Rev_TLI "LINK"
#define Rev_GD "GETDATA"
#define Rev_TUL1 "Unlink"

void clearBuff(void)
{
  for(j=0;j<MAXCHAR;j++)
  {
    Recdata[j]=0x00;
  }
  j=0;
}

/***********************************************************
函数名称：Print_Char
函数功能：发送单个字符
入口参数:ch      出口参数：无
***********************************************************/
void Print_Char(char ch)//发送单个字符
{
  U0CSR &= ~0x40;			//不能收数
  U0DBUF = ch;
  while(UTX0IF == 0);
  UTX0IF = 0;
  U0CSR |= 0x40;			//允许接收
}

/***********************************************************
函数名称：Print_Str
函数功能：发送字符串
入口参数:*str    出口参数：无
***********************************************************/
void Print_Str(char *str)//发送字符串
{
  
  while(*str!='\0')
  {
    Print_Char(*str);
    DelayMS(2);
    str++;
  }
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
  U0BAUD |= 216;				//波特率设为9600
  UTX0IF = 1;                                 //UART0 TX中断标志初始置位1 
  
  U0CSR |= 0X40;				//允许接收
  IEN0 |= 0x84;				//开总中断，接收中断    
}

/****************************************************************************
* 名    称: SetWifi()
* 功    能: 设置LED灯相应的IO口
* 入口参数: 无
* 出口参数: 无
****************************************************************************/
void SetWifi(void)
{
  P0DIR |= 0x40;           //P0.6定义为输出
  IGT = 1;                 //高电平复位
  DelayMS(500);
  IGT = 0;                 //低电平工作
}



void dispIGTState()
{
  if(IGT>0) //监测WIFI模块复位管脚
  {
    //LCD_P8x16Str(8, 5, "IGTH"); 
  }
  else
  {
    //LCD_P8x16Str(8, 5, "IGTL"); 
  }                
}


void dispLEDState()
{
  if(LED1>0) //监测WIFI模块复位管脚
  {
    LCD_P8x16Str(0, 5, "D1H"); 
    strcat(g_data,"D1H");
  }
  else
  {
    LCD_P8x16Str(0, 5, "D1L"); 
    strcat(g_data,"D1L");
  }    
  
  if(LED2>0) //监测WIFI模块复位管脚
  {
    LCD_P8x16Str(32, 5, "D2H"); 
    strcat(g_data,"D2H");
  }
  else
  {
    LCD_P8x16Str(32, 5, "D2L"); 
    strcat(g_data,"D2L");
  }    
  
  if(LED3>0) //监测WIFI模块复位管脚
  {
    LCD_P8x16Str(62, 5, "D3H"); 
    strcat(g_data,"D3H");
  }
  else
  {
    LCD_P8x16Str(62, 5, "D3L"); 
    strcat(g_data,"D3L");
  }    
}

void Wifi_Ctrl_ZGBLED(char const * str)
{
   
  if(strstr(str,Rev_D1G)!=NULL) //监测WIFI模块复位管脚
  {
    LED1=1;
  }
  if(strstr(str,Rev_D1K)!=NULL)
  {
    LED1=0;
  }
          
  if(strstr(str,Rev_D2G)!=NULL) //监测WIFI模块复位管脚
  {
    LED2=1;
  }
  if(strstr(str,Rev_D2K)!=NULL)
  {
    LED2=0;
  }
          
  if(strstr(str,Rev_D3G)!=NULL) //监测WIFI模块复位管脚
  {
    LED3=1;
  }
  if(strstr(str,Rev_D3K)!=NULL)
  {
    LED3=0;
  }  
}



void Wifi_Rst(void)
{
  
  
  clearBuff();
  Print_Str(RST_C);
  DelayMS(100);
  
  
  if(strstr((char const *)Recdata,"OK")==NULL)
  {
    LCD_P8x16Str(8,2,"Wifi Reset....");
    DelayMS(5000);
    clearBuff();
  }
  else
  {
    LCD_P8x16Str(8,2,"Wifi Reset[OK]");
    DelayMS(5000);
    clearBuff();
  }
  
}


void Connect_Wifi(void)
{
  
  
  clearBuff();
  Print_Str(AT_C);
  DelayMS(50);
  
  
  while(strstr((char const *)Recdata,"OK")==NULL)
  {
    LED1=1;
    DelayMS(500);
    LED1=0;
    LCD_P8x16Str(8,2,"connect.......");
    clearBuff();
    Print_Str(AT_C);
    DelayMS(500);
  }
  LCD_P8x16Str(8,2,"connect...[OK]");
  LED1=0;
  
}



void Init_MUX(void)
{ 
  clearBuff();
  Print_Str(MUX_C);
  DelayMS(50);
  
  
  while(strstr((char const *)Recdata,"OK")==NULL)
  {
    LED2=1;
    DelayMS(500);
    LED2=0;
    LCD_P8x16Str(8,2,"Init MUX......");
    clearBuff();
    Print_Str(MUX_C);
    DelayMS(500);
  }
  LCD_P8x16Str(8,2,"Init MUX..[OK]");
  LED2=0;
  
}

void Init_Server(void)
{
  
  
  clearBuff();
  Print_Str(SERVER_C);
  DelayMS(50);
  
  
  while(strstr((char const *)Recdata,"OK")==NULL)
  {
    LED3=1;
    DelayMS(500);
    LED3=0;
    LCD_P8x16Str(8,2,"Init Server...");
    clearBuff();
    Print_Str(SERVER_C);
    DelayMS(500);
  }
  LCD_P8x16Str(8,2,"TCP Server[OK]");
  LED3=0;
}

char Get_DS18B20(void)
{  
    float fTemp;
    P0SEL &= 0x7f;                  //DS18B20的io口初始化
   
    if(1)                           //插好了温度传感器
    {        
        memset(strTemp, 0, ARRAY_SIZE(strTemp)); 

//厂家提供的程序温度值不带小数，Ds18B20本身是支持1位小数位的，修改后使其支持，精度更高        
#if defined(FLOAT_TEMP)                 
        fTemp = floatReadDs18B20();       //温度读取函数 带1位小数位
        sprintf(strTemp, "%.01f", fTemp); //将浮点数转成字符串  
#else       
//        ucTemp = ReadDs18B20();           //温度读取函数
//        strTemp[0] = ucTemp/10+48;        //取出十位数
//        strTemp[1] = ucTemp%10+48;        //取出个位数
        sprintf(strTemp, "%d%d", ucTemp/10, ucTemp%10);
#endif 
        LCD_P8x16Str(95, 5, (unsigned char*)strTemp);
        strcat(g_data,"#");
        strcat(g_data,strTemp);
        //Delay_ms(1000);                   //延时函数使用定时器方式
    }
    return 0;
}

int Send_Wifi_DATA(char *str, int len)
{
  char SEND_C[20];
  memset(SEND_C,0,20);
  sprintf(SEND_C,"AT+CIPSEND=%d,%d\r\n",g_thread,len);
  
  Print_Str(SEND_C);
  DelayMS(50);
  
  while(strstr((char const *)Recdata,">")==NULL)
  {
    if(g_timeout>50)
    {
        g_timeout=0;
        return -1;
    }
    DelayMS(5);
    g_timeout++;
    
  }
  Print_Str(str);
  return 0;
}

/****************************************************************
主函数							
****************************************************************/
void main(void)
{
  Delay_ms(10);          //让设备稳定
  SetWifi();		                //设置LED灯相应的IO口
  
  P1DIR |= 0x03; 				//P1控制LED 10 11 04
  P0DIR |= 0x10;
  LED1 = 1;                               //关LED
  LED2 = 1;				//关LED
  LED3 = 1;                               //关LED
  
  clearBuff();       //清空缓冲
  initUART0();       //初始化串口
  Print_Str("init uart [ok]\r\n");	      

  ////
  LCD_Init();   //LCD初始化
  LCD_CLS();    //清屏
  LCD_welcome();     
  Print_Str("init OLED [ok]\r\n");	
  
  
  dispIGTState();    //显示WIFI是否开启
  Wifi_Rst();        //wifi软件复位
  
  Connect_Wifi();               //zigbee和WIFI通信
  DelayMS(1000);
  
  Init_MUX();       
  DelayMS(1000);
  
  Init_Server();
  
  
  while(1)
  {
    memset(g_data,0,50);
    strcat(g_data,"ZW#");
    dispIGTState();
    dispLEDState();
    Get_DS18B20();
   if(strstr((char const *)Recdata,Rev_F)!=NULL) //接收到了数据
    {
      Wifi_Ctrl_ZGBLED((char const *)Recdata);
    }

   
    if(strstr((char const *)Recdata,Rev_TUL)!=NULL)
    {
      LCD_P8x16Str(8,2,"PC/MP UnLink .");
      clearBuff();  
    }
    if(strstr((char const *)Recdata,Rev_TUL1)!=NULL)
    {
      LCD_P8x16Str(8,2,"PC/MP UnLink .");
    }
    if(strstr((char const *)Recdata,Rev_TLI)!=NULL)
    {
      LCD_P8x16Str(8,2,"PC/MP Link On.");
      clearBuff();  
    }
   
    if(strstr((char const *)Recdata,Rev_GD)!=NULL) //搜集采集数据
    {
      DelayMS(1000);
      Send_Wifi_DATA(g_data,strlen(g_data)) ;
      DelayMS(1000);
    }
    
            
    clearBuff();   
    DelayMS(10);
  }
}
/****************************************************************
串口接收一个字符:一旦有数据从串口传至CC2530,则进入中断，将接收到的数据赋值给变量temp.
****************************************************************/
#pragma vector = URX0_VECTOR
__interrupt void UART0_ISR(void)
{
  
  if(j<81)
  {  
    tempRX = U0DBUF; 
    Recdata[j]=tempRX;//命令存到命令数组
    
    URX0IF=0; //软件清除接收中断
    j++;
  }
}
