/**
  **************************************************************************************************
  * @file     adc.c
  * @author   罗涛
  * @version  V1.0.0
  * @date     2019.5.31
  * @brief    ADC初始化,包含单路ADC和多路ADC应用
  **************************************************************************************************
  * @attention 
  *              
  *             1. 根据实际情况添加裁剪
  *
  **************************************************************************************************
  */
  
/*Includes ----------------------------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "adc.h"
#include "delay.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#ifdef  __ENABLE_ADC_
 
/*Defines -----------------------------------------------------------------------------------------*/
/*Variables ---------------------------------------------------------------------------------------*/
/*Functions ---------------------------------------------------------------------------------------*/

/**
  * @brief  初始化ADC的GPIO,可用于单路或多路,根据实际使用情况添加裁剪
  * @param  无
  * @retval 无
  */
void ADC_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE );	 				//使能GPIOA时钟 
	
	// PA0至PA6 作为模拟通道输入引脚   
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |    /* 根据实际情况修改通道*/
								   GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | 
								   GPIO_Pin_6 ;	 
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;							//模拟输入引脚       
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
/**
  * @brief  单路；ADC1 单通道初始化 
  * @param  无
  * @retval 无
  */
void ADC1_OneWay_Init(void)
{
  ADC_InitTypeDef ADC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1通道时钟

  ADC_GPIO_Init(); //初始化ADC引脚

  RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
  ADC_DeInit(ADC1);                 //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  //ADC工作模式:ADC1和ADC2工作在独立模式
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       //模数转换工作在单通道模式
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 //模数转换工作在单次转换模式
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              //ADC数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 1;                             //顺序进行规则转换的ADC通道的数目
  ADC_Init(ADC1, &ADC_InitStructure);                                 //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

  //	ADC_DMACmd(ADC1, ENABLE);												    	//开启DMA
  ADC_Cmd(ADC1, ENABLE);      //使能指定的ADC1
  ADC_ResetCalibration(ADC1); //使能复位校准
  while (ADC_GetResetCalibrationStatus(ADC1));                         //等待复位校准结束
  ADC_StartCalibration(ADC1); //开启AD校准
  while (ADC_GetCalibrationStatus(ADC1)) ; //等待校准结束
  // ADC_SoftwareStartConvCmd(ADC1, ENABLE);											//使能指定的ADC1的软件转换启动功能
}

/**
  * @brief  单路；ADC2 单通道初始化 
  * @param  无
  * @retval 无
  */
void ADC2_OneWay_Init(void)
{
  ADC_InitTypeDef ADC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //使能ADC1通道时钟

  ADC_GPIO_Init(); //初始化ADC引脚

  RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
  ADC_DeInit(ADC2);                 //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  //ADC工作模式:ADC1和ADC2工作在独立模式
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       //模数转换工作在单通道模式
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                 //模数转换工作在单次转换模式
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              //ADC数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 1;                             //顺序进行规则转换的ADC通道的数目
  ADC_Init(ADC2, &ADC_InitStructure);                                 //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

  //	ADC_DMACmd(ADC1, ENABLE);											 //开启DMA
  ADC_Cmd(ADC2, ENABLE);                             //使能指定的ADC1
  ADC_ResetCalibration(ADC2);                        //使能复位校准
  while (ADC_GetResetCalibrationStatus(ADC2)) ;      //等待复位校准结束
  ADC_StartCalibration(ADC2);                        //开启AD校准
  while (ADC_GetCalibrationStatus(ADC2));            //等待校准结束
  //	ADC_SoftwareStartConvCmd(ADC2, ENABLE);				 //使能指定的ADC1的软件转换启动功能
}

/**
  * @brief  多路: 初始化ADC1通道0至通道6  
  * @param  无
  * @retval 无
  */											   
