
/*-----------------------------------------------
  ���ƣ�����S1��LED1����
  ���ݣ�ͨ����������LED������
------------------------------------------------*/
#include <ioCC2530.h> //����ͷ�ļ���һ���������Ҫ�Ķ���ͷ�ļ��������⹦�ܼĴ����Ķ���

#define uint  unsigned int
#define uchar unsigned char 

//������ƵƵĶ˿�
#define LED1 P1_0	//����LED1ΪP10�ڿ���
#define KEY1 P0_1      //KEY1ΪP0.1�ڿ���

//��������
void Delay(unsigned int t); //��������
void InitIO(void);		//��ʼ��LED����IO�ں���
void InitKey();

/*------------------------------------------------
                    ������
------------------------------------------------*/
void main (void)
{                  
  unsigned int CYCLE=600,PWM_LOW=0;//�������ڲ���ֵ
  InitIO();
  InitKey();
  while (1)         //��ѭ��
  {
    
    if(KEY1==0)
    {
      //S1����,һֱ����Ŷ��
      PWM_LOW++;
      if(PWM_LOW>CYCLE)
      {
        PWM_LOW=CYCLE-1;
      }
    }
    else
    {
      PWM_LOW--;
      if(PWM_LOW<1)
      {
        PWM_LOW=1;
      }
    }
    
    if(PWM_LOW==1)
    {
      LED1=0;
    }
    else if(PWM_LOW==CYCLE)
    {
      LED1=1;
    }
    else if(CYCLE>PWM_LOW)
    {
      LED1=1;
      Delay(PWM_LOW);
      LED1=0;
      Delay(CYCLE-PWM_LOW);
    }
  }
  
}
/*------------------------------------------------
 ��ʱ����������������� unsigned int t���޷���ֵ
 unsigned int �Ƕ����޷������α�������ֵ�ķ�Χ��
 0~65535
------------------------------------------------*/
void Delay(unsigned int t)
{
 while(t)
 {
   t--;
   t++;
   t--;
 }
}

/****************************
//��ʼ��IO�ڳ���
*****************************/
void InitIO(void)
{
    P1DIR |= 0x03;  //P10��P11����Ϊ���
}


/****************************
     ������ʼ������
*****************************/
void InitKey()
{
  P0SEL &= ~0x01; //����P0.1Ϊ��ͨIO��
  P0DIR &= ~0X01; //��������P0.1���ϣ���P0.1Ϊ����ģʽ
  P0INP &= ~0x01; //��P0.1��������
}