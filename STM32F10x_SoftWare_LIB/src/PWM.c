/**
  **************************************************************************************************
  * @file     pwm.c
  * @author   1008 Laboratory
  * @version  V3.0.0
  * @date     2017.6.29
  * @brief    各定时器PWM模式初始化 
  **************************************************************************************************
  * @attention
  *              1. 定时器PWM模式初始化,定时器6和定时器7没有PWM输出功能
  *              2. 可根据实际情况对初始化函数进行裁剪和修改
  *				 3. 用高级定时器1 PWM模式时不能用串口1
  **************************************************************************************************
  */
 #include "stm32f10x.h"
#include "pwm.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#ifdef __ENABLE_PWM_
/*Includes ----------------------------------------------------------------------------------------*/
/*Defines -----------------------------------------------------------------------------------------*/
/*Variables ---------------------------------------------------------------------------------------*/
/*Functions ---------------------------------------------------------------------------------------*/

/**
  * @brief  TIM1_PWM初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM1_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);	//使能TIME1定时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA口外设时钟使能

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				 //速率50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |	//TIM1:PA8_CH1,  PA9_CH2
																GPIO_Pin_10 | GPIO_Pin_11; //TIM1:PA10_CH3, PA11_CH4
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_DeInit(TIM1); //复位定时器

	TIM_TimeBaseStructure.TIM_Period    = arr;											//初值重装
	TIM_TimeBaseStructure.TIM_Prescaler = psc;									//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;								//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;						//重复计数设置
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);							//根据上面的参数初始化定时器

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;							//模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;														//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//高电平有效

	TIM_OC1Init(TIM1, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC2Init(TIM1, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC3Init(TIM1, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC4Init(TIM1, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH1预装载使能
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH2预装载使能
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH3预装载使能
	TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); //CH4预装载使能

	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器
	TIM_CtrlPWMOutputs(TIM1, ENABLE);		//MOE 主输出使能
	TIM_Cmd(TIM1, ENABLE);							//使能TIM1
}

/**
  * @brief  TIM2_PWM初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM2_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	// 使能TIME2定时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA口外设时钟使能

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				//速率50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | //TIM2:PA0_CH1, PA1_CH2
																GPIO_Pin_2 | GPIO_Pin_3;	//TIM2:PA2_CH3, PA3_CH4
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_DeInit(TIM2); //复位定时器

	TIM_TimeBaseStructure.TIM_Period = arr;											//初值重装
	TIM_TimeBaseStructure.TIM_Prescaler = psc;									//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;								//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);							//根据上面的参数初始化定时器

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;							//模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;														//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//高电平有效

	TIM_OC1Init(TIM2, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC2Init(TIM2, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC3Init(TIM2, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC4Init(TIM2, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable); //CH1预装载使能
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); //CH2预装载使能
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable); //CH3预装载使能
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable); //CH4预装载使能

	TIM_ARRPreloadConfig(TIM2, ENABLE); //使能TIMx在ARR上的预装载寄存器
	TIM_CtrlPWMOutputs(TIM2, ENABLE);		//MOE 主输出使能
	TIM_Cmd(TIM2, ENABLE);							//使能TIM2
}
/**
  * @brief  TIM3_PWM初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM3_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能TIME3定时器时钟
																												//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);  //使能PA口外设时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB口外设时钟使能

	/*GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_AF_PP;         		//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				//速率50M
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_6 | GPIO_Pin_7 ;		//TIM3:PA6_CH1, PA7_CH2    	
	GPIO_Init(GPIOA, &GPIO_InitStructure);*/

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;				 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //速率50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //TIM3:PB0_CH3, PB1_CH4
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_DeInit(TIM3); //复位定时器

	TIM_TimeBaseStructure.TIM_Period = arr;											//初值重装
	TIM_TimeBaseStructure.TIM_Prescaler = psc;									//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;								//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);							//根据上面的参数初始化定时器

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;							//模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;														//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//高电平有效

	//TIM_OC1Init(TIM3, &TIM_OCInitStructure);  						//根据指定的参数初始化外设TIMx
	//TIM_OC2Init(TIM3, &TIM_OCInitStructure);  						//根据指定的参数初始化外设TIMx
	TIM_OC3Init(TIM3, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC4Init(TIM3, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx

	//TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  				//CH1预装载使能
	//TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  				//CH2预装载使能
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable); //CH3预装载使能
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable); //CH4预装载使能

	TIM_ARRPreloadConfig(TIM3, ENABLE); //使能TIMx在ARR上的预装载寄存器
	TIM_CtrlPWMOutputs(TIM3, ENABLE);		//MOE 主输出使能
	TIM_Cmd(TIM3, ENABLE);							//使能TIM3
}
/**
  * @brief  TIM4_PWM初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM4_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能TIME4定时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PB口外设时钟使能

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				//速率50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | //TIM4:PB6_CH1, PB7_CH2
																GPIO_Pin_8 | GPIO_Pin_9;	//TIM4:PB8_CH3, PB9_CH4
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_DeInit(TIM4); //复位定时器

	TIM_TimeBaseStructure.TIM_Period = arr;											//初值重装
	TIM_TimeBaseStructure.TIM_Prescaler = psc;									//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;								//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);							//根据上面的参数初始化定时器

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;							//模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;														//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//高电平有效

	TIM_OC1Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC2Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC4Init(TIM4, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH1预装载使能
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH2预装载使能
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH3预装载使能
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable); //CH4预装载使能

	TIM_ARRPreloadConfig(TIM4, ENABLE); //使能TIMx在ARR上的预装载寄存器
	TIM_CtrlPWMOutputs(TIM4, ENABLE);		//MOE 主输出使能
	TIM_Cmd(TIM4, ENABLE);							//使能TIM4
}
/**
  * @brief  TIM5_PWM初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM5_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能TIME5定时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA口外设时钟使能

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				//速率50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | //TIM5:PA0_CH1, PA1_CH2
																GPIO_Pin_2 | GPIO_Pin_3;	//TIM5:PA2_CH3, PA3_CH4
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_DeInit(TIM5); //复位定时器

	TIM_TimeBaseStructure.TIM_Period = arr;											//初值重装
	TIM_TimeBaseStructure.TIM_Prescaler = psc;									//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;								//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);							//根据上面的参数初始化定时器

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;							//模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;														//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//高电平有效

	TIM_OC1Init(TIM5, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC2Init(TIM5, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC3Init(TIM5, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC4Init(TIM5, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx

	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH1预装载使能
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH2预装载使能
	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH3预装载使能
	TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable); //CH4预装载使能

	TIM_ARRPreloadConfig(TIM5, ENABLE); //使能TIMx在ARR上的预装载寄存器
	TIM_CtrlPWMOutputs(TIM5, ENABLE);		//MOE 主输出使能
	TIM_Cmd(TIM5, ENABLE);							//使能TIM5
}

/**
  * @brief  TIM8_PWM初始化
  * @param  arr ；初值
  *         psc ；分频系数
  * @retval 无
  */
