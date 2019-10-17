/*******************************************************************************
  @File   : IIC.c
  @Author : 罗涛
  @Date   : 2019年5月30日 22.18.30
  @Brief  : IIC驱动
  @Others : none 
  @History: none
  Modification: V1.0.0
  1.可以供给多种IIC设备的地成驱动函数
  2.增加代码移植性，全部都是以函数方式运行
	                  只有修改相应的函数就可以移植到任何
									  单片机上面
   3.简化的使用难度，只需要 修改头文件里面的
	                   SDA和SCL的端口宏就可以
									  自由在任何端口使用此函数
   4.使用操作见Example.txt
*******************************************************************************/
#include "IIC.h"

void IIC_Init(void)
{	
	  GPIO_InitTypeDef GPIO_InitStructure;
	
	  RCC_APB2PeriphClockCmd(IIC_SDA_RCC,ENABLE);         /* 配置SDA引脚*/
      GPIO_InitStructure.GPIO_Pin   = IIC_SDA_PIN;        
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(IIC_SDA_PORT, &GPIO_InitStructure);	

 	  RCC_APB2PeriphClockCmd(IIC_SCL_RCC,ENABLE);         /* 配置SCL引脚*/
      GPIO_InitStructure.GPIO_Pin   = IIC_SCL_PIN;        
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
      GPIO_Init(IIC_SCL_PORT, &GPIO_InitStructure);

      SDA_OUT_H();
	  SCL_OUT_H();         /*拉高SDA,SCL让IIC处于空闲状态*/
      
}
/**
  * @brief  发送开始信号
  * @param  None
  * @retval None
  */
void IIC_Start(void)
{
	SDAOut();                                   /*设置SDA为输出*/
	SDA_OUT_H();	  	  
	SCL_OUT_H();
	delay_us(4);                               /* 根据IIC设备的要求脉冲的要不小于一定的时间*/
 	SDA_OUT_L();                               /* 在一个脉冲把SDA由高拉低*/
	delay_us(4);
	SCL_OUT_L();                               //钳住I2C总线，准备发送或接收数据 
}	  
/**
  * @brief  发送停止信号
  * @param  None
  * @retval None
  */
void IIC_Stop(void)
{
	SDAOut();                                  /* 设定SDA为输出*/
	SCL_OUT_L();
	SDA_OUT_L();  /* 在一个脉冲把SDA由低拉高*/
 	delay_us(4);                               /* 根据IIC的要求脉冲的要不小于一定的时间*/
	SCL_OUT_H(); 
	SDA_OUT_H();
	delay_us(4);							   	
}
/**
  * @brief  等待应答
  * @param  None
  * @retval 返回应答状态 1 成功应答
	*                      0 应答失败
  */
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime = 0;   /* 应答等待时间*/
	uint8_t state = true;	   /* 应答状态*/
	SDAIn();				         /* 设置SDA为输入*/
	SDA_OUT_H();
	delay_us(1);
    SCL_OUT_H();
  delay_us(1);
	while (READ_SDA())
	{
		ucErrTime++;				       /*增加等待时间*/
		if (ucErrTime > 250)       /*等待超时*/
		{
			IIC_Stop();
			state = false;           /*标记传输错误*/
            break;         
		}
	}
	GPIO_ResetBits(IIC_SCL_PORT, IIC_SCL_PIN); /*准备下次发送数据*/
	return state;
}
/**
  * @brief  发送应答
  * @param  None
  * @retval None
  */
void IIC_Ack(void)
{
	SCL_OUT_L();
	SDAOut();
	SDA_OUT_L();        /*在一个脉冲 把SDA拉低*/
	delay_us(1);
	SCL_OUT_H();
	delay_us(2);
	SCL_OUT_L();
}
/**
  * @brief  不发送应答
  * @param  None
  * @retval None
  */
void IIC_NAck(void)
{
	SCL_OUT_L();
	SDAOut();
	SDA_OUT_H();       /*在一个脉冲 把SDA拉高*/
	delay_us(1);
	SCL_OUT_H();
	delay_us(1);
	SCL_OUT_L();
}					 				     
/**
  * @brief  不发送应答
  * @param  None
  * @retval None
  */		  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDAOut(); 	    
    SCL_OUT_L();            //拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
		if((txd&0x80)>>7)                                    /*由高到低发送数据*/
		  {
                SDA_OUT_H();  /* 写1*/
	  	  }else 
		    {
				SDA_OUT_L();        /* 写0*/
			}
        txd<<=1; 	  
		delay_us(1);   
		SCL_OUT_H();
		delay_us(2); 
		SCL_OUT_L();	
		delay_us(2);
    }	 
} 	    
/**
  * @brief  发送一个字节
  * @param   ack  1  发送应答
	*               0 不发送应答 
  * @retval None
  */
