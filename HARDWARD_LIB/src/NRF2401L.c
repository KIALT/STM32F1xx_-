/*******************************************************************************
  @File   : NRF2401l.c
  @Author : 罗涛
  @Date   : 2019.6.8  10.40
  @Brief  : nrf2401驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
  
       1.??ò?????Example.txt
*******************************************************************************/

/* include *******************************************************************/

#include "delay.h"
#include "nrf2401.h"

uint8_t  TX_ADD[TX_ADR_WIDTH]   ={0xe7,0xd1,0xf0,0x35,0x76};  /*自定义发送接收地址*/
uint8_t  RX_ADD_0[RX_ADR_WIDTH] ={0xe7,0xd1,0xf0,0x35,0x76}; 


void NRF2401_Port_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

   if( SPI1 == NRF_SPI)                 /*如果使的是SPI1*/
	 {
		 SPI1_Init();
	 }else if(SPI2 == NRF_SPI)           /*如果使用的是SPI2*/
	 {
		 SPI2_Init();
	 }else if (SPI3 == NRF_SPI)          /*如果使用的SPI3*/
   {
     SPI3_Init();
   }
   RCC_APB2PeriphClockCmd(CE_RCC,ENABLE);
   RCC_APB2PeriphClockCmd(CSN_RCC,ENABLE);
   RCC_APB2PeriphClockCmd(IRQ_RCC,ENABLE);
	
   GPIO_InitStruct.GPIO_Pin   = CE_PIN;              /* NRF2401 模式控制引脚*/
   GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(CE_PORT,&GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin   = CSN_PIN;               /* NRF2401的SPI片选*/
   GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(CSN_PORT,&GPIO_InitStruct);
	
	 GPIO_InitStruct.GPIO_Pin   = IRQ_PIN;               /* NRF2401中断输出引脚IRQ*/
   GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(IRQ_PORT,&GPIO_InitStruct);

}
/**
  * @brief  SPI读写数据（8位）
  * @param  SPIx   使用那个SPI
  *         data   发送的数据（8位） 
  * @retval 读取的数据（8位）
  */
uint8_t SPI_RW_Bybt(SPI_TypeDef *SPIx, uint8_t data)
{
  uint8_t i; /* 用于等待SPI的发送和接收的完成的判断*/

  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) /* 等待SPIx发射区为空*/
  {
    i++;
    if (i > 200)
    {
      return false; /* 超时退出*/
    }
  }
  SPI_I2S_SendData(SPIx, data); 
  i = 0;

  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET) /*等待SPIx接收区为空 */
  {
    i++;
    if (i > 200)
    {
      return false; /* 超时退出*/
    }
  }
  return SPI_I2S_ReceiveData(SPIx);
}

/**
  * @brief  NRF写指令
  * @param  reg    NRF寄存器
  *         cmd    指令
  * @retval        true  写入成功
  *                flase 写入失败
  */
uint8_t NRF_write_reg(uint8_t reg, uint8_t cmd)
{
  uint8_t status = true;
  NRF_CSN_L();                                    /* 关片选 */
  status = SPI_RW_Bybt(NRF_SPI, reg | CMD_W_REG); /* 发送指令*/
  SPI_RW_Bybt(NRF_SPI, cmd);
  NRF_CSN_H();                                    /*开启片选 使能SPI工作*/
  return status;                                  /* 返回写入状态 */
}

/**
  * @brief  NRF读数据（8位）
  * @param  reg    NRF数据寄存器
  * @retval 返回NRF 寄存器的里面的数据
  *  
  */
uint8_t NRF_read_reg(uint8_t reg) 
{
  uint8_t receive = true;
  NRF_CSN_L();                           /* 关片选 */
  SPI_RW_Bybt(NRF_SPI, reg | CMD_R_REG); /* 发送读指令+寄存器*/
  receive = SPI_RW_Bybt(NRF_SPI, 0XA5);  /* 读取NRF寄存器的数据*/
  NRF_CSN_H();                           /*开启片选 使能SPI工作*/
  return receive;
}

