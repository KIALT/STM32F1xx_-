/**
  **************************************************************************************************
  * @file     exti.h
  * @author   1008 Laboratory
  * @version  V3.0.0
  * @date     2017.7.2
  * @brief    
  **************************************************************************************************
  * @attention
  *                
  *  				
  * 
  **************************************************************************************************
  */
#include <Enable_sys_file.h>
/* Define to prevent recursive inclusion ----------------------------------------------------------*/
#ifndef _EXTI_H
#define _EXTI_H

/*Includes ----------------------------------------------------------------------------------------*/

#include "stm32f10x.h"

/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/

/*Functions ---------------------------------------------------------------------------------------*/

void EXTI_GPIO_Init(void); //IO初始化
void EXTIX_Init(void);     //外部中断初始化

#endif

/*---------------------------------------------- End ------------------------------------------------*/
