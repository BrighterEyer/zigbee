/****************************************************************************
* ��    ��: ���ô��ڵ������ֲ����ʣ�115200bps 8N1
*           DS18B20�ɼ����¶�ͨ�����ڴ���������ʾ
****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "ds18b20.h"  
#include "LCD.h"

typedef unsigned char uchar;
typedef unsigned int  uint;
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr)[0])
#define FLOAT_TEMP      1          //������߾���ʱ�򿪴�ע��

extern void Delay_ms(unsigned int k);//�ⲿ����ms������

/****************************************************************************
* ��    ��: InitCLK()
* ��    ��: ����ϵͳʱ��Դ
* ��ڲ���: ��
* ���ڲ���: ��
****************************************************************************/
void InitCLK()
{
    CLKCONCMD &= ~0x40;             //����ϵͳʱ��ԴΪ32MHZ����
    while(CLKCONSTA & 0x40);        //�ȴ������ȶ�Ϊ32M
    CLKCONCMD &= ~0x47;             //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ   
}

/****************************************************************************
* ��    ��: InitUart()
* ��    ��: ���ڳ�ʼ������
* ��ڲ���: ��
* ���ڲ���: ��
****************************************************************************/
void InitUart()
{
    PERCFG = 0x00;                  //λ��1 P0��
    P0SEL = 0x0c;                   //P0��������
    P2DIR &= ~0xc0;                 //P0������ΪUART0 
    U0CSR |= 0x80;                  //��������ΪUART��ʽ
    U0GCR |= 11;
    U0BAUD |= 216;                  //��������Ϊ115200
    U0CSR |= 0x40;                  //UART������ʹ��
    UTX0IF = 0;                     //UART0 TX�жϱ�־��ʼ��λ0
}

/****************************************************************************
* ��    ��: UartSendString()
* ��    ��: ���ڷ��ͺ���
* ��ڲ���: Data:���ͻ�����   len:���ͳ���
* ���ڲ���: ��
****************************************************************************/
void UartSendString(char *Data, int len)
{
    uint i;
    
    for(i=0; i<len; i++)
    {
        U0DBUF = *Data++;
        while(UTX0IF == 0);
        UTX0IF = 0;
    }
}

/****************************************************************************
* ������ں���
****************************************************************************/
void main()
{
    char str[9]="DS18B20:";
    char strTemp[30];
    float fTemp;

    
    InitCLK();                      //����ϵͳʱ��Դ
    InitUart();                     //���ڳ�ʼ��
    P0SEL &= 0x7f;                  //DS18B20��io�ڳ�ʼ��
    
    LCD_Init();                 //oled ��ʼ��  
    LCD_CLS();                  //��ȫ�� 
    LCD_welcome();
    
    while(1)
    {        
        memset(strTemp, 0, ARRAY_SIZE(strTemp)); 

//�����ṩ�ĳ����¶�ֵ����С����Ds18B20������֧��1λС��λ�ģ��޸ĺ�ʹ��֧�֣����ȸ���        
#if defined(FLOAT_TEMP)                 
        fTemp = floatReadDs18B20();       //�¶ȶ�ȡ���� ��1λС��λ
        sprintf(strTemp, "%s%.01f", str, fTemp); //��������ת���ַ���  
        UartSendString(strTemp, strlen(strTemp));       //ͨ�����ڷ����¶�ֵ��������ʾ
#else       
        ucTemp = ReadDs18B20();           //�¶ȶ�ȡ����
//        strTemp[0] = ucTemp/10+48;        //ȡ��ʮλ��
//        strTemp[1] = ucTemp%10+48;        //ȡ����λ��
        sprintf(strTemp, "%s%d%d", str, ucTemp/10, ucTemp%10);
        UartSendString(strTemp, strlen(strTemp));       //ͨ�����ڷ����¶�ֵ��������ʾ
#endif 
        LCD_P8x16Str(0, 5, (unsigned char*)strTemp);
        UartSendString("\r\n", 2);          // �س�����     
        Delay_ms(1000);                   //��ʱ����ʹ�ö�ʱ����ʽ
    }
}