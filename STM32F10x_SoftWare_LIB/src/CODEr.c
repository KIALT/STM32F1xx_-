/**
  **************************************************************************************************
  * @file     coder.c
  * @author   1008 Laboratory
  * @version  V3.0.0
  * @date     2017.7.3
  * @brief    定时器编码器模式初始化
  **************************************************************************************************
  * @attention
  *           1.  所有定时器的编码器模式统一用CH1和CH2
  *           2.  不用通道1和通道2需自行修改初始化函数
  *			      3.  定时器1和定时器8没验证
  **************************************************************************************************
  */

/*Includes ----------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "coder.h"
#ifdef __ENABLE_CODER_ 

/*Defines -----------------------------------------------------------------------------------------*/
/*Variables ---------------------------------------------------------------------------------------*/
/*Functions ---------------------------------------------------------------------------------------*/

/**
  * @brief  初始化定时器1编码器模式  : PA8\PA9
  * @param  无
  * @retval 无
  */
void TIM1_CODER_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);  //使能定时器1时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA口时钟

  GPIO_StructInit(&GPIO_InitStructure);                  //前A相  后B相
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9; //PA8,PA9端口设置:TIM1_CH1/CH2-PA8/PA9
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);                 //根据上面的参数初始化IO口

  TIM_DeInit(TIM1);                               //将外设TIM1的寄存器重设为缺省值
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); //把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入

  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                  //自动重装载值65536
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //设置分频因子
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //重复计数设置
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);             //根据上面的参数初始化TIME1

  TIM_EncoderInterfaceConfig //设置编码器模式
      (
          TIM1,                  //定时器1的编码器
          TIM_EncoderMode_TI12,  //输入模式3：IC1FP1映射到TI1上.IC2FP2映射到TI2上
          TIM_ICPolarity_Rising, //极性:TI1正向,上升沿有效
          TIM_ICPolarity_Rising  //极性:TI2正向,上升沿有效
      );

  TIM_SetCounter(TIM1, 0); //计数器新值0
  TIM_Cmd(TIM1, ENABLE);   //定时器1使能
}

/**
  * @brief  初始化定时器2编码器模式
  * @param  无
  * @retval 无
  */
void TIM2_CODER_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  //使能定时器2时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA口时钟

  GPIO_StructInit(&GPIO_InitStructure);                  //前A相  后B相
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //PA0,PA1端口设置:TIM2_CH1/CH2-PA0/PA1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);                 //根据上面的参数初始化IO口

  TIM_DeInit(TIM2);                               //将外设TIM2的寄存器重设为缺省值
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); //把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入

  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;                  //自动重装载值65536
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //设置分频因子
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);             //根据上面的参数初始化TIME2

  TIM_EncoderInterfaceConfig //设置编码器模式
      (
          TIM2,                  //定时器2的编码器
          TIM_EncoderMode_TI12,  //输入模式3：IC1FP1映射到TI1上.IC2FP2映射到TI2上
          TIM_ICPolarity_Rising, //极性:TI1正向,上升沿有效
          TIM_ICPolarity_Rising  //极性:TI2正向,上升沿有效
      );

  TIM_SetCounter(TIM2, 0); //计数器新值0
  TIM_Cmd(TIM2, ENABLE);   //定时器2使能
}

/**
  * @brief  初始化定时器3编码器模式
  * @param  无
  * @retval 无
  */
void TIM3_CODER_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //使能定时器3时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA口时钟

  GPIO_StructInit(&GPIO_InitStructure);                  //前A相  后B相
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //PA6,PA7端口设置:TIM3_CH1/CH2-PA6/PA7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);                 //根据上面的参数初始化IO口

  TIM_DeInit(TIM3);                               //将外设TIM3的寄存器重设为缺省值
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); //把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入

  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                  //自动重装载值65536
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //设置分频因子
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //根据上面的参数初始化TIME3

  TIM_EncoderInterfaceConfig //设置编码器模式
      (
          TIM3,                  //定时器3的编码器
          TIM_EncoderMode_TI12,  //输入模式3：IC1FP1映射到TI1上.IC2FP2映射到TI2上
          TIM_ICPolarity_Rising, //极性:TI1正向,上升沿有效
          TIM_ICPolarity_Rising  //极性:TI2正向,上升沿有效
      );

  TIM_SetCounter(TIM3, 0); //计数器新值0
  TIM_Cmd(TIM3, ENABLE);   //定时器3使能
}

/**
  * @brief  初始化定时器4编码器模式
  * @param  无
  * @retval 无
  */
void TIM4_CODER_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  //使能定时器4时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB口时钟

  GPIO_StructInit(&GPIO_InitStructure);                  //前A相  后B相
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //PB6,PB7端口设置:TIM4_CH1/CH2-PB6/PB7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
  GPIO_Init(GPIOB, &GPIO_InitStructure);                 //根据上面的参数初始化IO口

  TIM_DeInit(TIM4);                               //将外设TIM4的寄存器重设为缺省值
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); //把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入

  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                  //自动重装载值65536
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //设置分频因子
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);             //根据上面的参数初始化TIME4

  TIM_EncoderInterfaceConfig //设置编码器模式
      (
          TIM4,                  //定时器4的编码器
          TIM_EncoderMode_TI12,  //输入模式3：IC1FP1映射到TI1上.IC2FP2映射到TI2上
          TIM_ICPolarity_Rising, //极性:TI1正向,上升沿有效
          TIM_ICPolarity_Rising  //极性:TI2正向,上升沿有效
      );

  TIM_SetCounter(TIM4, 0); //计数器新值0
  TIM_Cmd(TIM4, ENABLE);   //定时器4使能
}

