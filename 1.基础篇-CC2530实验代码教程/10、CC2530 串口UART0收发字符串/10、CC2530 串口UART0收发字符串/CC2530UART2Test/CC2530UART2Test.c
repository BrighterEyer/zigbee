#include <iocc2530.h>
#include <string.h>
#define uint unsigned int
#define uchar unsigned char

//������ƵƵĶ˿�
#define LED1 P1_0
#define LED2 P1_1
#define LED3 P0_4

void initUART0(void);
void InitialAD(void);
void UartTX_Send_String(uchar *Data,int len);

uchar Recdata[30]="hello zigbee!\r\n";
uchar RXTXflag = 1;
uchar temp;
uint  datanumber = 0;
uint  stringlen;

/****************************************************************
���ڷ����ַ�������				
****************************************************************/
void UartTX_Send_String(uchar *Data,int len)
{
  int j;
  for(j=0;j<len;j++)
  {
    U0DBUF = *Data++;
    while(UTX0IF == 0);
    UTX0IF = 0;
  }
}

/****************************************************************
��ʼ������0����					
****************************************************************/
void initUART0(void)
{
    CLKCONCMD &= ~0x40;                         //����ϵͳʱ��ԴΪ32MHZ����
    while(CLKCONSTA & 0x40);                    //�ȴ������ȶ�
    CLKCONCMD &= ~0x47;                         //����ϵͳ��ʱ��Ƶ��Ϊ32MHZ
   
    PERCFG = 0x00;				//λ��1 P0��
    P0SEL = 0x0c;				//P0��������
    P2DIR &= ~0XC0;                             //P0������ΪUART0    
    
    U0CSR |= 0x80;				//��������ΪUART��ʽ
    U0GCR |= 11;				
    U0BAUD |= 216;				//��������Ϊ115200
    UTX0IF = 1;                                 //UART0 TX�жϱ�־��ʼ��λ1 
    
    U0CSR |= 0X40;				//�������
    IEN0 |= 0x84;				//�����жϣ������ж�
}

/****************************************************************
������							
****************************************************************/
void main(void)
{	
	P1DIR = 0x03; 				//P1����LED
	LED1 = 1;
	LED2 = 1;				//��LED
        LED3 = 1;
	initUART0();
        stringlen = strlen((char *)Recdata);
	UartTX_Send_String(Recdata,stringlen);	            
	while(1)
	{
          if(RXTXflag == 1)			     //����״̬
          {
            
            if( temp != 0)
            {
                LED2 = 0;				     //����״ָ̬ʾ
                if((temp!='#')&&(datanumber<50))     //������������Ϊ�����ַ�������ܽ���50���ַ�
                {          
                  Recdata[datanumber++] = temp;
                }
                else
                {
                  RXTXflag = 3;                      //���뷢��״̬
                }
                
                if(datanumber == 50)
                  RXTXflag = 3;
                
              temp  = 0;	
            }
          }
          if(RXTXflag == 3)			//����״̬
          {
            UartTX_Send_String("send:",5);
            
            LED1 = 0;			        //����״ָ̬ʾ
            
            U0CSR &= ~0x40;			//��������
            UartTX_Send_String(Recdata,datanumber);
            UartTX_Send_String("\r\n",2);
            U0CSR |= 0x40;			//�������
            
            RXTXflag = 1;		        //�ָ�������״̬
            datanumber = 0;			//ָ���0
            LED1 = 1;			        //�ط���ָʾ
            LED2 = 1;	
            memset(Recdata, 0, sizeof(Recdata));
          }
	}
}
/****************************************************************
���ڽ���һ���ַ�:һ�������ݴӴ��ڴ���CC2530,������жϣ������յ������ݸ�ֵ������temp.
****************************************************************/
#pragma vector = URX0_VECTOR
 __interrupt void UART0_ISR(void)
 {
 	URX0IF = 0;				//���жϱ�־
	temp = U0DBUF;                          
 }
