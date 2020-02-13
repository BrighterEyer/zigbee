#include <ioCC2530.h>

#define uint unsigned int
#define uchar unsigned char

//�������LED�ƵĶ˿�
#define LED1 P1_0	//LED1ΪP1.0�ڿ���
#define KEY1 P0_1      //KEY1ΪP0.1�ڿ���

//��������
void Delayms(uint);		//��ʱ����
void InitLed(void);		//��ʼ��LED1
void KeyInit();                 //������ʼ��
uchar KeyScan();                //����ɨ�����

/****************************
��ʱ����
*****************************/
void Delayms(uint xms)   //i=xms ����ʱi����
{
 uint i,j;
 for(i=xms;i>0;i--)
   for(j=587;j>0;j--);
}

/****************************
      LED��ʼ������
*****************************/
void InitLed(void)
{
    P1DIR |= 0x01;  //P1_0����Ϊ���
    LED1 = 1;       //LED1��Ϩ��     
}

/****************************
     ������ʼ������
*****************************/
void InitKey()
{
  P0SEL &= ~0X2;    //����P01Ϊ��ͨIO��  
  P0DIR &= ~0X2;   //������P01 �ڣ�����Ϊ����ģʽ 
  P0INP &=  ~0x2;   //��P01��������,��Ӱ��
}

/****************************
     ������⺯��
*****************************/
uchar KeyScan(void)
{
  if(KEY1==0)
  {
    Delayms(10);
    if(KEY1==0)
    {
      while(!KEY1);  //���ּ��
      return 1;      //�а�������
    }
  }
  return 0;           //�ް�������
}

/***************************
      ������
***************************/
void main(void)
{
  InitLed();		//���ó�ʼ������
  InitKey();
  while(1)
  {
   if(KeyScan())       //�����ı�LED״̬
     LED1=~LED1;       
  }
}
