/*******************************************************************************
  @File   : NRF2401.h
  @Author : 罗涛
  @Date   : 2019年6月8日 16.54
  @Brief  : NRF2401驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
  
       1.使用操作见Example.txt
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _NRF2401_H
#define _NRF2401_H
/* Public includes -----------------------------------------------------------*/
#include "stdint.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stdbool.h"
#include "stdio.h"
#include "stm32f10x_spi.h"
#include "spi.h"
/* pirvate include **********************************************************/
#include "delay.h"
/* Define ******************************************************************/
/***********************NRF SPI寄存器指令*********************************/
#define CMD_R_REG 0x00        // 读寄存器指令
#define CMD_W_REG 0x20        // 写寄存器指令
#define CMD_RX_PL_WID 0x60    // 读取接收数据长度
#define CMD_R_RX_PAYLOAD 0x61 // 读取接收数据指令
#define CMD_W_TX_PAYLOAD 0xA0 // 写待发数据指令
#define CMD_FLUSH_TX 0xE1     // 冲洗发送 FIFO指令
#define CMD_FLUSH_RX 0xE2     // 冲洗接收 FIFO指令
#define CMD_REUSE_TX_PL 0xE3  // 定义重复装载数据指令
#define CMD_NOP 0xFF          // 保留，可用作读取status寄存器

#define CMD_W_ACK_PAYLOAD(P) (0xA8 | (P & 0x0F)) //PRX模式装载PAYLOAD并使能P通道
#define CMD_W_TX_PAYLOAD_NO_ACK 0xB0             //PTX模式写NO ACK数据

//***********************NRF 寄存器地址***********************************//
#define REG_CONFIG      0x00       // 配置收发状态，CRC校验模式以及收发状态响应方式
#define REG_EN_AA       0x01       // 自动应答功能设置
#define REG_EN_RXADDR   0x02       // 可用信道设置
#define REG_SETUP_AW    0x03       // 收发地址宽度设置
#define REG_SETUP_RETR  0x04       // 自动重发功能设置
#define REG_RF_CH       0x05       // 工作频率设置
#define REG_RF_SETUP    0x06       // 发射速率、功耗功能设置
#define REG_STATUS      0x07       // 状态寄存器
#define REG_OBSERVE_TX  0x08       // 发送监测功能
#define REG_RPD         0x09       // 接收功率检测
#define REG_RX_ADDR_P0  0x0A       // 频道0接收数据地址
#define REG_RX_ADDR_P1  0x0B       // 频道1接收数据地址
#define REG_RX_ADDR_P2  0x0C       // 频道2接收数据地址
#define REG_RX_ADDR_P3  0x0D       // 频道3接收数据地址
#define REG_RX_ADDR_P4  0x0E       // 频道4接收数据地址
#define REG_RX_ADDR_P5  0x0F       // 频道5接收数据地址
#define REG_TX_ADDR     0x10       // 发送地址寄存器
#define REG_RX_PW_P0    0x11       // 接收频道0接收数据长度
#define REG_RX_PW_P1    0x12       // 接收频道1接收数据长度
#define REG_RX_PW_P2    0x13       // 接收频道2接收数据长度
#define REG_RX_PW_P3    0x14       // 接收频道3接收数据长度
#define REG_RX_PW_P4    0x15       // 接收频道4接收数据长度
#define REG_RX_PW_P5    0x16       // 接收频道5接收数据长度
#define REG_FIFO_STATUS 0x17       // FIFO栈入栈出状态寄存器设置
#define REG_DYNPD       0x1C       // 动态数据包长度
#define REG_FEATURE     0x1D       // 特点寄存器

#define MAX_TX_BIT  		    0x10       //达到最大发送次数中断
#define TX_OK_BIT   		    0x20       //TX发送完成中断
#define RX_OK_BIT   		    0x40       //接收到数据中断

#define NRF_SPI SPI2               //定义NRF使用的SPI
//24L01发送接收数据宽度定义
#define TX_ADR_WIDTH 5    //5字节的地址宽度
#define RX_ADR_WIDTH 5    //5字节的地址宽度
#define TX_PLOAD_WIDTH 32 //32字节的用户数据宽度
#define RX_PLOAD_WIDTH 32 //32字节的用户数据宽度
/* NRF2401 端口定义***************************************************/
#define CSN_RCC   RCC_APB2Periph_GPIOG
#define CSN_PORT  GPIOG
#define CSN_PIN   GPIO_Pin_7
#define CE_RCC    RCC_APB2Periph_GPIOG
#define CE_PORT   GPIOG
#define CE_PIN    GPIO_Pin_8
#define IRQ_RCC   RCC_APB2Periph_GPIOG
#define IRQ_PORT  GPIOG
#define IRQ_PIN   GPIO_Pin_6

