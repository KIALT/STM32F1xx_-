/**
  ***************************************************************************************************
  * @file     spi.c
  * @author   1008 Laboratory
  * @version  V3.0.0
  * @date     2017.6.29
  * @brief    spi通讯；硬件 
  ***************************************************************************************************
  * @attention
  *               硬件SPI1,SPI2,SPI3初始化
  * 
  ***************************************************************************************************
  */

#include "stm32f10x.h"
#include "spi.h"
/*Includes ----------------------------------------------------------------------------------------*/
#ifdef __ENABLE_SPI_

/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/

/*Functions ---------------------------------------------------------------------------------------*/

/**
  * @brief  SPI1初始化
  * @param  无
  * @retval 无
  */
void SPI1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;                                        //定义结构体变量
  SPI_InitTypeDef SPI_InitStructure;                                          //定义结构体变量
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE); //时钟使能

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; //PA5:SCK; PA6:MISO; PA7:MOSI;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                     //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                   //速率50MHZ
  GPIO_Init(GPIOA, &GPIO_InitStructure);                              //根据上面的参数初始化GPIO

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //设置SPI工作模式:设置为主SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //设置SPI的数据大小:SPI发送接收8位帧结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                         //选择了串行时钟的稳态:时钟悬空高
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        //数据捕获于第二个时钟沿
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //定义波特率预分频的值:波特率预分频值为64
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
  SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRC值计算的多项式
  SPI_Init(SPI1, &SPI_InitStructure);                                 //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

  SPI_Cmd(SPI1, ENABLE); //使能SPI外设
}

/**
  * @brief  SPI2初始化
  * @param  无
  * @retval 无
  */
void SPI2_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
  SPI_InitTypeDef SPI_InitStructure;   //定义结构体变量

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);  //SPI2时钟使能
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //GPIOB时钟使能

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; //PB13:SCK; PB14:MISO; PB15:MOSI;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                        //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                      //速率50MHZ
  GPIO_Init(GPIOB, &GPIO_InitStructure);                                 //根据上面的参数初始化GPIO

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //设置SPI工作模式:设置为主SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //设置SPI的数据大小:SPI发送接收8位帧结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                         //选择了串行时钟的稳态:时钟悬空高
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        //数据捕获于第二个时钟沿
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //定义波特率预分频的值:波特率预分频值为64
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
  SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRC值计算的多项式
  SPI_Init(SPI2, &SPI_InitStructure);                                 //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

  SPI_Cmd(SPI2, ENABLE); //使能SPI2外设
}
/**
  * @brief  SPI3初始化
  * @param  无
  * @retval 无
  */
void SPI3_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量
  SPI_InitTypeDef SPI_InitStructure;   //定义结构体变量

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //开启复用时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);  //SPI2时钟使能
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //GPIOB时钟使能

  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //关闭JTAG , 开启SWD

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5; //PA5:SCK; PA6:MISO; PA7:MOSI;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                     //复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                   //速率50MHZ
  GPIO_Init(GPIOB, &GPIO_InitStructure);                              //根据上面的参数初始化GPIO

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //设置SPI工作模式:设置为主SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   //设置SPI的数据大小:SPI发送接收8位帧结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;                         //选择了串行时钟的稳态:时钟悬空高
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;                        //数据捕获于第二个时钟沿
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //定义波特率预分频的值:波特率预分频值为64
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                  //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
  SPI_InitStructure.SPI_CRCPolynomial = 7;                            //CRC值计算的多项式
  SPI_Init(SPI3, &SPI_InitStructure);                                 //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器

  SPI_Cmd(SPI3, ENABLE); //使能SPI外设
}

/**
  * @brief  SPI1 速度设置函数
  * @param  SpeedSet ；
  * @retval 无
  */
void SPI1_SetSpeed(u8 SpeedSet)
{
  SPI1->CR1 &= 0XFFC7;
  SPI1->CR1 |= SpeedSet;
  SPI_Cmd(SPI1, ENABLE);
}

/**
  * @brief  SPI2 速度设置函数
  * @param  SpeedSet ；
  * @retval 无
  */
void SPI2_SetSpeed(u8 SpeedSet)
{
  SPI2->CR1 &= 0XFFC7;
  SPI2->CR1 |= SpeedSet;
  SPI_Cmd(SPI2, ENABLE);
}

/**
  * @brief  SPI3 速度设置函数
  * @param  SpeedSet ；
  * @retval 无
  */
void SPI3_SetSpeed(u8 SpeedSet)
{
  SPI3->CR1 &= 0XFFC7;
  SPI3->CR1 |= SpeedSet;
  SPI_Cmd(SPI3, ENABLE);
}

/**
  * @brief  SPI1 读写一个字节
  * @param  TxData ；要写入的数据
  * @retval 读取到的数据
  */
u8 SPI1_ReadWriteByte(u8 TxData)
{
  u8 retry = 0;
  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
  {
    retry++;
    if (retry > 200)
      return 0;
  }
  SPI_I2S_SendData(SPI1, TxData); //通过外设SPI1发送一个数据
  retry = 0;

  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
  {
    retry++;
    if (retry > 200)
      return 0;
  }
  return SPI_I2S_ReceiveData(SPI1); //返回通过SPI1最近接收的数据
}

/**
  * @brief  SPI2 读写一个字节
  * @param  TxData ；要写入的数据
  * @retval 读取到的数据
  */
u8 SPI2_ReadWriteByte(u8 TxData)
{
  u8 retry = 0;
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
  {
    retry++;
    if (retry > 200)
      return 0;
  }
  SPI_I2S_SendData(SPI2, TxData); //通过外设SPI1发送一个数据
  retry = 0;

  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
  {
    retry++;
    if (retry > 200)
      return 0;
  }
  return SPI_I2S_ReceiveData(SPI2); //返回通过SPI1最近接收的数据
}

/**
  * @brief  SPI3 读写一个字节
  * @param  TxData ；要写入的数据
  * @retval 读取到的数据
  */
u8 SPI3_ReadWriteByte(u8 TxData)
{
  u8 retry = 0;
  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
  {
    retry++;
    if (retry > 200)
      return 0;
  }
  SPI_I2S_SendData(SPI3, TxData); //通过外设SPI1发送一个数据
  retry = 0;

  while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
  {
    retry++;
    if (retry > 200)
      return 0;
  }
  return SPI_I2S_ReceiveData(SPI3); //返回通过SPI1最近接收的数据
}

/*---------------------------------------------- End ------------------------------------------------*/
#endif