/**
  * @brief  NRF写入多个指令
  * @param  reg    NRF寄存器
  *         buf    指令
  *         len    指令长度
  * @retval true   写入成功 
  *         flase  写入失败 
  */        
uint8_t NRF_Writes(uint8_t reg, const uint8_t *buf, uint8_t len)
{
  uint8_t i = 0;
  uint8_t status = true;
  NRF_CSN_L();                        /* 关片选 */
  status = SPI_RW_Bybt(NRF_SPI, reg); /* 读取写入状态 */
  for (i = 0; i < len; i++)
  {
    SPI_RW_Bybt(NRF_SPI, buf[i]); /*连续写入指令*/
  }

  NRF_CSN_H();   /* 开片选*/
  return status; /* 返回写入状态*/
}
/**
  * @brief  NRF读取
  * @param  reg    NRF寄存器
  *         buf    接收缓冲区
  *         len    读取长度
  * @retval true   读取成功
  *         fasle  读取失败
  */
uint8_t NRF_Reads(uint8_t reg, uint8_t *buf, uint8_t len)
{
  uint8_t i = 0;
  uint8_t status = true;
  NRF_CSN_L();                        /* 关片选 */
  status = SPI_RW_Bybt(NRF_SPI, reg); /* 读取读取状态 */
  for (i = 0; i < len; i++)
  {
    buf[i] = SPI_RW_Bybt(NRF_SPI, 0); /* 连续读取*/
  }

  NRF_CSN_H();   /*开片选*/
  return status; /* 返回读取状态*/
}

/**
  * @brief  检测NRF2401是否在线
  * @param  None
  * @retval ture   在线
  *         flase  没有连接
  *  @other 通过向NRF2401 写入和读取地址是否相同，来判断NRF2401是否在线
  */
uint8_t Check_Nrf2401(void)
{
  uint8_t i;
  uint8_t check_address[RX_ADR_WIDTH] = {0};                 /*检测地址数组 */
  NRF_Writes(CMD_W_REG | REG_TX_ADDR, TX_ADD, TX_ADR_WIDTH); /*写入地址*/
  NRF_Reads(CMD_R_REG | REG_TX_ADDR, check_address, RX_ADR_WIDTH);

  for (i = 0; i < TX_ADR_WIDTH; i++)
  {
    printf("%x   ", check_address[i]); /*打印写入地址*/
  }
  printf("\r\n");
  for (i = 0; i < TX_ADR_WIDTH; i++)
  {
    if (check_address[i] != TX_ADD[i]) /* 检测读取到地址是否和写入地址相同*/
    {
      return false; /*检测失败，NRF未在线*/
    }
  }
  return true; /* 检测到NRFNRF2401*/
}
/**
  * @brief  设置NRF通信频段
  * @param  frechannel  0~125  2.4GHZ~2.525GHZ频段
  * @retval None
  */
