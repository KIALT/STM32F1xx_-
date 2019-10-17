/*******************************************************************************
  @File   : HC-05.h
  @Author : 罗涛
  @Date   : 2019年6月8日 10.40
  @Brief  : 蓝牙HC-05驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
  
       1.使用操作见Example.txt
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _HC_05_H
#define _HC_05_H

/* Pulic include ************************************************************/
#include "stdint.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stdbool.h"
#include "stdio.h"
/* private include ********************************************************/
#include "delay.h"
#include "usart.h"

/* Define ***************************************************************/
#define HC05_USART   USART1

#endif