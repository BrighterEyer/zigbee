/*-----------------------------------------------
名称：PWM调光
内容：通过PWM（脉宽调制）调节LED的亮度
------------------------------------------------*/
#include <ioCC2530.h> //包含头文件，一般情况不需要改动，头文件包含特殊功能寄存器的定义

#define uint  unsigned int
#define uchar unsigned char 

//定义控制灯的端口
#define LED0 P1_0	//定义LED1为P10口控制

//函数声明
void Delay(unsigned int t); //函数声明
void InitIO(void);		//初始化LED控制IO口函数

/*------------------------------------------------
主函数
------------------------------------------------*/
void main (void)
{
  unsigned int CYCLE=600,PWM_LOW=0;//定义周期并赋值
  InitIO();
  while (1)         //主循环
  {
    LED0=1;
    Delay(60000);        //特意加延时，可以看到熄灭的过程
    for(PWM_LOW=1;PWM_LOW<CYCLE;PWM_LOW++)
    {
      //PWM_LOW表示低
      //电平时间，这个循环中低电平时长从1累加到CYCLE（周期）的值，即600次
      LED0=0;        //点亮LED  
      Delay(PWM_LOW);//延时长度，600次循环中从1加至599
      LED0=1;        //熄灭LED
      Delay(CYCLE-PWM_LOW);//延时长度，600次循环中从599减至1
    }

    LED0=0;
    for(PWM_LOW=CYCLE-1;PWM_LOW>0;PWM_LOW--)
    {
      //与逐渐变亮相反的过程    
      LED0=0;
      Delay(PWM_LOW);
      LED0=1;
      Delay(CYCLE-PWM_LOW);    
    }
    //主循环中添加其他需要一直工作的程序
  }
}
/*------------------------------------------------
延时函数，含有输入参数 unsigned int t，无返回值
unsigned int 是定义无符号整形变量，其值的范围是
0~65535
------------------------------------------------*/
void Delay(unsigned int t)
{
  while(--t);
}

/****************************
//初始化IO口程序
*****************************/
void InitIO(void)
{
  P1DIR |= 0x1;  //P10定义为输出
}

