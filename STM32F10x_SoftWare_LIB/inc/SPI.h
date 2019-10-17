/**
  ***************************************************************************************************
  * @file     spi.h
  * @author   1008 Laboratory
  * @version  V3.0.0
  * @date     2017.6.29
  * @brief    spi通讯；硬件
  ***************************************************************************************************
  * @attention
  *               
  *     	  
  * 
  ***************************************************************************************************
  */
#include <Enable_sys_file.h>
/*Define to prevent recursive inclusion --------------------------------------------------------*/
#ifndef _SPI_H
#define _SPI_H

/*Includes ----------------------------------------------------------------------------------------*/

#include "stm32f10x.h"

/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/

/*Functions ---------------------------------------------------------------------------------------*/

void SPI1_Init(void);             //SPI1初始化
void SPI1_SetSpeed(u8 SpeedSet);  //SPI1 速度设置函数
u8 SPI1_ReadWriteByte(u8 TxData); //SPI1 读写一个字节

void SPI2_Init(void);             //SPI2初始化
void SPI2_SetSpeed(u8 SpeedSet);  //SPI2 速度设置函数
u8 SPI2_ReadWriteByte(u8 TxData); //SPI2 读写一个字节

void SPI3_Init(void);             //SPI3初始化
void SPI3_SetSpeed(u8 SpeedSet);  //SPI3 速度设置函数
u8 SPI3_ReadWriteByte(u8 TxData); //SPI3 读写一个字节

#endif
