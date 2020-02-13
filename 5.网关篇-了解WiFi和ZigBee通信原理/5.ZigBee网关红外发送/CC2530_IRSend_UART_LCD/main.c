/****************************************************************************
* �� �� ��: main.c
* ��    ��: ��˼ͨ��
* ��    ��: 2015-06-08
* ��    ��: V1.0
* ��    ��: ������
****************************************************************************/

#include "uart2.h"
#include "lcd12864.h"
#include "IRSend.h"
#include <stdio.h>


#define KEY1 P0_1      //KEY1ΪP0.1�ڿ���
#define KEY2 P2_0      //KEY2ΪP2.0�ڿ���

uint8  Recdata[30]="����������\r\n";
uint16 stringlen;

extern uint16 HWSendAddcode;//���ⷢ�͵�ַ��
//extern uint16 HWdat[66];
/****************************
��ʱ����
*****************************/
void Delayms(uint16 xms)   //i=xms ����ʱi����
{
 uint16 i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}

/****************************
     ������ʼ������
*****************************/
void InitKey()
{
  P0SEL &= ~0X2;    //����P01Ϊ��ͨIO��  
  P0DIR &= ~0X2;   //������P01 �ڣ�����Ϊ����ģʽ 
  P0INP &=  ~0x2;   //��P01��������,��Ӱ��
  
  P2SEL &= ~0X01;    //����P20Ϊ��ͨIO��  
  P2DIR &= ~0X01;   //������P20 �ڣ�����Ϊ����ģʽ 
  P2INP &=  ~0x01;   //��P20��������,��Ӱ��  
  
}
/****************************
     ������⺯��
*****************************/
uint8 KeyScan(void)
{
  if(KEY1==0)		//���KEY�ǵ͵�ƽ
  {
    Delayms(10);	//��ʱ���� 
    if(KEY1==0)		//���KEY���ǵ͵�ƽ
    {
      while(!KEY1);  //�ȴ��ߵ�ƽ
      return 1;      //���ذ�ť��  �а�������
    }
  }
  if(KEY2==0)		//ͬ�ϣ�������һ������
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
������							
****************************************************************/
void main(void)
{	
	unsigned char str[40];	
	uint8 key=0;
	P1DIR = 0x03; 			//P1����LED
	LED1 = 1;				//��LED1
	LED2 = 0;				//��LED2
    LED3 = 1;				//��LED3
	initUART0();			//���ڳ�ʼ��
    stringlen = strlen((char *)Recdata);//����ַ�������
	UartTX_Send_String(Recdata,stringlen);//�����ַ���
	
	LCD_Init();				//oled ��ʼ��  
    LCD_CLS();				//��ȫ�� 
    LCD_welcome();			//��ʾ��ʼ���ַ�
	Uart2_Send_char(0x11);	//���ڲ���
	
	IRSendInit();
	
	sprintf((char *)str, "0x%04X", HWSendAddcode);//�ѵ�ַ��ת���ַ���
	LCD_P8x16Str(80, 2, str);				//��ʾ��ַ��
				
	while(1)
	{
		key = KeyScan();		//����ɨ��
		if(key==1)
		{
			IR_Sending(0xEA15);		//���ͺ��� ֻ����ָ����Ϳ����ˣ���ַ�뱾ң��������0xff00
			sprintf((char *)str, "0x%04X", 0xEA15);//��ָ����ת���ַ���
			LCD_P8x16Str(80, 4, str);				//��ʾָ����
			LCD_P8x16Str(80, 6, "VOL+ ");			//��ʾָ������
			stringlen = strlen("SendIR��0xEA15 VOL+ \r\n");
			UartTX_Send_String("SendIR��0xEA15 VOL+ \r\n",stringlen);//�������
		}
		else if(key==2)
		{
			IR_Sending(0xF807);		//���ͺ��� ֻ����ָ����Ϳ����ˣ���ַ�뱾ң��������0xff00
			sprintf((char *)str, "0x%04X", 0xF807);//��ָ����ת���ַ���
			LCD_P8x16Str(80, 4, str);				//��ʾָ����
			LCD_P8x16Str(80, 6, "VOL- ");			//��ʾָ������
			stringlen = strlen("SendIR��0xF807 VOL- \r\n");
			UartTX_Send_String("SendIR��0xF807 VOL- \r\n",stringlen);//�������			
			
		}
	}
}