void TIM8_PWM_Init(u16 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);	//使能TIME8定时器时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能PC口外设时钟使能

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;					//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				//速率50M
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | //TIM8:PC6_CH1, PC7_CH2
																GPIO_Pin_8 | GPIO_Pin_9;	//TIM8:PC8_CH3, PC9_CH4
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	TIM_DeInit(TIM8); //复位定时器

	TIM_TimeBaseStructure.TIM_Period = arr;											//初值重装
	TIM_TimeBaseStructure.TIM_Prescaler = psc;									//预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;								//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;						//重复计数设置
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);							//根据上面的参数初始化定时器

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;							//模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;														//设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			//高电平有效

	TIM_OC1Init(TIM8, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC2Init(TIM8, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC3Init(TIM8, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx
	TIM_OC4Init(TIM8, &TIM_OCInitStructure); //根据指定的参数初始化外设TIMx

	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); //CH1预装载使能
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable); //CH2预装载使能
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable); //CH3预装载使能
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable); //CH4预装载使能

	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRConfig(TIM8, &TIM_BDTRInitStructure);

	TIM_ARRPreloadConfig(TIM8, ENABLE); //使能TIMx在ARR上的预装载寄存器
	TIM_CtrlPWMOutputs(TIM8, ENABLE);		//MOE 主输出使能
	TIM_Cmd(TIM8, ENABLE);							//使能TIM8
}

/**
  * @brief  定时器1 PWM更新函数
  * @param  PWM1 ~ PWM4； PWM值
  * @retval 无
  */
void TIM1_PWM_update(s16 PWM1, s16 PWM2, s16 PWM3, s16 PWM4)
{
	if (PWM1 > TIM1_PWM_MAX)
		PWM1 = TIM1_PWM_MAX;
	if (PWM2 > TIM1_PWM_MAX)
		PWM2 = TIM1_PWM_MAX;
	if (PWM3 > TIM1_PWM_MAX)
		PWM3 = TIM1_PWM_MAX;
	if (PWM4 > TIM1_PWM_MAX)
		PWM4 = TIM1_PWM_MAX;

	if (PWM1 < -TIM1_PWM_MAX)
		PWM1 = -TIM1_PWM_MAX;
	if (PWM2 < -TIM1_PWM_MAX)
		PWM2 = -TIM1_PWM_MAX;
	if (PWM3 < -TIM1_PWM_MAX)
		PWM3 = -TIM1_PWM_MAX;
	if (PWM4 < -TIM1_PWM_MAX)
		PWM4 = -TIM1_PWM_MAX;

	if (PWM1 < 0)
		PWM1 = -PWM1;
	if (PWM2 < 0)
		PWM2 = -PWM2;
	if (PWM3 < 0)
		PWM3 = -PWM3;
	if (PWM4 < 0)
		PWM4 = -PWM4;

	TIM1_PWM_OC1 = PWM1; //通道 1 赋值
	TIM1_PWM_OC2 = PWM2; //通道 2 赋值
	TIM1_PWM_OC3 = PWM3; //通道 3 赋值
	TIM1_PWM_OC4 = PWM4; //通道 4 赋值
}

