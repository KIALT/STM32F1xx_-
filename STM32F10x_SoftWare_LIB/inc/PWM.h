/**
  **************************************************************************************************
  * @file     pwm.h
  * @author   1008 Laboratory
  * @version  V3.0.0
  * @date     2017.6.29
  * @brief    初始化定时器2为PWM模式  
  **************************************************************************************************
  * @attention
  *                
  *  				PWM_update();函数为更新PWM输出至电机
  * 
  **************************************************************************************************
  */
  #include <Enable_sys_file.h>
/* Define to prevent recursive inclusion ----------------------------------------------------------*/
#ifndef _PWM_H
#define _PWM_H

/*Includes ----------------------------------------------------------------------------------------*/

#include "stm32f10x.h"

/*Defines -----------------------------------------------------------------------------------------*/

//PWM最大阈值
#define  TIM1_PWM_MAX  2000  
#define  TIM2_PWM_MAX  2000 
#define  TIM3_PWM_MAX  2000 
#define  TIM4_PWM_MAX  2000 
#define  TIM5_PWM_MAX  2000 
#define  TIM8_PWM_MAX  2000 

//作用通道
#define TIM1_PWM_OC1   TIM1->CCR1
#define TIM1_PWM_OC2   TIM1->CCR2
#define TIM1_PWM_OC3   TIM1->CCR3
#define TIM1_PWM_OC4   TIM1->CCR4

#define TIM2_PWM_OC1   TIM2->CCR1
#define TIM2_PWM_OC2   TIM2->CCR2
#define TIM2_PWM_OC3   TIM2->CCR3
#define TIM2_PWM_OC4   TIM2->CCR4

#define TIM3_PWM_OC1   TIM3->CCR1
#define TIM3_PWM_OC2   TIM3->CCR2
#define TIM3_PWM_OC3   TIM3->CCR3
#define TIM3_PWM_OC4   TIM3->CCR4

#define TIM4_PWM_OC1   TIM4->CCR1
#define TIM4_PWM_OC2   TIM4->CCR2
#define TIM4_PWM_OC3   TIM4->CCR3
#define TIM4_PWM_OC4   TIM4->CCR4

#define TIM5_PWM_OC1   TIM5->CCR1
#define TIM5_PWM_OC2   TIM5->CCR2
#define TIM5_PWM_OC3   TIM5->CCR3
#define TIM5_PWM_OC4   TIM5->CCR4

#define TIM8_PWM_OC1   TIM8->CCR1
#define TIM8_PWM_OC2   TIM8->CCR2
#define TIM8_PWM_OC3   TIM8->CCR3
#define TIM8_PWM_OC4   TIM8->CCR4

/*Variables ---------------------------------------------------------------------------------------*/
/*Functions ---------------------------------------------------------------------------------------*/

void TIM1_PWM_Init(u16 arr,u16 psc);							//TIM1 PWM初始化
void TIM2_PWM_Init(u16 arr,u16 psc);							//TIM2 PWM初始化
void TIM3_PWM_Init(u16 arr,u16 psc);							//TIM3 PWM初始化
void TIM4_PWM_Init(u16 arr,u16 psc);							//TIM4 PWM初始化
void TIM5_PWM_Init(u16 arr,u16 psc);							//TIM5 PWM初始化
void TIM8_PWM_Init(u16 arr,u16 psc);							//TIM8 PWM初始化

void TIM1_PWM_update(s16 PWM1,s16 PWM2,s16 PWM3,s16 PWM4);	    //TIM1_PWM更新函数
void TIM2_PWM_update(s16 PWM1,s16 PWM2,s16 PWM3,s16 PWM4);	    //TIM2_PWM更新函数
void TIM3_PWM_update(s16 PWM1,s16 PWM2,s16 PWM3,s16 PWM4);	    //TIM3_PWM更新函数
void TIM4_PWM_update(s16 PWM1,s16 PWM2,s16 PWM3,s16 PWM4);	    //TIM4_PWM更新函数
void TIM5_PWM_update(s16 PWM1,s16 PWM2,s16 PWM3,s16 PWM4);	    //TIM5_PWM更新函数
void TIM8_PWM_update(s16 PWM1,s16 PWM2,s16 PWM3,s16 PWM4);	    //TIM8_PWM更新函数


#endif

/*---------------------------------------------- End ------------------------------------------------*/
