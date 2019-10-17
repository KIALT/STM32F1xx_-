/*******************************************************************************
  @File   : ULtrasonic.h
  @Author : 罗涛
  @Date   : 2019年6月5日 20.12
  @Brief  : 超声波模块驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
  4.使用操作见Example.txt
*******************************************************************************/
#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

/* pulic include ****************************************/
#include "stdint.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stdbool.h"
#include "stdio.h"
/* pirvate include *************************************/
#include "delay.h"
/* Define *********************************************/

#define ULTR_RX_RCC  RCC_APB2Periph_GPIOE
#define ULTR_TX_RCC  RCC_APB2Periph_GPIOE
#define ULTR_RX_PORT GPIOE
#define ULTR_TX_PORT GPIOE                   /* 这个只是对端口简单的定义，根据实际情况进行更改*/
#define ULTR_RX_PIN  GPIO_Pin_2
#define ULTR_TX_PIN  GPIO_Pin_0

#define SOUND_SPEED 345 //声音在空气的速度为s = 331 + 0.6t(介质温度)，这里取温度为25度的速度

/**function ****************************************/
void  ULtrasonic_Init(void);    /* 超声波初始化*/
float get_ULtrasonicVal(void); /* 获得超声波测量的距离（单位为厘米）*/
void  ULtrasonic_star(void);    /* 发送超声引导脉冲 */
void  EXTI2_Init(void);         /* 外部中断初始化 */
#endif

