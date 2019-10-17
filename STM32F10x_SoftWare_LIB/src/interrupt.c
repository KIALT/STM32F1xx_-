/**
  **************************************************************************************************
  * @file     interrupt.c
  * @author   1008 Laboratory
  * @version  V3.0.0
  * @date     2017.7.3
  * @brief    中断处理
  **************************************************************************************************
  * @attention
  *           1.  所有外设中断函数都在本文件执行
  *			  2.  没有的需自行添加,在启动文件(.s)中可找到中断函数名名称
  *      
  **************************************************************************************************
  */

/*Includes ----------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#ifdef __ENABLE_INTERRUPT_
//#include "interrupt.h"
//#include "user_config.h"

/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/

extern float angle, gyro_x;

/*Functions ---------------------------------------------------------------------------------------*/

/****************************************** 定时器中断 *********************************************/

/**
  * @brief  TIM1更新中断服务函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void TIM1_UP_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {

    TIM_ClearITPendingBit(TIM1, TIM_IT_Update); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/**
  * @brief  TIM1捕获中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void TIM1_CC_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM1, TIM_IT_CC1) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {

    TIM_ClearITPendingBit(TIM1, TIM_IT_CC1); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/**
  * @brief  TIM2中断服务函数 ,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {

    TIM_ClearITPendingBit(TIM2, TIM_IT_Update); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/**
  * @brief  TIM3中断服务函数,中断源如不符合需自行修改 
  * @param  无
  * @retval 无
  */
