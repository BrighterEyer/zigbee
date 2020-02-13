/****************************************************************************
* 文 件 名: lcd12864.h
* 作    者: 创思通信
* 修    订: 2015-06-08
* 版    本: V1.0
* 描    述: LCD显示屏头文件
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