void NRF_SetFreChannl(uint8_t frechannel)
{
   if(frechannel < 125)
   {
     NRF_write_reg(REG_RF_CH,frechannel);      /* 写入通信频段*/
   }
}
/**
  * @brief  设置NRF241的发送速率
  * @param  datarate  data_rata_250k   发送数率为250KB
  *                   data_rata_1M     发送数率为1M 
  *                   data_rata_2M     发送数率为2M  
  *                   [RF_DR_LOW, RF_DR_HIGH]:
  *                   [    5     ,   3       ]:
                      [00]    1Mbps
                      [01]    2Mbps
                      [10]    250kbps
                      [11]    Reserved     
  * @retval 
  *  
  */
 void NRF_SetDataRate(NRFrate_enum datarate)
 {
   uint8_t rate =0;
   rate = NRF_read_reg(REG_RF_SETUP);
   rate &= ~((1 << 5) | (1 << 3));    /* 清空以前设定的数率*/
   switch(datarate)
   {
   case data_rata_250K:
     rate |= ( (1 << 5) | (0 << 3));
     break;

   case data_rata_1M:
     rate |= ((0 << 5) | (0 << 3));
     break;

   case data_rata_2M:
     rate |= ((0 << 5) | (1 << 3));
     break;
  }
   NRF_write_reg(REG_RF_SETUP, rate); /* д写人设定数率*/
}
 /**
  * @brief   设定NRF2401的发射增益
  * @param  power power_0dBM   0dBM
  *               power_6dBM   6dBM
  *               power_12dBM  12dBm
  *               power_18dBM  18dBM
  * @retval  None
                    2:1  
                  [00] -18dBm
                  [01] -12dBm
                  [10] -6dBm
                  [11] -0dBm 
 */
 void NRF_setPower(NRFpower_enum power)
 {
   uint8_t old_power;
   old_power = NRF_read_reg(REG_RF_SETUP); /* 读取以前设定的发射增益*/
   old_power &= ~((1 << 1) | (1 << 2));    /* 清空以前设定发射增益*/
   switch (power)
   {
   case power_0dBM:
     old_power |= (1 << 2) | (1 << 1);
     break;

   case power_6dBM:
     old_power |= ( (1 << 2) | (0 << 1));
     break;

   case power_12dBM:
     old_power |= ((0 << 2) | (1 << 1));
     break;

   case power_18dBM:
     old_power |= ( (0 << 2) | (0 << 1));
     break;

   default:
     break;
   }
   NRF_write_reg(REG_RF_SETUP, old_power); /* 写入发射增益*/
 }
 
 /**
  * @brief  设定NRF重发间隔
  * @param  txinterval 250us~4000us
  * @retval None
  *       [7:4]
  *       [0000]   Wait 250uS
          [0001]   Wait 500uS
          [0010]   Wait 750uS
            ..
          [1111] Wait 4000uS
  */
 void NRF_SetTxInterval(NRFTxInterval_enum txinterval)
 {
    uint8_t time = 0;
    time |= (txinterval << 4);
    NRF_write_reg(REG_SETUP_RETR,time); 
 }

 /**
  * @brief  设置NRF数据重发上限次数
  * @param  arc  0~15
  * @retval None
  */
 void NRF_setArc(uint8_t arc)
 {
   uint8_t old_arc = 0;
   if (arc > 15)
     return;         /*设置 错误退出*/

   old_arc = NRF_read_reg(REG_SETUP_RETR);
   old_arc |= arc;
   NRF_write_reg(REG_SETUP_RETR, old_arc);
 }


 /**
  * @brief  初始化NRF
  * @param  NRF_modeENUM  RX_MODE 发射模式
  *                       TX_MODE 接收模式
  * @retval None
  */