/**
  * @brief  初始化定时器5编码器模式
  * @param  无
  * @retval 无
  */
void TIM5_CODER_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);  //使能定时器1时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA口时钟

  GPIO_StructInit(&GPIO_InitStructure);                  //前A相  后B相
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //PA0,PA1端口设置:TIM2_CH1/CH2-PA0/PA1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);                 //根据上面的参数初始化IO口							 //根据上面的参数初始化IO口

  TIM_DeInit(TIM5);                               //将外设TIM5的寄存器重设为缺省值
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); //把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入

  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                  //自动重装载值65536
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //设置分频因子
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);             //根据上面的参数初始化TIME5

  TIM_EncoderInterfaceConfig //设置编码器模式
      (
          TIM5,                  //定时器5的编码器
          TIM_EncoderMode_TI12,  //输入模式3：IC1FP1映射到TI1上.IC2FP2映射到TI2上
          TIM_ICPolarity_Rising, //极性:TI1正向,上升沿有效
          TIM_ICPolarity_Rising  //极性:TI2正向,上升沿有效
      );

  TIM_SetCounter(TIM5, 0); //计数器新值0
  TIM_Cmd(TIM5, ENABLE);   //定时器5使能
}

/**
  * @brief  初始化定时器8编码器模式
  * @param  无
  * @retval 无
  */
void TIM8_CODER_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //定义结构体变量
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);  //使能定时器8时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PC口时钟

  GPIO_StructInit(&GPIO_InitStructure);                  //前A相  后B相
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //PC6,PC7端口设置:TIM8_CH1/CH2-PC6/PC7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
  GPIO_Init(GPIOC, &GPIO_InitStructure);                 //根据上面的参数初始化IO口

  TIM_DeInit(TIM8);                               //将外设TIM8的寄存器重设为缺省值
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); //把TIM_TimeBaseInitStruct中的每一个参数按缺省值填入

  TIM_TimeBaseStructure.TIM_Period = 0XFFFF;                  //自动重装载值65536
  TIM_TimeBaseStructure.TIM_Prescaler = 0;                    //预分频
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;                //设置分频因子
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;            //重复计数设置
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
  TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);             //根据上面的参数初始化TIME8

  TIM_EncoderInterfaceConfig //设置编码器模式
      (
          TIM8,                  //定时器8的编码器
          TIM_EncoderMode_TI12,  //输入模式3：IC1FP1映射到TI1上.IC2FP2映射到TI2上
          TIM_ICPolarity_Rising, //极性:TI1正向,上升沿有效
          TIM_ICPolarity_Rising  //极性:TI2正向,上升沿有效
      );

  TIM_SetCounter(TIM8, 0); //计数器新值0
  TIM_Cmd(TIM8, ENABLE);   //定时器8使能
}

/**
  * @brief  读取定时器1的编码器值
  * @param  无
  * @retval Coder_Value :  获取到的值
  */
short TIM1_Getcoder(void)
{
  short Coder_Value;

  Coder_Value = TIM_GetCounter(TIM1); //获取编码器值
  TIM_SetCounter(TIM1, 0);            //计数器清零

  return Coder_Value;
}

/**
  * @brief  读取定时器2的编码器值
  * @param  无
  * @retval Coder_Value :  获取到的值
  */
short TIM2_Getcoder(void)
{
  short Coder_Value;

  Coder_Value = TIM_GetCounter(TIM2); //获取编码器值
  TIM_SetCounter(TIM2, 0);            //计数器清零

  return Coder_Value;
}

/**
  * @brief  读取定时器3的编码器值
  * @param  无
  * @retval Coder_Value :  获取到的值
  */
short TIM3_Getcoder(void)
{
  short Coder_Value;

  Coder_Value = TIM_GetCounter(TIM3); //获取编码器值
  TIM_SetCounter(TIM3, 0);            //计数器清零

  return Coder_Value;
}

/**
  * @brief  读取定时器4的编码器值
  * @param  无
  * @retval Coder_Value :  获取到的值
  */
short TIM4_Getcoder(void)
{
  short Coder_Value;

  Coder_Value = TIM_GetCounter(TIM4); //获取编码器值
  //TIM_SetCounter(TIM4, 0);		  	 	  //计数器清零

  return Coder_Value;
}

/**
  * @brief  读取定时器5的编码器值
  * @param  无
  * @retval Coder_Value :  获取到的值
  */
short TIM5_Getcoder(void)
{
  short Coder_Value;

  Coder_Value = TIM_GetCounter(TIM5); //获取编码器值
  TIM_SetCounter(TIM5, 0);            //计数器清零

  return Coder_Value;
}

/**
  * @brief  读取定时器8的编码器值
  * @param  无
  * @retval Coder_Value :  获取到的值
  */
short TIM8_Getcoder(void)
{
  short Coder_Value;

  Coder_Value = TIM_GetCounter(TIM8); //获取编码器值
  TIM_SetCounter(TIM8, 0);            //计数器清零

  return Coder_Value;
}

/*---------------------------------------------- End ------------------------------------------------*/
#endif