void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {

    TIM_ClearITPendingBit(TIM3, TIM_IT_Update); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/**
  * @brief  TIM4中断服务函数,中断源如不符合需自行修改 
  * @param  无
  * @retval 无
  */
void TIM4_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {

    TIM_ClearITPendingBit(TIM4, TIM_IT_Update); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/**
  * @brief  TIM5中断服务函数,中断源如不符合需自行修改 
  * @param  无
  * @retval 无
  */
void TIM5_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {

    TIM_ClearITPendingBit(TIM5, TIM_IT_Update); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/**
  * @brief  TIM6中断服务函数 ,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void TIM6_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {
    //PID_Adjust();

    TIM_ClearITPendingBit(TIM6, TIM_IT_Update); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/**
  * @brief  TIM7中断服务函数 ,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void TIM7_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {

    TIM_ClearITPendingBit(TIM7, TIM_IT_Update); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/**
  * @brief  TIM8更新中断服务函数 ,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void TIM8_UP_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM8, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {

    TIM_ClearITPendingBit(TIM8, TIM_IT_Update); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/**
  * @brief  TIM8捕获中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void TIM8_CC_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM8, TIM_IT_CC1) != RESET) //检查指定的TIM中断发生与否:TIM 中断源
  {

    TIM_ClearITPendingBit(TIM8, TIM_IT_CC1); //清除TIMx的中断待处理位:TIM 中断源
  }
}

/******************************************** 外部中断 **********************************************/

/**
  * @brief  外部中断0,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void EXTI0_IRQHandler(void)
{
}

/**
  * @brief  外部中断1,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void EXTI1_IRQHandler(void)
{
}

/**
  * @brief  外部中断2,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void EXTI2_IRQHandler(void)
{
}

/**
  * @brief  外部中断3,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void EXTI3_IRQHandler(void)
{
}

/**
  * @brief  外部中断4,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void EXTI4_IRQHandler(void)
{
}

/**
  * @brief  外部中断5~9,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void EXTI9_5_IRQHandler(void)
{
}

/**
  * @brief  外部中断10~15,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void EXTI15_10_IRQHandler(void)
{
}

/************************************************ 串口中断 ***********************************************/

u8 Res;
u8 bz = 0, num = 0, xsbz = 0, fhbz = 0;
volatile u8 ckt_PID[7] = {0, 0, 0, 0, 0, 0, 0};
float xiaosd, sjcf;
u16 weiquan;

/**
  * @brief  串口1中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void USART1_IRQHandler(void)
{
//  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//  {
//    Res = USART_ReceiveData(USART1); //(USART1->DR);	//读取接收到的数据

//    if (Res == 0x4b)
//    {
//      bz = 1;
//      num = 0;
//    }
//    if (Res == 0x3b)
//    {
//      bz = 0;
//      num = 0;
//    }
//    if (bz == 1)
//    {
//      num++;
//      if (num == 2)
//      {
//        ckt_PID[0] = Res;
//      }
//      if (num == 3)
//      {
//        ckt_PID[1] = Res;
//      }
//      if (num == 4)
//      {
//        ckt_PID[2] = Res;
//      }
//      if (num == 5)
//      {
//        ckt_PID[3] = Res;
//      }
//      if (num == 6)
//      {
//        ckt_PID[4] = Res;
//      }
//      if (num == 7)
//      {
//        ckt_PID[5] = Res;
//      }
//      if (num == 8)
//      {
//        ckt_PID[6] = Res;
//        for (num = 1; num < 7; num++)
//        {
//          ckt_PID[num] = ckt_PID[num] - 0x30;
//        }

//        for (num = 2; num < 6; num++)
//        {
//          if (ckt_PID[num] == 254)
//          {
//            if (num == 2)
//            {
//              xsbz = 1;
//              xiaosd = 0.0001;
//              break;
//            }
//            if (num == 3)
//            {
//              xsbz = 1;
//              xiaosd = 0.001;
//              break;
//            }
//            if (num == 4)
//            {
//              xsbz = 1;
//              xiaosd = 0.01;
//              break;
//            }
//            if (num == 5)
//            {
//              xsbz = 1;
//              xiaosd = 0.1;
//              break;
//            }
//          }
//          xsbz = 0;
//        }

//        if (ckt_PID[1] == 253)
//        {
//          if (xsbz == 0)
//            sjcf = (ckt_PID[2] * 10000 + ckt_PID[3] * 1000 + ckt_PID[4] * 100 + ckt_PID[5] * 10 + ckt_PID[6]) * (-1);
//          else
//          {
//            if (num == 2)
//              sjcf = (ckt_PID[3] * 1000 + ckt_PID[4] * 100 + ckt_PID[5] * 10 + ckt_PID[6]) * xiaosd * (-1);
//            if (num == 3)
//              sjcf = (ckt_PID[2] * 1000 + ckt_PID[4] * 100 + ckt_PID[5] * 10 + ckt_PID[6]) * xiaosd * (-1);
//            if (num == 4)
//              sjcf = (ckt_PID[2] * 1000 + ckt_PID[3] * 100 + ckt_PID[5] * 10 + ckt_PID[6]) * xiaosd * (-1);
//            if (num == 5)
//              sjcf = (ckt_PID[2] * 1000 + ckt_PID[3] * 100 + ckt_PID[4] * 10 + ckt_PID[6]) * xiaosd * (-1);
//          }
//        }
//        else
//        {
//          if (xsbz == 0)
//            sjcf = ckt_PID[1] * 100000 + ckt_PID[2] * 10000 + ckt_PID[3] * 1000 + ckt_PID[4] * 100 + ckt_PID[5] * 10 + ckt_PID[6];
//          else
//          {
//            if (num == 2)
//              sjcf = (ckt_PID[1] * 10000 + ckt_PID[3] * 1000 + ckt_PID[4] * 100 + ckt_PID[5] * 10 + ckt_PID[6]) * xiaosd;
//            if (num == 3)
//              sjcf = (ckt_PID[1] * 10000 + ckt_PID[2] * 1000 + ckt_PID[4] * 100 + ckt_PID[5] * 10 + ckt_PID[6]) * xiaosd;
//            if (num == 4)
//              sjcf = (ckt_PID[1] * 10000 + ckt_PID[2] * 1000 + ckt_PID[3] * 100 + ckt_PID[5] * 10 + ckt_PID[6]) * xiaosd;
//            if (num == 5)
//              sjcf = (ckt_PID[1] * 10000 + ckt_PID[2] * 1000 + ckt_PID[3] * 100 + ckt_PID[4] * 10 + ckt_PID[6]) * xiaosd;
//          }
//        }

//        if (ckt_PID[0] == 'p')
//        {
//          Kp = sjcf;
//        }
//        if (ckt_PID[0] == 'd')
//        {
//          Kd = sjcf;
//        }
//        if (ckt_PID[0] == 's')
//        {
//          Ks = sjcf;
//        }
//        if (ckt_PID[0] == 'i')
//        {
//          Ki = sjcf;
//        }
//        num = 0;
//      }
//    }
//  }
}

/**
  * @brief  串口2中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
//void USART2_IRQHandler(void)
//{
//}

/**
  * @brief  串口3中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void USART3_IRQHandler(void)
{
}

/****************************************** SPI中断 **********************************************/

/**
  * @brief  SPI1中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void SPI1_IRQHandler(void)
{
}

/**
  * @brief  SPI1中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void SPI2_IRQHandler(void)
{
}

/**
  * @brief  SPI3中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void SPI3_IRQHandler(void)
{
}

/******************************************** DMA中断 ********************************************/

/**
  * @brief  DMA1通道1中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA1_Channel1_IRQHandler(void)
{
}

/**
  * @brief  DMA1通道2中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA1_Channel2_IRQHandler(void)
{
}

/**
  * @brief  DMA1通道3中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA1_Channel3_IRQHandler(void)
{
}

/**
  * @brief  DMA1通道4中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA1_Channel4_IRQHandler(void)
{
}

/**
  * @brief  DMA1通道5中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA1_Channel5_IRQHandler(void)
{
}

/**
  * @brief  DMA1通道6中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA1_Channel6_IRQHandler(void)
{
}

/**
  * @brief  DMA1通道7中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA1_Channel7_IRQHandler(void)
{
}

/**
  * @brief  DMA2通道1中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA2_Channel1_IRQHandler(void)
{
}

/**
  * @brief  DMA2通道2中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA2_Channel2_IRQHandler(void)
{
}

/**
  * @brief  DMA2通道3中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA2_Channel3_IRQHandler(void)
{
}

/**
  * @brief  DMA2通道4,5中断函数,中断源如不符合需自行修改
  * @param  无
  * @retval 无
  */
void DMA2_Channel4_5_IRQHandler(void)
{
}

/*---------------------------------------------- End ------------------------------------------------*/
#endif