/**************************************/
/*������ͨ����ʱ��T1��ѯ��ʽ����LED1��
        ������˸
**************************************/

#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//�������LED�ƵĶ˿�
#define LED1 P1_0	//����LED1ΪP10�ڿ���

//��������
void Delayms(uint xms);		//��ʱ����
void InitLed(void);		//��ʼ��P1��
void InitT1();                  //��ʼ����ʱ��T1

/****************************
//��ʱ����
*****************************/
void Delayms(uint xms)   //i=xms ����ʱi����
{
	uint i, j;
	for (i = xms; i > 0; i--)
		for (j = 587; j > 0; j--);
}

/****************************
//��ʼ������
*****************************/
void InitLed(void)
{
	P1DIR |= 0x03; //P1_0����Ϊ���
	LED1 = 1;       //LED1�Ƴ�ʼ��Ϩ��

}
//��ʱ����ʼ��
void InitT1() //ϵͳ�����ù���ʱ��ʱĬ����2��Ƶ����16MHz
{
	T1CTL = 0x0d;          //128��Ƶ���Զ���װ 0X0000-0XFFFF
	T1STAT = 0x21;         //ͨ��0, �ж���Ч
}

/***************************
//������
***************************/
void main(void)
{
	uchar count;
	InitLed();		//���ó�ʼ������
	InitT1();
	while (1)
	{
		if (IRCON > 0)
		{	IRCON = 0;
			if (++count >= 1)   //Լ1s��������˸
			{
				count = 0;
				LED1 = !LED1;        //LED1��˸
			}
		}
	}
}
