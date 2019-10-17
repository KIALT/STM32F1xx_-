/*******************************************************************************
  @File   : OLED.h
  @Author : 罗涛
  @Date   : 2019年6月6日 20.31
  @Brief  : IIC驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
  
       1.使用操作见Example.txt
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef  _OLED_H
#define  _OLED_H
/* pulic include **************************************************************/
#include "stdint.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stdbool.h"
#include "stdio.h"
/* pirvate include************************************************************/
#include "iic.h"
/* Define ********************************************************************/
#define  OLED_IIC 

#define OLED_CLK_RCC   RCC_APB2Periph_GPIOC
#define OLED_MOSI_RCC  RCC_APB2Periph_GPIOC
#define OLED_CS_RCC    RCC_APB2Periph_GPIOC
#define OLED_DC_RCC    RCC_APB2Periph_GPIOC

#define OLED_CLK_PORT  GPIOC
#define OLED_MOSI_PORT GPIOC
#define OLED_CS_PORT   GPIOC                         /* 这里只是对端口简单的定义 */
#define OLED_DC_PORT   GPIOC                         /* 根据实际情况更改*/

#define OLED_CLK_Pin   GPIO_Pin_0              /*接OLED的 D0*/
#define OLED_MOSI_Pin  GPIO_Pin_1              /*接OLED的 D1*/  
#define OLED_CS_Pin    GPIO_Pin_2              /*接OLED的 CS*/
#define OLED_DC_Pin    GPIO_Pin_3              /*接OLED的 DC*/

#define OLED_CLK_OUT_H()   GPIO_SetBits  (OLED_CLK_PORT , OLED_CLK_Pin)
#define OLED_CLK_OUT_L()   GPIO_ResetBits(OLED_CLK_PORT , OLED_CLK_Pin)
#define OLED_MOSI_OUT_H()  GPIO_SetBits  (OLED_MOSI_PORT, OLED_MOSI_Pin)
#define OLED_MOSI_OUT_L()  GPIO_ResetBits(OLED_MOSI_PORT, OLED_MOSI_Pin)
#define OLED_CS_OUT_H()    GPIO_SetBits  (OLED_CS_PORT  , OLED_CS_Pin)
#define OLED_CS_OUT_L()    GPIO_ResetBits(OLED_CS_PORT  , OLED_CS_Pin)
#define OLED_DC_OUT_H()    GPIO_SetBits  (OLED_DC_PORT  , OLED_DC_Pin)
#define OLED_DC_OUT_L()    GPIO_ResetBits(OLED_DC_PORT  , OLED_DC_Pin)

/* function ******************************************************************/
void OLED_Init(void);                                                                    /* OLED初始化*/
void OLED_SetPos(uint8_t x, uint8_t y);                                                  /* 设置起始位置*/
void OLED_Fill(uint8_t fill_data);                                                       /* OLED全屏填充 */
void OLED_CLS(void);                                                                     /* OLED清屏*/
void OLED_ON(void);                                                                      /* 唤醒OLED*/
void OLED_OFF(void);                                                                     /* 关闭OLED*/
void OLED_PutPixel(uint8_t x, uint8_t y);                                                /* OLED绘制一个点 */
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize);                 /* OLED显示ASCII字符  有6*8和8*16大小可选 */
void OLED_ShowNum(uint8_t x, uint8_t y, uint8_t Number, uint8_t TextSize, int N);        /*OLED在指定的地址显示整数数字*/
void OLED_Show_FloatNum(uint8_t x, uint8_t y, double real, uint8_t TextSize, uint8_t N); /*OLED在指定的地址显示浮点数数字 */
void OLED_ShowCN(uint8_t x, uint8_t y, uint8_t N);                                       /*OLED显示汉字  16*16 */
void OLED_ShowBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[]);        /* OLED显示图片 */
#endif 