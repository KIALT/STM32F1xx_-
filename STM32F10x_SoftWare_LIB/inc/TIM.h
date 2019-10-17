/**
  *************************************************************************************************
  * @file     time.h
  * @author   罗涛
  * @version  V3.0.0
  * @date     2019.5.31
  * @brief    各定时器初始化,仅限定时
  **************************************************************************************************
  * @attention
  *                
  *  				None
  * 
  **************************************************************************************************
  */
  
  #include <Enable_sys_file.h>
/* Define to prevent recursive inclusion ----------------------------------------------------------*/
#ifndef _TIME_H
#define _TIME_H
 
/*Includes ----------------------------------------------------------------------------------------*/
#include "stm32f10x.h"

/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/
/*Functions ---------------------------------------------------------------------------------------*/

void TIM1_Init(u16 arr,u16 psc);	//定时器1初始化
void TIM2_Init(u16 arr,u16 psc);	//定时器2初始化
void TIM3_Init(u16 arr,u16 psc);	//定时器3初始化
void TIM4_Init(u16 arr,u16 psc);	//定时器4初始化
void TIM5_Init(u16 arr,u16 psc);	//定时器5初始化
void TIM6_Init(u16 arr,u16 psc);	//定时器6初始化
void TIM7_Init(u16 arr,u16 psc);	//定时器7初始化
void TIM8_Init(u16 arr,u16 psc);	//定时器8初始化

#endif


/*---------------------------------------------- End ------------------------------------------------*/