void NRF_Init(NRF_modeENUM nrf_mode)
{
  NRF_Writes(CMD_W_REG | REG_RX_ADDR_P0, RX_ADD_0, RX_ADR_WIDTH); /* 写入通道0的地址*/
  NRF_Writes(CMD_W_REG | REG_TX_ADDR, TX_ADD, TX_ADR_WIDTH);      /* 写入发射地址*/
  NRF2401_Port_Init();
  while (!Check_Nrf2401())
  {
    printf("NO NRF2401..\r\n");
    delay_ms(100);
  }
  NRF_CE_L();
  printf("NRF2401 OK....\r\n");
  NRF_SetFreChannl(40);                /* 设置通信2.44GH频率*/
  NRF_SetDataRate(data_rata_2M);       /* 设置数据传输速率为2M*/
  NRF_setPower(power_0dBM);            /* 增益0dBM，低噪声增益模式*/
  NRF_setArc(10);                      /* 最大重发次数为10次*/
  NRF_SetTxInterval(TxInterval_500us); /* 重发间隔为500us，根据手册最低发射间隔为500us,太低数据容易出错*/
  NRF_write_reg(CMD_FLUSH_RX, 0xff);   /* 清空接收缓冲区*/
  NRF_write_reg(CMD_FLUSH_TX, 0xff);   /* 清空发射缓冲区*/

  if (nrf_mode == RX_MODE)
  {
    printf("RX_MODE Init\r\n");
    NRF_write_reg(REG_CONFIG, 0x0f);   /* 接收模式*/
    NRF_write_reg(REG_DYNPD, 0x01);    /* 使能通道0的动态有效数据长度*/
    NRF_write_reg(REG_FEATURE, 0x06);  /* 使能动态长度、ACK PLAYLOAD发送、W_TX_PAYLOAD_NOACK*/
    NRF_write_reg(REG_EN_AA, 0x01);    /* 使能通道0自动应答 */
  }
  else
  {
    printf("TX_MODE Init\r\n");
    NRF_write_reg(REG_CONFIG, 0x0e);    /* 发射模式,上电状态，使能16位CRC，开启最大接收重发中断,最大收发重发中断
                                        最大发送重发中断, 中断电平为低电平 */
    NRF_write_reg(REG_DYNPD, 0x01);     /* 使能通道0的动态有效数据长度*/
    NRF_write_reg(REG_FEATURE, 0x07);   /* 使能动态长度、ACK PLAYLOAD发送、W_TX_PAYLOAD_NOACK*/
  }
  NRF_CE_H();
}

 /**
  * @brief  检测NRF事件
  * @param  None
  * @retval TX_OK       发射成功
  *         RX_OK       接收成功
  *         MAX_RT      达到最大重发次数
  *         TOHER_EVENT 其他事件 
  */
NRFEvent_enum NRFEvent_check(void)
{
  uint8_t state;
  NRFEvent_enum nrf_event = OTHER_EVENT;
  state = NRF_read_reg(REG_STATUS);
  if (state & MAX_TX_BIT)
  {
    nrf_event = MAX_TX;
    printf("MAX_TX\r\n");
  }
  else if (state & TX_OK_BIT)
  {
    nrf_event = TX_OK;
    printf("TX_OK \r\n");
  }
  else if (state & RX_OK_BIT)
  {
    nrf_event = RX_OK;
    printf("RX_OK\r\n");
  }
  NRF_write_reg(REG_STATUS, 0x70);  /* 清空状态寄存器 */
  return nrf_event;
}
 /**
  * @brief  NRF发送一个数据包
  * @param  tx_buff  数据包（最大不超过32个字节）
  *         len      数据长度
  * @retval NRFEvent_enum 事件
  */
NRFEvent_enum NRF_Sendpackage(uint8_t *tx_buff, uint8_t Len)
{
  uint8_t state;
  NRF_CE_L();
  NRF_Writes(CMD_W_ACK_PAYLOAD(0), tx_buff, Len);
  NRF_CE_H();
  while (NRF_read_reg(REG_STATUS & 0x70) == 0);
  state = NRFEvent_check();
  if (state == MAX_TX)
  {
    return MAX_TX;
  }
  else if (state == TX_OK)
  {
    return TX_OK;
  }
  return OTHER_EVENT;
}
 /**
  * @brief  NRF接收一个数据包
  * @param  rx_buff  数据包（最大不超过32个字节）
  *         len      数据长度
  * @retval NRFEvent_enum 事件
  */
NRFEvent_enum NRF_RXpackage(uint8_t *rx_buff, uint8_t *rx_len)
{
  uint8_t len;
  NRFEvent_enum RxEvent = OTHER_EVENT;
  if (RX_OK == NRFEvent_check())
  {
    len = NRF_read_reg(CMD_RX_PL_WID);      /* 读取数据 */
    if ((len > 0) && (len < 33))
    {
      NRF_Reads(CMD_R_RX_PAYLOAD, rx_buff, len);
      *rx_len = len;
      RxEvent = RX_OK;
      printf("rxbuff = %s\r\n", rx_buff);
    }
    else
    {
      rx_len = 0;
    }
  }
  NRF_write_reg(CMD_FLUSH_RX, 0xff);      /*清空RX FIFO*/
  return RxEvent;
}
