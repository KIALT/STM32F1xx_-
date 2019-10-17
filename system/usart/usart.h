/*******************************************************************************
  @File   : Usart.h
  @Author : 罗涛
  @Date   : 2019年6月7日 13.42
  @Brief  : 串口综合驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
  
       1.使用操作见Example.txt
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

/* pulicd include ************************************************************/
#include "misc.h"
#include "stdio.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stdarg.h"
#include "string.h"
/* Define ******************************************************************/
#define USART1_CONFIG  1        /* 串口标号*/
#define USART2_CONFIG  2 
#define USART3_CONFIG  3
#define USART4_CONFIG  4

#define BUFF_SIZE     100     /*串口接受buffer大小*/
void USART_Config(uint8_t Usart_num, uint32_t baud);
void Usart_Send(USART_TypeDef *USARTx,const char* fomat,...);
#endif


