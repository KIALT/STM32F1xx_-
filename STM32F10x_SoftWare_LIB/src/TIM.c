/**
  *************************************************************************************************
  * @file     time.c
  * @author   罗涛
  * @version  V1.0.0
  * @date     2019.5.31
  * @brief    各定时器初始化,仅限定时
  **************************************************************************************************
  * @attention
  *                
  *  				定时器0~8初始化 定时作用  溢出中断
  *         根据实际情况可裁剪
  * 
  **************************************************************************************************
  */
  
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x.h"
#include "misc.h"
#include "time.h"
 #ifdef  __ENABLE_TIM_
/*Includes ----------------------------------------------------------------------------------------*/
/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/

/*Functions ---------------------------------------------------------------------------------------*/
/**
  * @brief  定时器1初始化
  * @param  arr 初值
  *         psc 分频系数
  * @retval 无
  */
void TIM1_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //TIME1 时钟使能

  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //重复计数设置
  TIM_TimeBaseStructure.TIM_Period = arr;                     //初值重装
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //预分频
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);             //根据上面的参数初始化定时器

  TIM_ClearFlag(TIM1, TIM_FLAG_Update); //清除中断标志位

  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;        //TIM1中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化外设NVIC寄存器

  TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); //TIM1使能中断
  TIM_Cmd(TIM1, ENABLE);                     //使能TIMx外设
}

/**
  * @brief  定时器2初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM2_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //TIME2 时钟使能

  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = arr;                     //初值重装
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //预分频
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             //根据上面的参数初始化定时器

  TIM_ClearFlag(TIM1, TIM_FLAG_Update); //清除中断标志位

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;           //TIM2中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化外设NVIC寄存器

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //TIM2 使能中断
  TIM_Cmd(TIM2, ENABLE);                     //使能TIMx外设
}

/**
  * @brief  定时器3初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //TIME3 时钟使能

  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = arr;                     //初值重装
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //预分频
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //根据上面的参数初始化定时器

  TIM_ClearFlag(TIM1, TIM_FLAG_Update); //清除中断标志位

  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           //TIM3中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化外设NVIC寄存器

  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //TIM3使能中断
  TIM_Cmd(TIM3, ENABLE);                     //使能TIMx外设
}

/**
  * @brief  定时器4初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM4_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //TIME4 时钟使能

  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = arr;                     //初值重装
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //预分频
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             //根据上面的参数初始化定时器

  TIM_ClearFlag(TIM1, TIM_FLAG_Update); //清除中断标志位

  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;           //TIM4中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化外设NVIC寄存器

  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //TIM4使能中断
  TIM_Cmd(TIM4, ENABLE);                     //使能TIMx外设
}

/**
  * @brief  定时器5初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM5_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //TIME5 时钟使能

  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = arr;                     //初值重装
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //预分频
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);             //根据上面的参数初始化定时器

  TIM_ClearFlag(TIM1, TIM_FLAG_Update); //清除中断标志位

 // NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;           //TIM5中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化外设NVIC寄存器

  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); //TIM5 使能中断
  TIM_Cmd(TIM5, ENABLE);                     //使能TIMx外设
}

/**
  * @brief  定时器6初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM6_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //TIME6 时钟使能

  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = arr;                     //初值重装
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //预分频
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);             //根据上面的参数初始化定时器

  TIM_ClearFlag(TIM1, TIM_FLAG_Update); //清除中断标志位

  //NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;           //TIM6中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化外设NVIC寄存器

  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); //TIM6使能中断
  TIM_Cmd(TIM6, DISABLE);                    //失能定时器6
                                             //TIM_Cmd(TIM6, ENABLE);  									//使能TIMx外设
}

/**
  * @brief  定时器7初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM7_Init(u16 arr, u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //TIME7 时钟使能

  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_Period = arr;                     //初值重装
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //预分频
  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);             //根据上面的参数初始化定时器

  TIM_ClearFlag(TIM1, TIM_FLAG_Update); //清除中断标志位

//  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;           //TIM7 中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化外设NVIC寄存器

  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); //TIM7 使能中断
  TIM_Cmd(TIM7, ENABLE);                     //使能TIMx外设
}

/**
  * @brief  定时器8初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM8_Init(u16 arr, u16 psc)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE); //TIME8 时钟使能

  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //重复计数设置
  TIM_TimeBaseStructure.TIM_Period = arr;                     //初值重装
  TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //预分频
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);             //根据上面的参数初始化定时器

  TIM_ClearFlag(TIM1, TIM_FLAG_Update); //清除中断标志位

//  NVIC_InitStructure.NVIC_IRQChannel = TIM8_UP_IRQn;        //TIM8中断
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;        //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);                           //根据指定的参数初始化外设NVIC寄存器

  TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE); //TIM8使能中断
  TIM_Cmd(TIM8, ENABLE);                     //使能TIMx外设
}

/*------------------------------------------------ End ----------------------------------------------------*/
#endif