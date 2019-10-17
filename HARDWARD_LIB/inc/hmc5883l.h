/*******************************************************************************
  @File   : hmc5883l.h
  @Author : 罗涛
  @Date   : 2019年6月4日 23.37
  @Brief  : hmc5883l地磁驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
*******************************************************************************/
#ifndef _HMC58831_H
#define _HMC58831_H
/* pulic include  **********************************/
#include "stdint.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stdbool.h"
#include "stdio.h"
/* pirvate include********************************/
#include "iic.h"

#define	HMC5883L_Addr    			0x3c	              //hmc5883l器件地址
#define	HMC5883L_xaddr   			0x03	              //磁场传感器器件地址
 
#define CONFIG_A_REG    0x00    //配置寄存器 A 地址
#define CONFIG_B_REG    0x01    //配置寄存器 B 地址
#define CONFIG_C_REG    0x02    //模式寄存器   地址
#define X_MSB_REG       0x03    //数据输出 X MSB 寄存器 
#define X_LSB_REG       0x04    //数据输出 X LSB 寄存器
#define Z_MSB_REG       0x05    //数据输出 Z MSB寄存器 
#define Z_LSB_REG       0x06    //数据输出 Z LSB 寄存器
#define Y_MSB_REG       0x07    //数据输出 Y MSB 寄存器
#define Y_LSB_REG       0x08    //数据输出 Y LSB 寄存器
/* typedef struct*************************************/
typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
}_Gemag;

/* function ******************************************/
void HMC5883L_init(void);                       //HMC5883L地磁驱动初始化
uint8_t  HMC5883L_get_magnetic(_Gemag *gemag);  /* 获得三轴地磁*/
#endif