/**
  * @brief  定时器2 PWM更新函数
  * @param  PWM1 ~ PWM4； PWM值
  * @retval 无
  */
void TIM2_PWM_update(s16 PWM1, s16 PWM2, s16 PWM3, s16 PWM4)
{
	if (PWM1 > TIM2_PWM_MAX)
		PWM1 = TIM2_PWM_MAX;
	if (PWM2 > TIM2_PWM_MAX)
		PWM2 = TIM2_PWM_MAX;
	if (PWM3 > TIM2_PWM_MAX)
		PWM3 = TIM2_PWM_MAX;
	if (PWM4 > TIM2_PWM_MAX)
		PWM4 = TIM2_PWM_MAX;

	if (PWM1 < -TIM2_PWM_MAX)
		PWM1 = -TIM2_PWM_MAX;
	if (PWM2 < -TIM2_PWM_MAX)
		PWM2 = -TIM2_PWM_MAX;
	if (PWM3 < -TIM2_PWM_MAX)
		PWM3 = -TIM2_PWM_MAX;
	if (PWM4 < -TIM2_PWM_MAX)
		PWM4 = -TIM2_PWM_MAX;

	if (PWM1 < 0)
		PWM1 = -PWM1;
	if (PWM2 < 0)
		PWM2 = -PWM2;
	if (PWM3 < 0)
		PWM3 = -PWM3;
	if (PWM4 < 0)
		PWM4 = -PWM4;

	TIM2_PWM_OC1 = PWM1; //通道 1 赋值
	TIM2_PWM_OC2 = PWM2; //通道 2 赋值
	TIM2_PWM_OC3 = PWM3; //通道 3 赋值
	TIM2_PWM_OC4 = PWM4; //通道 4 赋值
}

/**
  * @brief  定时器3 PWM更新函数
  * @param  PWM1 ~ PWM4； PWM值
  * @retval 无
  */
void TIM3_PWM_update(s16 PWM1, s16 PWM2, s16 PWM3, s16 PWM4)
{
	if (PWM1 > TIM3_PWM_MAX)
		PWM1 = TIM3_PWM_MAX;
	if (PWM2 > TIM3_PWM_MAX)
		PWM2 = TIM3_PWM_MAX;
	if (PWM3 > TIM3_PWM_MAX)
		PWM3 = TIM3_PWM_MAX;
	if (PWM4 > TIM3_PWM_MAX)
		PWM4 = TIM3_PWM_MAX;

	if (PWM1 < -TIM3_PWM_MAX)
		PWM1 = -TIM3_PWM_MAX;
	if (PWM2 < -TIM3_PWM_MAX)
		PWM2 = -TIM3_PWM_MAX;
	if (PWM3 < -TIM3_PWM_MAX)
		PWM3 = -TIM3_PWM_MAX;
	if (PWM4 < -TIM3_PWM_MAX)
		PWM4 = -TIM3_PWM_MAX;

	if (PWM1 < 0)
		PWM1 = -PWM1;
	if (PWM2 < 0)
		PWM2 = -PWM2;
	if (PWM3 < 0)
		PWM3 = -PWM3;
	if (PWM4 < 0)
		PWM4 = -PWM4;

	TIM3_PWM_OC1 = PWM1; //通道 1 赋值
	TIM3_PWM_OC2 = PWM2; //通道 2 赋值
	TIM3_PWM_OC3 = PWM3; //通道 3 赋值
	TIM3_PWM_OC4 = PWM4; //通道 4 赋值
}

/**
  * @brief  定时器4 PWM更新函数
  * @param  PWM1 ~ PWM4； PWM值
  * @retval 无
  */
