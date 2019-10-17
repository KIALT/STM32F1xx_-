/*******************************************************************************
  @File   : Usart.c
  @Author : 罗涛
  @Date   : 2019年6月7日 13.42
  @Brief  : 串口综合驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
  
       1.使用操作见Example.txt
*******************************************************************************/

/* pulic include ************************* */

/*piravet inlcude*************************/
#include "usart.h"

/**
  * @brief  USART1工作参数配置
  * @param  baud  设定串口1的波特率 
  * @retval 无
  */
void Usart1_Init(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; /*将USART Tx的GPIO配置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; /*将USART Rx的GPIO配置为浮空输入模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baud;																			/* 配置波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;											/* 数据字长 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;													/* 配置停止位 */
	USART_InitStructure.USART_Parity = USART_Parity_No;															/* 配置校验位 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /* 配置硬件流控制 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									/* 配置工作模式，收发一起 */
	USART_Init(USART1, &USART_InitStructure);

	/*
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;          //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		            //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			             //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	                                //根据指定的参数初始化VIC寄存器
	USART_ITConfig(USART1, USART_IT_RXNE | USART_IT_TXE, ENABLE);   //开启串口接受中断
	 */

	// 使能串口
	USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  USART1工作参数配置
  * @param  baud  设定串口1的波特率 
  * @retval 无
  */
void Usart2_Init(uint32_t baud)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef  NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; /*将USART Tx的GPIO配置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; /*将USART Rx的GPIO配置为浮空输入模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baud;																			/* 配置波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;											/* 数据字长 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;													/* 配置停止位 */
	USART_InitStructure.USART_Parity = USART_Parity_No;															/* 配置校验位 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /* 配置硬件流控制 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									/* 配置工作模式，收发一起 */
	USART_Init(USART2, &USART_InitStructure);

	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;          //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		            //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			             //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	                                //根据指定的参数初始化VIC寄存器
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);   //开启串口接受中断
	 
	// 使能串口
	USART_Cmd(USART2, ENABLE);
}
void Usart3_Init(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; /*将USART Tx的GPIO配置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; /*将USART Rx的GPIO配置为浮空输入模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baud;																			/* 配置波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;											/* 数据字长 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;													/* 配置停止位 */
	USART_InitStructure.USART_Parity = USART_Parity_No;															/* 配置校验位 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /* 配置硬件流控制 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									/* 配置工作模式，收发一起 */
	USART_Init(USART3, &USART_InitStructure);

	/*
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;          //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		            //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			             //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	                                //根据指定的参数初始化VIC寄存器
	USART_ITConfig(USART3, USART_IT_RXNE | USART_IT_TXE, ENABLE);   //开启串口接受中断
	 */

	// 使能串口
	USART_Cmd(USART3, ENABLE);
}

void Usart4_Init(uint32_t baud)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; /*将USART Tx的GPIO配置为推挽复用模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; /*将USART Rx的GPIO配置为浮空输入模式 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = baud;																			/* 配置波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;											/* 数据字长 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;													/* 配置停止位 */
	USART_InitStructure.USART_Parity = USART_Parity_No;															/* 配置校验位 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; /* 配置硬件流控制 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;									/* 配置工作模式，收发一起 */
	USART_Init(UART4, &USART_InitStructure);

	/*
	NVIC_InitStructure.NVIC_IRQChannel = USART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;          //抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		            //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			             //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	                                //根据指定的参数初始化VIC寄存器
	USART_ITConfig(USART4, USART_IT_RXNE | USART_IT_TXE, ENABLE);   //开启串口接受中断
	 */

	// 使能串口
	USART_Cmd(UART4, ENABLE);
}

/**
  * @brief  USART  配置,工作参数配置
  * @param  baud  设定串口的波特率 
  * @retval 无
  */
void USART_Config(uint8_t Usart_num, uint32_t baud)
{
  switch (Usart_num)
	{
	case USART1_CONFIG:
	 Usart1_Init(baud);
	break;
	
	case USART2_CONFIG:
   Usart2_Init(baud);
	break;

	case USART3_CONFIG:
  Usart3_Init(baud);
  break;

	 case USART4_CONFIG:
	 Usart4_Init(baud);
	 break;

	default:
	break;
	}
}
/******************不使用微型标准库********************/
#pragma import(__use_no_semihosting)
//标准库需要的支持函数
struct __FILE
{
	int handle;

};

FILE __stdout;
//定义_sys_exit()以避免使用半主机模式
int _sys_exit(int x)
{
	x = x;
}
//重定义fputc函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USART1, (uint8_t) ch);

		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

		return (ch);
}


/**
  * @brief   串口数据发送
  * @param   USARTx 串口结构体
	*        fomat  发送数据的格式
             ...     要发送的数据
  * @retval  None
  */
void Usart_Send(USART_TypeDef *USARTx, const char *fomat, ...)
{
	char buffer[BUFF_SIZE] = {0}; /*发送数据缓冲区*/
	va_list ap;										/*声明一个指向堆栈的指针*/
	va_start(ap, fomat);					/*开始从栈中获取数据*/
	vsprintf(buffer, fomat, ap);	/*将栈中数据转换成fomat格式储放在缓冲区*/
	for (int i = 0; i < strlen(buffer); i++)
	{
		USARTx->DR = buffer[i]; /* 发送缓冲区数据*/
		while (!(USARTx->SR & USART_SR_TXE)); /*等待发送完成*/
	}
	va_end(ap); /*结束数据获取*/
}

	