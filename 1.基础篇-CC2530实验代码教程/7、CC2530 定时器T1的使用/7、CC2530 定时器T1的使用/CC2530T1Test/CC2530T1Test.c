
#include <ioCC2530.h>
#define uint   unsigned  int
#define uchar  unsigned  char

#define LED1   P1_0	        //����LED1ΪP10�ڿ���
#define LED2   P1_1	        //����LED2ΪP11�ڿ���
#define LED3   P0_4	        //����LED3ΪP04�ڿ���

uint counter=0;				//ͳ���������
uint LEDFlag;				//��־�Ƿ�Ҫ��˸

void InitialT1test(void);               //��ʼ����������

/****************************
//T1��ʼ������
***************************/
void InitialT1test(void)
{
	//��ʼ��LED���ƶ˿�P1
	P1DIR = 0x03; 	         //P10 P11 Ϊ���
    P0DIR = 0x10;            //P04Ϊ���

    //��Ĭ��Ϊ��
	LED1 = 1;
	LED2 = 1;
    LED3 = 1;
        
	//��ʼ��������1
	T1CTL = 0x05;	
    T1STAT = 0x21;          //ͨ��0,�ж���Ч,8��Ƶ;�Զ���װģʽ(0x0000->0xffff)        
}
/***************************
//������
***************************/
void main()
{
  InitialT1test(); 	 //���ó�ʼ������
  while(1)   	         //��ѯ���
  {
    if(IRCON > 0)
    {
      IRCON = 0;                //�������־     
      counter++;
      
      if(counter==15)            //�жϼ�����Լ0.25s
      {
        counter =0;
        LEDFlag = !LEDFlag;
      }
    }
    
    if(LEDFlag)
    {
      LED2 =  LED1;
      LED3 = !LED2;
      LED1 = !LED1;	   // ÿ 1s LED����˸һ�� 
      LEDFlag = !LEDFlag;   // ��˸��־������0
    }                
  }
}


