/****************************************************************************
* �� �� ��: main.c
* ��    ��: ��˼ͨ��
* ��    ��: 2015-06-08
* ��    ��: V1.0
* ��    ��: ������
****************************************************************************/

#include "uart2.h"
#include "lcd12864.h"
#include "IRDecod.h"
#include <stdio.h>


uint8  Recdata[30]="����������\r\n";//��������ַ���
uint16 stringlen;//�ַ�������

extern uint16 HWAddcode,HWComcode;//������� ��ַ�� ָ����ȫ�ֵ��� IRDecod.c
//extern uint16 HWdat[66];

/****************************************************************
������							
****************************************************************/
void main(void)
{	
	unsigned char str[40];	
	uint8 j = 0;
	P1DIR = 0x03; 			//P1����LED
	LED1 = 0;				//��LED1
	LED2 = 0;				//��LED2
    LED3 = 1;				//��LED3
	initUART0();			//���ڳ�ʼ��
    stringlen = strlen((char *)Recdata);//����ַ�������
	UartTX_Send_String(Recdata,stringlen);//�����ַ���
	
	IRInit();				//������ճ�ʼ��
	
	LCD_Init();				//oled ��ʼ��  
    LCD_CLS();				//��ȫ�� 
    LCD_welcome();			//��ʾ��ʼ���ַ�
	Uart2_Send_char(0x11);	//���ڲ���
	while(1)
	{
		if(IR_IRQ==0)		//����������ͷ���ź�
		{
			j = IR_Decoding();//��ʼ����
			if(j==0)
			{
				sprintf((char *)str, "0x%04X", HWAddcode);//�ѵ�ַ��ת���ַ���
				LCD_P8x16Str(80, 2, str);				//��ʾ��ַ��
				sprintf((char *)str, "0x%04X", HWComcode);//��ָ����ת���ַ���
				LCD_P8x16Str(80, 4, str);				//��ʾָ����
				switch(HWComcode)//�ж�ָ��
				{
					case 0x1234:
						LCD_P8x16Str(64, 6, "CH-     ");
						//stringlen = strlen("KeyName��CH-\r\n");
						//UartTX_Send_String("KeyName��CH-\r\n",stringlen);
						break;					
					case 0xBA45:
						LCD_P8x16Str(64, 6, "CH-     ");//��ʾң�ذ�������
						stringlen = strlen("KeyName��CH-\r\n");
						UartTX_Send_String("KeyName��CH-\r\n",stringlen);//�������
						break;
					case 0xB946:
						LCD_P8x16Str(64, 6, "CH      ");
						stringlen = strlen("KeyName��CH\r\n");
						UartTX_Send_String("KeyName��CH\r\n",stringlen);
						break;
					case 0xB847:
						LCD_P8x16Str(64, 6, "CH+     ");
						stringlen = strlen("KeyName��CH+\r\n");
						UartTX_Send_String("KeyName��CH+\r\n",stringlen);
						break;
					case 0xBB44:
						LCD_P8x16Str(64, 6, "PREV    ");
						stringlen = strlen("KeyName��PREV\r\n");
						UartTX_Send_String("KeyName��PREV\r\n",stringlen);
						break;
					case 0xBF40:
						LCD_P8x16Str(64, 6, "NEXT    ");
						stringlen = strlen("KeyName��NEXT\r\n");
						UartTX_Send_String("KeyName��NEXT\r\n",stringlen);
						break;
					case 0xBC43:
						LCD_P8x16Str(64, 6, "PLAY    ");
						stringlen = strlen("KeyName��PLAY\r\n");
						UartTX_Send_String("KeyName��PLAY\r\n",stringlen);
						break;
					case 0xF807:
						LCD_P8x16Str(64, 6, "VOL-    ");
						stringlen = strlen("KeyName��VOL-\r\n");
						UartTX_Send_String("KeyName��VOL-\r\n",stringlen);
						break;
					case 0xEA15:
						LCD_P8x16Str(64, 6, "VOL+    ");
						stringlen = strlen("KeyName��VOL+\r\n");
						UartTX_Send_String("KeyName��VOL+\r\n",stringlen);
						break;
					case 0xF609:
						LCD_P8x16Str(64, 6, "EQ      ");
						stringlen = strlen("KeyName��EQ\r\n");
						UartTX_Send_String("KeyName��EQ\r\n",stringlen);
						break;
					case 0xE916:
						LCD_P8x16Str(64, 6, "0       ");
						stringlen = strlen("KeyName��0\r\n");
						UartTX_Send_String("KeyName��0\r\n",stringlen);
						break;
					case 0xE619:
						LCD_P8x16Str(64, 6, "100+    ");
						stringlen = strlen("KeyName��100+\r\n");
						UartTX_Send_String("KeyName��100+\r\n",stringlen);
						break;
					case 0xF20D:
						LCD_P8x16Str(64, 6, "200+    ");
						stringlen = strlen("KeyName��200+\r\n");
						UartTX_Send_String("KeyName��200+\r\n",stringlen);
					break;
					case 0xF30C:
						LCD_P8x16Str(64, 6, "1       ");
						stringlen = strlen("KeyName��1\r\n");
						UartTX_Send_String("KeyName��1\r\n",stringlen);
						break;
					case 0xE718:
						LCD_P8x16Str(64, 6, "2       ");
						stringlen = strlen("KeyName��2\r\n");
						UartTX_Send_String("KeyName��2\r\n",stringlen);
						break;
					case 0xA15E:
						LCD_P8x16Str(64, 6, "3       ");
						stringlen = strlen("KeyName��3\r\n");
						UartTX_Send_String("KeyName��3\r\n",stringlen);
						break;
					case 0xF708:
						LCD_P8x16Str(64, 6, "4       ");
						stringlen = strlen("KeyName��4\r\n");
						UartTX_Send_String("KeyName��4\r\n",stringlen);
						break;
					case 0xE31C:
						LCD_P8x16Str(64, 6, "5       ");
						stringlen = strlen("KeyName��5\r\n");
						UartTX_Send_String("KeyName��5\r\n",stringlen);
						break;
					case 0xA55A:
						LCD_P8x16Str(64, 6, "6       ");
						stringlen = strlen("KeyName��6\r\n");
						UartTX_Send_String("KeyName��6\r\n",stringlen);
						break;	
					case 0xBD42:
						LCD_P8x16Str(64, 6, "7       ");
						stringlen = strlen("KeyName��7\r\n");
						UartTX_Send_String("KeyName��7\r\n",stringlen);
						break;
					case 0xAD52:
						LCD_P8x16Str(64, 6, "8       ");
						stringlen = strlen("KeyName��8\r\n");
						UartTX_Send_String("KeyName��8\r\n",stringlen);
						break;
					case 0xB54A:
						LCD_P8x16Str(64, 6, "9       ");
						stringlen = strlen("KeyName��9\r\n");
						UartTX_Send_String("KeyName��9\r\n",stringlen);
						break;							
					default:
						LCD_P8x16Str(64, 6, "CodError");
						stringlen = strlen("CodError\r\n");
						UartTX_Send_String("CodError\r\n",stringlen);
						break;
				}
				
			}
		}
	}
}
