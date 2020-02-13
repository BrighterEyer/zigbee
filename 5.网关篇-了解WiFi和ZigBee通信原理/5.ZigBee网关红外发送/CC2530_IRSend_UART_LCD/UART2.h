#ifndef UART2_H
#define UART2_H

#include <iocc2530.h>
#include <string.h>
#include "hal_types.h"

//定义控制灯的端口
#define LED1 P1_0
#define LED2 P1_1
#define LED3 P0_4

void initUART0(void);
void InitialAD(void);
void UartTX_Send_String(uint8 *Data,int len);
void Uart2_Send_char(uint8 Data);
void Uart2_Send_int(uint16 Data);

#endif

