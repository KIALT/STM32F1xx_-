/**
  **************************************************************************************************
  * @file     exti.c
  * @author   1008 Laboratory
  * @version  V3.0.0
  * @date     2017.7.3
  * @brief    外部中断
  **************************************************************************************************
  * @attention
  *              
  *      
  **************************************************************************************************
  */

/*Includes ----------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "exit.h"
#ifdef __ENABLE_EXIT_


/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/

/*Functions ---------------------------------------------------------------------------------------*/

/**
  * @brief  外部中断GPIO初始化,根据实际情况添加裁剪
  * @param  无
  * @retval 无
  */
void EXTI_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; //定义指针型结构体   :GPIO初始化

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIOB时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //外部中断，需要使能AFIO时钟

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置为上拉输入
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;     //PB.7端口配置
  GPIO_Init(GPIOB, &GPIO_InitStructure);        //根据上面的参数初始化GPIO
}

/**
  * @brief  外部中断初始化,初始化的外部中断要和IO口的中断号对应
  * @param  无
  * @retval 无
  */
void EXTIX_Init(void)
{
  EXTI_InitTypeDef EXTI_InitStructure; //定义指针型结构体   :外部中断初始化
  NVIC_InitTypeDef NVIC_InitStructure; //定义指针型结构体   :中断优先级分组

  EXTI_GPIO_Init(); //外部中断GPIO初始化

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource7); //PB7 中断线以及中断初始化配置
  EXTI_InitStructure.EXTI_Line = EXTI_Line7;                  //中断线标号 ：7
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;         //中断模式
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //上升沿触发
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;                   //中断线使能
  EXTI_Init(&EXTI_InitStructure);                             //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;           //使能PB7外部通道
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02; //抢占优先级 2,
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;        //响应优先级 2
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;              //使能外部中断通道
  NVIC_Init(&NVIC_InitStructure);                              //根据NVIC_InitStructure中指定的参数初始化外设NVIC寄存器
}

/*---------------------------------------------- End ------------------------------------------------*/

#endif