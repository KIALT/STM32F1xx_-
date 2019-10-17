/*******************************************************************************
  @File   : IIC.h
  @Author : 罗涛
  @Date   : 2019年5月30日 22.18.30
  @Brief  : IIC驱动
  @Others : none 
  @History: none
  @Modification: V1.0.0
  
       1.使用操作见Example.txt
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _IIC_H
#define _IIC_H

/* Public includes ----------------------------------------------------------*/
#include "stdint.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stdbool.h"
#include "stdio.h"
/* Pirvate includes --------------------------------------------------------*/
#include "delay.h"
/* Define ------------------------------------------------------------------*/
#define IIC_SDA_RCC RCC_APB2Periph_GPIOB
#define IIC_SCL_RCC RCC_APB2Periph_GPIOB

#define IIC_SDA_PORT GPIOB
#define IIC_SCL_PORT GPIOB

#define IIC_SDA_PIN GPIO_Pin_13
#define IIC_SCL_PIN GPIO_Pin_14

#define GPIOX  GPIOB
/* 控制一个Io口,CRH控制7~15 */
/* CRL控制0~7位 请根据你IO来选择是CRH或者CRL*/
/* stm32 io的输入输出是CR寄存器，每4位 */
#define SDAout(x)                                                                             \
  {                                            /* stm32 io的输入输出是CR寄存器，每4位 */      \
    GPIOX->CRH &= (uint32_t)~(15 << (4 * x));  /* 控制一个Io口,CRH控制7~15 */                 \
    GPIOX->CRH |= (uint32_t)3    << (4 * x);   /* CRL控制0~7位 请根据你IO来选择是CRH或者CRL*/ \
  }
#define SDAin(x)                                                                              \
  {                                            /* 因为每4位控制一个IO口所以 */                \
    GPIOX->CRH &= (uint32_t)~(15 << (4 * x));  /* 根据你使用的IO拉改变4*后面的数值 */         \
    GPIOX->CRH |= (uint32_t)8    << (4 * x);   /* 这里默认PA1口 */                            \
  }
#define SDAOut() SDAout(5)                    /*使用不带参数的宏，代替带参数的宏，更好的移植IIC代码*/            
#define SDAIn()  SDAin(5)	                    /*先修改上面GPIOX端口，在根据你使用的IO口来设定X的值*/

#define SDA_OUT_H()   GPIO_SetBits  (IIC_SDA_PORT,IIC_SDA_PIN)	
#define SDA_OUT_L()   GPIO_ResetBits(IIC_SDA_PORT,IIC_SDA_PIN)
#define SCL_OUT_H()   GPIO_SetBits  (IIC_SCL_PORT,IIC_SCL_PIN)	
#define SCL_OUT_L()   GPIO_ResetBits(IIC_SCL_PORT,IIC_SCL_PIN)
#define READ_SDA()    GPIO_ReadInputDataBit(IIC_SDA_PORT, IIC_SDA_PIN)
/* type typedef ------------------------------------------------------------*/

/*  function ------------------------------------------------------------*/
void    IIC_Init(void);                                                                          /* IIC端口初始化*/
void    IIC_Stop(void);
uint8_t IICDevice_ReadByte(uint8_t SlaveAddr, uint8_t interAddr);                                /* IIC设备读取一个字节 */
uint8_t IICDevice_ReadBytes(uint8_t SlaveAddr, uint8_t interAddr, uint8_t len, uint8_t *rbuf);   /* IIC设备读取多个字节 */
uint8_t IICDevice_WriteByte(uint8_t SlaveAddr, uint8_t interAddr, uint8_t cmd);                  /* IIC设备写入一个字节 */
uint8_t IICDevice_WriteBytes(uint8_t SlaveAddr, uint8_t interAddr, uint8_t len, uint8_t *wbuf);  /* IIC设备写入多个字节 */
#endif
