/*******************************************************************************
  @File   : LCD_device.h
  @Author : 罗涛
  @Date   : 2019年6月2日 22.00
  @Brief  : LCD设备驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  _LCD_DEVICE_H
#define  _LCD_DEVICE_H
/* Pulic include ******************************************/
#include "stdint.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stdbool.h"
#include "stdarg.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
/*pirvate include ***************************************/
#include "delay.h"
/* Define************************************************/
#define BUFF_SIZE  20           /* 缓冲区的大小*/
#define SID_RCC    RCC_APB2Periph_GPIOE
#define SCK_RCC    RCC_APB2Periph_GPIOE
#define CS_RCC     RCC_APB2Periph_GPIOE
#define SID_PORT   GPIOE        /* 串行数据(RW)端口*/ 
#define SCK_PORT   GPIOE        /* 串行时钟(EN)端口*/
#define CS_PORT    GPIOE        /* 串行片(RS)选端口*/  /* 这里只是简单的定义，请根据使用自行修改这些参数*/
#define SID_PIN    GPIO_Pin_2   /* 串行数据引脚*/  
#define SCK_PIN    GPIO_Pin_4   /* 串行时钟引脚*/
#define CS_PIN     GPIO_Pin_0   /* 串行片选引脚*/

#define SID_OUT_H()  GPIO_SetBits  (SID_PORT, SID_PIN)
#define SID_OUT_L()  GPIO_ResetBits(SID_PORT, SID_PIN)
#define SCK_OUT_H()  GPIO_SetBits  (SCK_PORT, SCK_PIN)
#define SCK_OUT_L()  GPIO_ResetBits(SCK_PORT, SCK_PIN)
#define CS_OUT_H()   GPIO_SetBits  (CS_PORT,  CS_PIN)
#define CS_OUT_L()   GPIO_ResetBits(CS_PORT, CS_PIN)

/* function********************************************/
void LCD_init(void);                                     /*LCD初始化*/
void LCD_clean(void);                                    /*LCD清屏*/
void LCD12864_Display(char x, char y, char *fomat, ...); /* LCD清屏函数*/
bool strinsert(int index, char *str1,char *str2);       /*字符串插入函数*/
void Display(char *str);
void LCD_pos(char x, char y);
#endif