uint8_t IIC_Read_Byte(unsigned char ack)
{
	uint8_t i;					   /* 发送数据位数 */
	uint8_t receive = 0;  /*  读取的数据  */
	SDAIn();				      /* 设置SDA为输入 */
	for (i = 0; i < 8; i++)
	{     
    GPIO_ResetBits(IIC_SCL_PORT, IIC_SCL_PIN);
		delay_us(2);
		GPIO_SetBits(IIC_SCL_PORT, IIC_SCL_PIN);
    delay_us(2);
		receive <<= 1;
        
		if (READ_SDA())
	  receive++; /* 写1*/
		delay_us(1);
	}
	if (ack)
		IIC_Ack(); //发送应答
	else
		IIC_NAck(); //不发送应答
	return receive;
}

/**
  * @brief  从IIC设备读取一个字节数据
  * @param   SlaveAddr    器件地址
	*          interAddr    寄存器地址
  * @retval 发回读取interAddr地址的数据
  */
uint8_t IICDevice_ReadByte(uint8_t SlaveAddr, uint8_t interAddr)
{
	uint8_t recrive = 0; /* 读取的数据*/
	IIC_Start();
	IIC_Send_Byte(SlaveAddr); /* 发送器件地址+写指令*/
	IIC_Wait_Ack();
	IIC_Send_Byte(interAddr); /* 发送要读取的寄存器的地址*/
	IIC_Wait_Ack();

	IIC_Start();
	IIC_Send_Byte(SlaveAddr | 1); /*器件地址+读指令*/
	IIC_Wait_Ack();
	recrive = IIC_Read_Byte(0);
	IIC_Stop(); /* 结束读取 */
	return recrive;
}
/**
  * @brief  从IIC设备读取多个字节数据
  * @param  SlaveAddr    器件地址
	*         interAddr    寄存器地址
	*         len          字节数量
  *         rbuf         数据缓冲器
  * @retval None
  */
uint8_t IICDevice_ReadBytes(uint8_t SlaveAddr, uint8_t interAddr, uint8_t len, uint8_t *rbuf)
{
	uint8_t i = 0;				/* 用来循环*/
	uint8_t state = true; /*读取状态*/
	IIC_Start();
	IIC_Send_Byte(SlaveAddr); /* 发送器件地址+写指令 */
	state = IIC_Wait_Ack();		/* 读取读取状态 */
	IIC_Send_Byte(interAddr); /* 发送寄存器地址 */
	IIC_Wait_Ack();

	IIC_Start();
	IIC_Send_Byte(SlaveAddr | 1); /*发送器件地址+读指令*/
	IIC_Wait_Ack();
	for (i = 0; i < len; i++)
	{
		if (i == len - 1)
		{
			rbuf[i] = IIC_Read_Byte(0);   /* 最后一个不需要自加寄存器地址*/
		}
		else
        {
            rbuf[i] = IIC_Read_Byte(1); /* 每次应答后IIC设备读自动把寄存器地址自加1*/
        }
			
	}
	IIC_Stop(); /* 结束数据读取 */
	return state;
}

/**
  * @brief   往IIC设备发送指令
  * @param   SlaveAddr    器件地址
	*          interAddr    寄存器地址
	*          cmd          指令
  * @retval  state        true   写入成功
	*                       false  写人失败 
  */
uint8_t IICDevice_WriteByte(uint8_t SlaveAddr, uint8_t interAddr, uint8_t cmd)
{
	uint8_t state = true; /*读取状态*/
	IIC_Start();
	IIC_Send_Byte(SlaveAddr); /* 发送器件地址+写指令*/
	state = IIC_Wait_Ack();
	IIC_Send_Byte(interAddr); /* 发送寄存器地址 */
	IIC_Wait_Ack();
	IIC_Send_Byte(cmd); /* 发送指令 */
	IIC_Wait_Ack();
	IIC_Stop();		/* 结束发送 */
	return state; /* 发回读取状态 */
}

/**
  * @brief  往IIC设备写入多个字节数据
  * @param   SlaveAddr    器件地址
	*          interAddr    寄存器地址
	*          len          字节数量
  *          rbuf         数据缓冲器
  * @retval  state        true  写入成功
	*                       false 写人失败
  */
uint8_t IICDevice_WriteBytes(uint8_t SlaveAddr, uint8_t interAddr, uint8_t len, uint8_t *wbuf)
{
	uint8_t i = 0;				/* 用于循环*/
	uint8_t state = true; /* 写入状态*/
	IIC_Start();
	IIC_Send_Byte(SlaveAddr); /* 发送器件地址+写指令 */
	state = IIC_Wait_Ack();		/*查看写入状态*/
	IIC_Send_Byte(interAddr); /* 发送寄存器地址*/
	IIC_Wait_Ack();
	for (i = 0; i < len; i++)
	{
		IIC_Send_Byte(wbuf[i]); /* 循环发送指令*/
		IIC_Wait_Ack();
	}
	IIC_Stop();
	return state; /* 发回读回状态*/
}
