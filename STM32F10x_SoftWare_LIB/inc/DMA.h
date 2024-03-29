/**
  **************************************************************************************************
  * @file     dma.h
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
#ifndef _DMA_H
#define _DMA_H

/*Includes ----------------------------------------------------------------------------------------*/

#include "stm32f10x.h"

/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/

/*Functions ---------------------------------------------------------------------------------------*/

void DMA1_ADC1_Init(u32 Adc_DR_Addr, u32 Ad_Mybuf, u16 Buf_Size);
void DMA1_SPI1RX_Init(u32 Adc_DR_Addr, u32 Ad_Mybuf, u16 Buf_Size);

#endif

/*---------------------------------------------- End ------------------------------------------------*/
