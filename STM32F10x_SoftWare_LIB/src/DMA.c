/**
  **************************************************************************************************
  * @file     dma.c
  * @author   1008 Laboratory
  * @version  V3.0.0
  * @date     2017.7.2
  * @brief    DMA通道各外设初始化
  **************************************************************************************************
  * @attention
  *              1.	ADC1对应DMA1的通道1
  *      		 2.	SPI1_RX对应DMA1的通道2
  *				 3.	其它后续添加
  **************************************************************************************************
  */

/*Includes ----------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "dma.h"
#ifdef __ENABLE_DMA_


/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/

/*Functions ---------------------------------------------------------------------------------------*/

/**
  * @brief  初始化DMA1的ADC1通道
  * @param  Adc_DR_Addr :  DMA外设寄存器地址
  *			Ad_Mybuf	:  DMA内存基地址
  *			Buf_Size	:  DMA通道缓存大小
  * @retval 无
  */
void DMA1_ADC1_Init(u32 Adc_DR_Addr, u32 Ad_Mybuf, u16 Buf_Size)
{
  DMA_InitTypeDef DMA_InitStructure; //定义DMA结构体变量

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                          //使能DMA传输
  DMA_DeInit(DMA1_Channel1);                                                  //将DMA的通道11寄存器重设为缺省值
  DMA_InitStructure.DMA_PeripheralBaseAddr = Adc_DR_Addr;                     //DMA外设基地址 (STM32外设数据寄存器地址)
  DMA_InitStructure.DMA_MemoryBaseAddr = Ad_Mybuf;                            //DMA内存基地址 (存放读取到数据的一段空间的地址 通常是一个数组)
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                          //数据传输方向  读取ADC寄存器的值存到数组
  DMA_InitStructure.DMA_BufferSize = Buf_Size;                                //DMA通道的DMA缓存的大小
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;            //外设地址寄存器不变
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                     //内存地址寄存器递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //数据宽度为16位  半字
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;         //数据宽度为16位  半字
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                             //循环缓存模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                       //DMA通道x中优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                                //DMA通道x没有设置为内存到内存传输
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);                                //根据DMA_InitStruct中指定的参数初始化DMA的通道
                                                                              //DMA_Cmd(DMA1_Channel1, ENABLE);  											//使能DMA
}

/**
  * @brief  初始化DMA1的SPI1RX通道: 没验证        
  * @param  Adc_DR_Addr :  DMA外设寄存器地址
  *			Ad_Mybuf	:  DMA内存基地址
  *			Buf_Size	:  DMA通道缓存大小
  * @retval 无
  */
void DMA1_SPI1RX_Init(u32 Adc_DR_Addr, u32 Ad_Mybuf, u16 Buf_Size)
{
  DMA_InitTypeDef DMA_InitStructure; //定义DMA结构体变量

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);                      //使能DMA传输
  DMA_DeInit(DMA1_Channel2);                                              //将DMA的通道1寄存器重设为缺省值
  DMA_InitStructure.DMA_PeripheralBaseAddr = Adc_DR_Addr;                 //DMA外设基地址 (STM32外设数据寄存器地址)
  DMA_InitStructure.DMA_MemoryBaseAddr = Ad_Mybuf;                        //DMA内存基地址 (存放读取到数据的一段空间的地址 通常是一个数组)
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                      //数据传输方向  读取ADC寄存器的值存到数组
  DMA_InitStructure.DMA_BufferSize = Buf_Size;                            //DMA通道的DMA缓存的大小
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //外设地址寄存器不变
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 //内存地址寄存器递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; //数据宽度为8位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         //数据宽度为8位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;                         //循环缓存模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   //DMA通道x中优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            //DMA通道x没有设置为内存到内存传输
  DMA_Init(DMA1_Channel2, &DMA_InitStructure);                            //根据DMA_InitStruct中指定的参数初始化DMA的通道
                                                                          //DMA_Cmd(DMA1_Channel1, ENABLE);  											//使能DMA
}

/*---------------------------------------------- End ------------------------------------------------*/
#endif