void TIM4_PWM_update(s16 PWM1, s16 PWM2, s16 PWM3, s16 PWM4)
{
	if (PWM1 > TIM4_PWM_MAX)
		PWM1 = TIM4_PWM_MAX;
	if (PWM2 > TIM4_PWM_MAX)
		PWM2 = TIM4_PWM_MAX;
	if (PWM3 > TIM4_PWM_MAX)
		PWM3 = TIM4_PWM_MAX;
	if (PWM4 > TIM4_PWM_MAX)
		PWM4 = TIM4_PWM_MAX;

	if (PWM1 < -TIM4_PWM_MAX)
		PWM1 = -TIM4_PWM_MAX;
	if (PWM2 < -TIM4_PWM_MAX)
		PWM2 = -TIM4_PWM_MAX;
	if (PWM3 < -TIM4_PWM_MAX)
		PWM3 = -TIM4_PWM_MAX;
	if (PWM4 < -TIM4_PWM_MAX)
		PWM4 = -TIM4_PWM_MAX;

	if (PWM1 < 0)
		PWM1 = -PWM1;
	if (PWM2 < 0)
		PWM2 = -PWM2;
	if (PWM3 < 0)
		PWM3 = -PWM3;
	if (PWM4 < 0)
		PWM4 = -PWM4;

	TIM4_PWM_OC1 = PWM1; //通道 1 赋值
	TIM4_PWM_OC2 = PWM2; //通道 2 赋值
	TIM4_PWM_OC3 = PWM3; //通道 3 赋值
	TIM4_PWM_OC4 = PWM4; //通道 4 赋值
}

/**
  * @brief  定时器5 PWM更新函数
  * @param  PWM1 ~ PWM4； PWM值
  * @retval 无
  */
void TIM5_PWM_update(s16 PWM1, s16 PWM2, s16 PWM3, s16 PWM4)
{
	if (PWM1 > TIM5_PWM_MAX)
		PWM1 = TIM5_PWM_MAX;
	if (PWM2 > TIM5_PWM_MAX)
		PWM2 = TIM5_PWM_MAX;
	if (PWM3 > TIM5_PWM_MAX)
		PWM3 = TIM5_PWM_MAX;
	if (PWM4 > TIM5_PWM_MAX)
		PWM4 = TIM5_PWM_MAX;

	if (PWM1 < -TIM5_PWM_MAX)
		PWM1 = -TIM5_PWM_MAX;
	if (PWM2 < -TIM5_PWM_MAX)
		PWM2 = -TIM5_PWM_MAX;
	if (PWM3 < -TIM5_PWM_MAX)
		PWM3 = -TIM5_PWM_MAX;
	if (PWM4 < -TIM5_PWM_MAX)
		PWM4 = -TIM5_PWM_MAX;

	if (PWM1 < 0)
		PWM1 = -PWM1;
	if (PWM2 < 0)
		PWM2 = -PWM2;
	if (PWM3 < 0)
		PWM3 = -PWM3;
	if (PWM4 < 0)
		PWM4 = -PWM4;

	TIM5_PWM_OC1 = PWM1; //通道 1 赋值
	TIM5_PWM_OC2 = PWM2; //通道 2 赋值
	TIM5_PWM_OC3 = PWM3; //通道 3 赋值
	TIM5_PWM_OC4 = PWM4; //通道 4 赋值
}

/**
  * @brief  定时器8 PWM更新函数
  * @param  PWM1 ~ PWM4； PWM值
  * @retval 无
  */
void TIM8_PWM_update(s16 PWM1, s16 PWM2, s16 PWM3, s16 PWM4)
{
	if (PWM1 > TIM8_PWM_MAX)
		PWM1 = TIM8_PWM_MAX;
	if (PWM2 > TIM8_PWM_MAX)
		PWM2 = TIM8_PWM_MAX;
	if (PWM3 > TIM8_PWM_MAX)
		PWM3 = TIM8_PWM_MAX;
	if (PWM4 > TIM8_PWM_MAX)
		PWM4 = TIM8_PWM_MAX;

	if (PWM1 < -TIM8_PWM_MAX)
		PWM1 = -TIM8_PWM_MAX;
	if (PWM2 < -TIM8_PWM_MAX)
		PWM2 = -TIM8_PWM_MAX;
	if (PWM3 < -TIM8_PWM_MAX)
		PWM3 = -TIM8_PWM_MAX;
	if (PWM4 < -TIM8_PWM_MAX)
		PWM4 = -TIM8_PWM_MAX;

	if (PWM1 < 0)
		PWM1 = -PWM1;
	if (PWM2 < 0)
		PWM2 = -PWM2;
	if (PWM3 < 0)
		PWM3 = -PWM3;
	if (PWM4 < 0)
		PWM4 = -PWM4;

	TIM8_PWM_OC1 = PWM1; //通道 1 赋值
	TIM8_PWM_OC2 = PWM2; //通道 2 赋值
	TIM8_PWM_OC3 = PWM3; //通道 3 赋值
	TIM8_PWM_OC4 = PWM4; //通道 4 赋值
}

/*---------------------------------------------- End ------------------------------------------------*/
#endif