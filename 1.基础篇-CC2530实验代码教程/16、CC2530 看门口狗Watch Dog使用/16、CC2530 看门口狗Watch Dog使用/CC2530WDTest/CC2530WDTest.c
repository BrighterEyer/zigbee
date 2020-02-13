# include <ioCC2530.h>

#define uint unsigned int 

#define LED1  P1_0 
#define LED2  P1_1

void InitLEDIO(void)
{
    P1DIR |= 0x03;  //P10��P11����Ϊ���
    LED1 = 1;
    LED2 = 1;
       //LED�Ƴ�ʼ��Ϊ��   
}
 
void Init_Watchdog(void)
{
	WDCTL = 0x00;
	//ʱ����һ�룬���Ź�ģʽ
	WDCTL |= 0x08;
	//�������Ź�
}

void  SET_MAIN_CLOCK(int source) 
   {                                  
      if(source) {                            
        CLKCONCMD |= 0x40;          /*RC*/               
        while(!(CLKCONSTA &0X40));  /*����*/       
             }                                       
      else {                       
        CLKCONCMD &= ~0x47;        /*����*/             
        while((CLKCONSTA &0X40));  /*����*/  
      }                                       
   }
void FeetDog(void)
{
	WDCTL = 0xa0;
	WDCTL = 0x50;
}
void Delay(uint n)
{
	uint i;
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
	for(i=0;i<n;i++);
}


void main(void)
{
	SET_MAIN_CLOCK(0) ;
	InitLEDIO();
	Init_Watchdog();
        
        Delay(10000);
        
	LED1=0;	       
	LED2=0;       
	while(1)
	{
		//FeetDog();	
	}	//ι��ָ������ϵͳ����λ��LED1��LED2������˸��
}
