#include <iocc2530.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"
#include "ds18b20.h"  

typedef unsigned char uchar;
typedef unsigned int  uint;

#define IGT P0_6       // P0.6�ڿ���IGT
uint count;             //���ڶ�ʱ������
int g_timeout=0;
/////�������¶����
extern void Delay_ms(unsigned int k);//�ⲿ����ms������
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr)[0])
#define FLOAT_TEMP
char strTemp[10];  //�¶ȴ��

//������ƵƵĶ˿�
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
//�ⲿ����
extern void DelayMS(unsigned int msec);

//����GPRS����
int  g_thread  = 0;
char g_data[50];
int Send_Wifi_DATA(char *str, int len);
//����
#define AT_C     "AT\r\n"
#define MUX_C    "AT+CIPMUX=1\r\n"
#define SERVER_C "AT+CIPSERVER=1,5000\r\n"
#define RST_C "AT+RST\r\n"

//�յ������ж�
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
�������ƣ�Print_Char
�������ܣ����͵����ַ�
��ڲ���:ch      ���ڲ�������
***********************************************************/
void Print_Char(char ch)//���͵����ַ�
{
  U0CSR &= ~0x40;			//��������
  U0DBUF = ch;
  while(UTX0IF == 0);
  UTX0IF = 0;
  U0CSR |= 0x40;			//�������
}

/***********************************************************
�������ƣ�Print_Str
�������ܣ������ַ���
��ڲ���:*str    ���ڲ�������
***********************************************************/
void Print_Str(char *str)//�����ַ���
{
  
  while(*str!='\0')
  {
    Print_Char(*str);
    DelayMS(2);
    str++;
  }
}

/****************************************************************
��ʼ������0����					
****************************************************************/
void initUART0(void)
{
  
  CLKCONCMD &= ~0x40;                         //����ϵͳʱ��ԴΪ32MHZ����
  while(CLKCONSTA & 0x40);                    //�ȴ������ȶ�
  CLKCONCMD &= ~0x47;                         //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ
  
  PERCFG = 0x00;				//λ��1 P0��
  P0SEL = 0x0c;				//P0��������
  P2DIR &= ~0XC0;                             //P0������ΪUART0    
  
  U0CSR |= 0x80;				//��������ΪUART��ʽ
  U0GCR |= 11;				
  U0BAUD |= 216;				//��������Ϊ9600
  UTX0IF = 1;                                 //UART0 TX�жϱ�־��ʼ��λ1 
  
  U0CSR |= 0X40;				//�������
  IEN0 |= 0x84;				//�����жϣ������ж�    
}

/****************************************************************************
* ��    ��: SetWifi()
* ��    ��: ����LED����Ӧ��IO��
* ��ڲ���: ��
* ���ڲ���: ��
****************************************************************************/
void SetWifi(void)
{
  P0DIR |= 0x40;           //P0.6����Ϊ���
  IGT = 1;                 //�ߵ�ƽ��λ
  DelayMS(500);
  IGT = 0;                 //�͵�ƽ����
}



void dispIGTState()
{
  if(IGT>0) //���WIFIģ�鸴λ�ܽ�
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
  if(LED1>0) //���WIFIģ�鸴λ�ܽ�
  {
    LCD_P8x16Str(0, 5, "D1H"); 
    strcat(g_data,"D1H");
  }
  else
  {
    LCD_P8x16Str(0, 5, "D1L"); 
    strcat(g_data,"D1L");
  }    
  
  if(LED2>0) //���WIFIģ�鸴λ�ܽ�
  {
    LCD_P8x16Str(32, 5, "D2H"); 
    strcat(g_data,"D2H");
  }
  else
  {
    LCD_P8x16Str(32, 5, "D2L"); 
    strcat(g_data,"D2L");
  }    
  
  if(LED3>0) //���WIFIģ�鸴λ�ܽ�
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
   
  if(strstr(str,Rev_D1G)!=NULL) //���WIFIģ�鸴λ�ܽ�
  {
    LED1=1;
  }
  if(strstr(str,Rev_D1K)!=NULL)
  {
    LED1=0;
  }
          
  if(strstr(str,Rev_D2G)!=NULL) //���WIFIģ�鸴λ�ܽ�
  {
    LED2=1;
  }
  if(strstr(str,Rev_D2K)!=NULL)
  {
    LED2=0;
  }
          
  if(strstr(str,Rev_D3G)!=NULL) //���WIFIģ�鸴λ�ܽ�
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
    P0SEL &= 0x7f;                  //DS18B20��io�ڳ�ʼ��
   
    if(1)                           //������¶ȴ�����
    {        
        memset(strTemp, 0, ARRAY_SIZE(strTemp)); 

//�����ṩ�ĳ����¶�ֵ����С����Ds18B20������֧��1λС��λ�ģ��޸ĺ�ʹ��֧�֣����ȸ���        
#if defined(FLOAT_TEMP)                 
        fTemp = floatReadDs18B20();       //�¶ȶ�ȡ���� ��1λС��λ
        sprintf(strTemp, "%.01f", fTemp); //��������ת���ַ���  
#else       
//        ucTemp = ReadDs18B20();           //�¶ȶ�ȡ����
//        strTemp[0] = ucTemp/10+48;        //ȡ��ʮλ��
//        strTemp[1] = ucTemp%10+48;        //ȡ����λ��
        sprintf(strTemp, "%d%d", ucTemp/10, ucTemp%10);
#endif 
        LCD_P8x16Str(95, 5, (unsigned char*)strTemp);
        strcat(g_data,"#");
        strcat(g_data,strTemp);
        //Delay_ms(1000);                   //��ʱ����ʹ�ö�ʱ����ʽ
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
������							
****************************************************************/
void main(void)
{
  Delay_ms(10);          //���豸�ȶ�
  SetWifi();		                //����LED����Ӧ��IO��
  
  P1DIR |= 0x03; 				//P1����LED 10 11 04
  P0DIR |= 0x10;
  LED1 = 1;                               //��LED
  LED2 = 1;				//��LED
  LED3 = 1;                               //��LED
  
  clearBuff();       //��ջ���
  initUART0();       //��ʼ������
  Print_Str("init uart [ok]\r\n");	      

  ////
  LCD_Init();   //LCD��ʼ��
  LCD_CLS();    //����
  LCD_welcome();     
  Print_Str("init OLED [ok]\r\n");	
  
  
  dispIGTState();    //��ʾWIFI�Ƿ���
  Wifi_Rst();        //wifi�����λ
  
  Connect_Wifi();               //zigbee��WIFIͨ��
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
   if(strstr((char const *)Recdata,Rev_F)!=NULL) //���յ�������
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
   
    if(strstr((char const *)Recdata,Rev_GD)!=NULL) //�Ѽ��ɼ�����
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
���ڽ���һ���ַ�:һ�������ݴӴ��ڴ���CC2530,������жϣ������յ������ݸ�ֵ������temp.
****************************************************************/
#pragma vector = URX0_VECTOR
__interrupt void UART0_ISR(void)
{
  
  if(j<81)
  {  
    tempRX = U0DBUF; 
    Recdata[j]=tempRX;//����浽��������
    
    URX0IF=0; //�����������ж�
    j++;
  }
}
