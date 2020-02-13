# include <ioCC2530.h>

#define uint unsigned int 

#define LED1  P1_0 
#define LED2  P1_1

void InitLEDIO(void)
{
    P1DIR |= 0x03;  //P10、P11定义为输出
    LED1 = 1;
    LED2 = 1;
       //LED灯初始化为关   
}
 
void Init_Watchdog(void)
{
	WDCTL = 0x00;
	//时间间隔一秒，看门狗模式
	WDCTL |= 0x08;
	//启动看门狗
}

void  SET_MAIN_CLOCK(int source) 
   {                                  
      if(source) {                            
        CLKCONCMD |= 0x40;          /*RC*/               
        while(!(CLKCONSTA &0X40));  /*待稳*/       
             }                                       
      else {                       
        CLKCONCMD &= ~0x47;        /*晶振*/             
        while((CLKCONSTA &0X40));  /*待稳*/  
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
	}	//喂狗指令（加入后系统不复位，LED1和LED2不再闪烁）
}
