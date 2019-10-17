/*******************************************************************************
  @File   : BMP085.h
  @Author : 罗涛
  @Date   : 2019年6月4日 22.54
  @Brief  : BMP085气压计的驱动
  @Others : none 
  @History: none
  @Modification: V1.0.0
  
       1.使用操作见Example.txt
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BMP085_H
#define _BMP085_H
/* Pulic include ***********************************************/
#include "stdint.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stdbool.h"
#include "stdio.h"
#include <math.h>
/* pirvate include*********************************************/
#include "iic.h"
/* Define resgister*******************************************/
#define AC1_MSB_ADDR     0xAA       //AC1高8位地址
#define AC1_LSB_ADDR     0xAB       //AC1低8位地址
#define AC2_MSB_ADDR     0xAC       //AC2高8位地址 
#define AC2_LSB_ADDR     0xAD       //AC2低8位地址
#define AC3_MSB_ADDR     0xAE       //AC3高8位地址
#define AC3_LSB_ADDR     0xAF       //AC3低8位地址
#define AC4_MSB_ADDR     0xB0       //AC4高8位地址
#define AC4_LSB_ADDR     0xB1       //AC4低8位地址
#define AC5_MSB_ADDR     0xB2       //AC5高8位地址
#define AC5_LSB_ADDR     0xB3       //AC5低8位地址
#define AC6_MSB_ADDR     0xB4       //AC6高8位地址
#define AC6_LSB_ADDR     0xB5       //AC6低8位地址
#define B1_MSB_ADDR      0xB6       //B1高8位地址
#define B1_LSB_ADDR      0xB7       //B1低8位地址
#define B2_MSB_ADDR      0xB8       //B2高8位地址
#define B2_LSB_ADDR      0xB9       //B2低8位地址
#define MB_MSB_ADDR      0xBA       //MB高8位地址
#define MB_LSB_ADDR      0xBB       //MB低8位地址
#define MC_MSB_ADDR      0xBC       //MC高8位地址
#define MC_LSB_ADDR      0xBD       //MC低8位地址
#define MD_MSB_ADDR      0xBE       //MD高8位地址
#define MD_LSB_ADDR      0xBF       //MD低8位地址

#define BMP085_ADDR      0xee      //气压传感器器件地址

#define OSS          0             //大气压转换时间 ，有0~3选择

typedef struct {
    short ac1;
    short ac2;
    short ac3;
    uint16_t ac4;
    uint16_t ac5;
    uint16_t ac6;      //BMP085的校准变量
    short b1;
    short b2;
    short mb;
    short mc;
    short md;
}_Bmp085Param;       //bmp085校检结构体 

/*External variable declaration ****************************************/
extern _Bmp085Param bmp085Param;

/***function************************************************************/
void   BMP085_Init(_Bmp085Param * bmp085Param);          /* 读取BMP085的校检系数*/
double BMP085_Get_Altitude(_Bmp085Param *bmp085Param);   /* 获取海抜值*/
short  BMP_read_byte(uint8_t reg, uint8_t times);        
#endif 