void ADC1_Multipath_Init(void)
{
  ADC_InitTypeDef ADC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1通道时钟

  ADC_GPIO_Init(); //初始化ADC引脚

  RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
  ADC_DeInit(ADC1);                 //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  //ADC工作模式:ADC1和ADC2工作在独立模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;                        //多通道模式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                  //连续转换
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              //ADC数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 7;                             //顺序进行规则转换的ADC通道的数目
  ADC_Init(ADC1, &ADC_InitStructure);                                 //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

  //设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 7, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期

  //	ADC_DMACmd(ADC1, ENABLE);												//开启DMA
  ADC_Cmd(ADC1, ENABLE);                              //使能指定的ADC1
  ADC_ResetCalibration(ADC1);                         //使能复位校准
  while (ADC_GetResetCalibrationStatus(ADC1));        //等待复位校准结束
  ADC_StartCalibration(ADC1);                         //开启AD校准
  while (ADC_GetCalibrationStatus(ADC1));             //等待校准结束
  //	ADC_SoftwareStartConvCmd(ADC1, ENABLE);				  //使能指定的ADC1的软件转换启动功能
}	


/**
  * @brief  多路: 初始化ADC2通道0至通道6  
  * @param  无
  * @retval 无
  */											   
void ADC2_Multipath_Init(void)
{
  ADC_InitTypeDef ADC_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //使能ADC1通道时钟

  ADC_GPIO_Init(); //初始化ADC引脚

  RCC_ADCCLKConfig(RCC_PCLK2_Div6); //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
  ADC_DeInit(ADC2);                 //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;                  //ADC工作模式:ADC1和ADC2工作在独立模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;                        //多通道模式
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                  //连续转换
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //转换由软件而不是外部触发启动
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;              //ADC数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 7;                             //顺序进行规则转换的ADC通道的数目
  ADC_Init(ADC2, &ADC_InitStructure);                                 //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器

  //设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC2, ADC_Channel_0, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	
	ADC_RegularChannelConfig(ADC2, ADC_Channel_1, 2, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 3, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 4, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC2, ADC_Channel_4, 5, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC2, ADC_Channel_5, 6, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期
	ADC_RegularChannelConfig(ADC2, ADC_Channel_6, 7, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期

  //	ADC_DMACmd(ADC1, ENABLE);										 //开启DMA
  ADC_Cmd(ADC2, ENABLE);                           //使能指定的ADC1
  ADC_ResetCalibration(ADC2);                      //使能复位校准
  while (ADC_GetResetCalibrationStatus(ADC2));     //等待复位校准结束
  ADC_StartCalibration(ADC2);                      //开启AD校准
  while (ADC_GetCalibrationStatus(ADC2));          //等待校准结束
  //	ADC_SoftwareStartConvCmd(ADC1, ENABLE);									//使能指定的ADC1的软件转换启动功能
}	


/**
  * @brief  获得ADC1值 
  * @param  无
  * @retval 无
  */	
u16 Get_Adc1(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);								//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));			 //等待转换结束

	return ADC_GetConversionValue(ADC1);								//返回最近一次ADC1规则组的转换结果
}

/**
  * @brief  获得ADC2值 
  * @param  无
  * @retval 无
  */	
u16 Get_Adc2(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC2, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);							//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC ));			//等待转换结束

	return ADC_GetConversionValue(ADC2);								//返回最近一次ADC1规则组的转换结果
}

/**
  * @brief  求ADC1平均值
  * @param  ch ；通道
  *         times ；次数
  * @retval 无
  */	
u16 Get_Adc1_Average(u8 ch,u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for(t = 0; t < times; t++)
	{
		temp_val += Get_Adc1(ch);  										//均值滤波
	}
	return temp_val / times;
} 	 

/**
  * @brief  求ADC2平均值
  * @param  ch ；通道
  *         times ；次数
  * @retval 无
  */	
u16 Get_Adc2_Average(u8 ch,u8 times)
{
	u32 temp_val = 0;
	u8 t;
	for(t = 0; t < times; t++)
	{
		temp_val += Get_Adc2(ch);  										//均值滤波
	}
	return temp_val / times;
} 	
/*---------------------------------------------- End ------------------------------------------------*/
#endif
