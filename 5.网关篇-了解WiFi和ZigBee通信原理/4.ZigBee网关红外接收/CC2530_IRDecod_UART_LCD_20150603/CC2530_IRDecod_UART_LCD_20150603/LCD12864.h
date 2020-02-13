/****************************************************************************
* �� �� ��: lcd12864.h
* ��    ��: ��˼ͨ��
* ��    ��: 2015-06-08
* ��    ��: V1.0
* ��    ��: LCD��ʾ��ͷ�ļ�
****************************************************************************/
#ifndef LCD12864_H
#define LCD12864_H

#include <iocc2530.h>
#include <string.h>
#include "hal_types.h"


void LCD_Init(void);
void LCD_CLS(void);
void LCD_welcome();
void LCD_P8x16Str(unsigned char x, unsigned char y,unsigned char ch[]);

#endif