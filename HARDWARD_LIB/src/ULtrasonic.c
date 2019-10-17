/*******************************************************************************
  @File   : ULtrasonic.c
  @Author : 罗涛
  @Date   : 2019年6月5日 20.12
  @Brief  : 超声波模块驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
  4.使用操作见Example.txt
*******************************************************************************/
#include "ULtrasonic.h"
#include "misc.h"
#include "stm32f10x_exti.h"

/* 中断实现超声波测距功能，根据实际情况来确定使用哪个驱动超声波*/
// void EXTI2_IRQHandler(void)
// {
//    TIM7->CNT =  0;             /*开启计数*/
//    TIM7->CR1 |= (1<<0);       /*开启TIM7 */
//    while(GPIO_ReadInputDataBit(ULTR_RX_PORT,ULTR_RX_PIN));
   
//    Tim_Cnt = TIM7->CNT;
//    distance = (Tim_Cnt *344 * 0.0001f) / (2.0f); 
// 	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE2上的中断标志位  
// } 
 
/**
  * @brief  初始化外部中断
  * @param  None
  * @retval None
  */
void EXTI2_Init(void)
{
  EXTI_InitTypeDef EXIT2_InitStruct;
  NVIC_InitTypeDef NVIC_InitStruct;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); /*要使用外部中断必须开启AFIO时钟 */

  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2); /* 配置PE2为外部中断2*/

  EXIT2_InitStruct.EXTI_Line = EXTI_Line2;             /* 配置外部中断2 */
  EXIT2_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;    /* 中断模式 */
  EXIT2_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising; /* 上升沿触发*/
  EXIT2_InitStruct.EXTI_LineCmd = ENABLE;              /* 使能外部中断二 */
  EXTI_Init(&EXIT2_InitStruct);

  NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;          /* 配置外部中断优先级*/
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2; /* 抢占优先级2*/
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;        /* 子优先级*/
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;           /* 使能外部中断2的优先级*/
  NVIC_Init(&NVIC_InitStruct);
}

/**
  * @brief  发送超声波模块的驱动信号
  * @param  None
  * @retval None
  */
void ULtrasonic_star(void)
{
  GPIO_SetBits(ULTR_TX_PORT, ULTR_TX_PIN);   /* 先发送一个大于10us的脉冲*/
  delay_us(20);                              /*随后超声波自动发送8个40KHZ的脉冲*/
  GPIO_ResetBits(ULTR_TX_PORT, ULTR_TX_PIN); /*之后RX端就会接受一个脉冲，脉冲的高电平时间就是超声波发送和返回的时间总和*/
}
void ULtrasonic_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_APB2PeriphClockCmd(ULTR_RX_RCC, ENABLE); /*初始化时钟 */
  RCC_APB2PeriphClockCmd(ULTR_TX_RCC, ENABLE);

  GPIO_InitStruct.GPIO_Pin = ULTR_RX_PIN; /* 配置RX引脚*/
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ULTR_RX_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = ULTR_TX_PIN; /* 配置TX引脚 */
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(ULTR_TX_PORT, &GPIO_InitStruct);

  RCC->APB1ENR |= (1 << 5); /*开启定器7的时钟*/
  TIM7->PSC = 71;           /*100KHZ计数频率,计一个数为10us*/
  TIM7->ARR = 999;          /*1ms计数上限,最大距离3.4米，根据实际情况修改ARR值*/  
  TIM7->CR1 &= ~(1 << 0); /* 关闭TIM7*/
}
/**
  * @brief 超声波测距函数
  * @param  None
  * @retval 返回测量到的距离(浮点型)单位为厘米
  */
float get_ULtrasonicVal(void)
{
  uint16_t i = 0;
  uint16_t Tim_Cnt = 0; /* Tim7计数时间*/
  float distance = 0;   /*超声波探测到的距离*/

  GPIO_ResetBits(ULTR_RX_PORT, ULTR_RX_PIN); /* 等待接收脉冲*/

  GPIO_SetBits(ULTR_TX_PORT, ULTR_TX_PIN); /*发送一个大于10us的脉冲*/
  delay_us(20);
  GPIO_ResetBits(ULTR_TX_PORT, ULTR_TX_PIN);

  while (!GPIO_ReadInputDataBit(ULTR_RX_PORT, ULTR_RX_PIN)) /* 接收到高电平*/
  {
    i++;
    if (i > 20000)   /*防止由于引脚接错，程序卡死*/
    {
      break;
      return 0;      /*等待带超时,退出等待*/ 
    }
  }
  TIM7->CNT = 0;         /* 开启计数*/
  TIM7->CR1 |= (1 << 0); /* 开启TIM7*/

  while (GPIO_ReadInputDataBit(ULTR_RX_PORT, ULTR_RX_PIN)) /*脉冲结束*/
  {
    i++;
    if (i > 2000)  /*防止由于引脚接错，程序卡死*/
    {
      break;
      return 0;    /*等待带超时,退出等待*/ 
    }
  }

  Tim_Cnt = TIM7->CNT;                                   /*读取时间*/
  distance = (Tim_Cnt * SOUND_SPEED * 0.0001f) / (2.0f); /* 时间转换成距离(单位为厘米)*/
  return distance;                                       /* 返回距离 */
}