#define NRF_CSN_L() GPIO_ResetBits (CSN_PORT, CSN_PIN)
#define NRF_CSN_H() GPIO_SetBits   (CSN_PORT, CSN_PIN)
#define NRF_CE_L()  GPIO_ResetBits (CE_PORT , CE_PIN)
#define NRF_CE_H()  GPIO_SetBits   (CE_PORT , CE_PIN)
#define IRQ_Read()  GPIO_ReadInputDataBit(IRQ_PORT,IRQ_PIN)

typedef enum /* 定义NRF SPI选择*/
{
  spi1_config = 1,
  spi2_config
} spi_eunm;

typedef enum /*定义NRF数据发射率*/
{
  data_rata_250K = 0,
  data_rata_1M,
  data_rata_2M
} NRFrate_enum;

typedef enum /* 定义NRF发射增益*/
{
  power_0dBM = 0,
  power_6dBM,
  power_12dBM,
  power_18dBM
} NRFpower_enum;

typedef enum /* 定义NRF数据重发间隔*/
{
  TxInterval_250us = 0,
  TxInterval_500us,
  TxInterval_750us,
  TxInterval_1000us,
  TxInterval_1250us,
  TxInterval_1500us,
  TxInterval_1750us,
  TxInterval_2000us,
  TxInterval_2250us,
  TxInterval_2500us,
  TxInterval_2750us,
  TxInterval_3000us,
  TxInterval_3250us,
  TxInterval_3500us,
  TxInterval_3750us,
  TxInterval_4000us,
} NRFTxInterval_enum;

typedef enum /* 定义NRF模式选择*/
{
  RX_MODE = 0,
  TX_MODE
} NRF_modeENUM;

typedef enum /* 定义NRF应答通道选择*/
{
  ENAA_P0 = 1,  
  ENAA_P1,
  ENAA_P2,
  ENAA_P3,
  ENAA_P4,
  ENAA_P5,
} NRFACKCHannl_enum;

typedef enum /*定义发射数据包格式*/
{
  ACK_PLAYLOAD_MODE = 0,   /* 发送带应答的动态数据包 */
  NO_ACK_PLAYLOAD_MODE,    /* 发送不带应答动态数据包 */
  PLAYLOAD_MODE,           /* 直接发送动态数据包*/
} NRFAckMode_enum;

typedef enum /* 定义NRF事件 */
{
  MAX_TX      = 0x10,             /* 最大重发事件 */
  TX_OK       = 0x20,             /* 发射成功事件 */
  RX_OK       = 0x40 ,            /* 接收成功事件*/
  OTHER_EVENT = 0x00
} NRFEvent_enum;

/*function ***************************************************************/
void NRF2401_Port_Init(void);                                     /* NRF端口初始化 */
uint8_t SPI_RW_Bybt(SPI_TypeDef *SPIx, uint8_t data);             /* SPI读写操作*/
uint8_t NRF_write_reg(uint8_t reg, uint8_t cmd);                  /* NRF写入一个字节指令 */
uint8_t NRF_read_reg(uint8_t reg);                                /* NRF读取一个字节数据 */
uint8_t NRF_Writes(uint8_t reg, const uint8_t *buf, uint8_t len); /* NRF写入多个数据 */
uint8_t NRF_Reads(uint8_t reg, uint8_t *buf, uint8_t len);        /* NRF读取多个数据 */
uint8_t Check_Nrf2401(void);                                      /* 检测NRF是否在线 */
void NRF_SetFreChannl(uint8_t frechannel);                        /* 设置NRF通信频段 */
void NRF_SetDataRate(NRFrate_enum datarate);                      /* 设置NRF数据发射率 */
void NRF_setPower(NRFpower_enum power);                           /* 设置NRF发增益 */
void NRF_SetTxInterval(NRFTxInterval_enum txinterval);            /* 设置NRF重发时间间隔 */
void NRF_setArc(uint8_t arc);                                     /* 设置NRF最大重发次数 */
void NRF_Init(NRF_modeENUM nrf_mode);                             /* 初始NRF设置 */
NRFEvent_enum NRF_Sendpackage(uint8_t *tx_buff, uint8_t Len);     /* NRF发一个数据包*/
NRFEvent_enum NRF_RXpackage(uint8_t *rx_buff, uint8_t *rx_len);   /* NRF接收一个数据包*/  
#endif 