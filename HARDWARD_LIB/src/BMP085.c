/*******************************************************************************
  @File   : BMP085.c
  @Author : 罗涛
  @Date   : 2019年6月4日 22.53
  @Brief  : BMP085气压计驱动代码
  @Others : none 
  @History: none
  @Modification: V1.0.0
  BMP085 是一款气压传感器，和其他相同的气压传感器器的驱动方式类似
*******************************************************************************/

#include "bmp085.h"

_Bmp085Param bmp085Param ={0};                         /* BMP085校检系数*/
/**
  * @brief  Bmp085读取数据（由于bmp085的寄存器是16位，每次读取也是16位）
  * @param  reg   数据寄存器
  *         times 读取次数
  * @retval 返回（带符号）的16位数据
  */
short BMP_read_byte(uint8_t reg, uint8_t times)
{
  uint8_t state = true;                                    /* BMP085读取状态*/
  uint8_t msb = 0;                                         /* BMP寄存器是16位每次先发高8位*/
  uint8_t lsb = 0;                                         /* 在发低8位*/
  short recive = 0;                                       /* 读取寄存器的值16位*/
  uint8_t rxBuffer[10] = {0};                             /* 用于支持IIC读取多个字节的缓冲区*/
  state = IICDevice_ReadBytes(BMP085_ADDR, reg, times, rxBuffer); /*先读高8位，在读低8位*/
  recive = ((short)rxBuffer[0]) << 8 | rxBuffer[1];       /* 合并数据*/
  
  return recive;
}
/**
  * @brief  Bmp085写指令
  * @param  reg      数据寄存器
  *         cmd      要发送的指令
  * @retval 写入状态  1 写入成功
  *                  0写人失败
  */
uint8_t BMP_Write_byte(uint8_t reg, uint8_t cmd)
{
  uint8_t state = true; /* 写入状态*/
  state = IICDevice_WriteByte(BMP085_ADDR, reg, cmd);
  return state;
}
/*
  * @brief  Bmp085初始化
  * @param  None      
  * @retval None             
  */
void BMP085_Init(_Bmp085Param * bmp085Param)
{
  bmp085Param ->ac1  =  BMP_read_byte(AC1_MSB_ADDR, 2);
  bmp085Param ->ac2  =  BMP_read_byte(AC2_MSB_ADDR, 2);
  bmp085Param ->ac3  =  BMP_read_byte(AC3_MSB_ADDR, 2);
  bmp085Param ->ac4  =  BMP_read_byte(AC4_MSB_ADDR, 2);
  bmp085Param ->ac5  =  BMP_read_byte(AC5_MSB_ADDR, 2);
  bmp085Param ->ac6  =  BMP_read_byte(AC6_MSB_ADDR, 2);    /*读取储存在EEPROM的11字节 */
  bmp085Param ->b1   =  BMP_read_byte(B1_MSB_ADDR,  2);
  bmp085Param ->b2   =  BMP_read_byte(B2_MSB_ADDR,  2);
  bmp085Param ->mb   =  BMP_read_byte(MB_MSB_ADDR,  2);
  bmp085Param ->mc   =  BMP_read_byte(MC_MSB_ADDR,  2);
  bmp085Param ->md   =  BMP_read_byte(MD_MSB_ADDR,  2);
}

/******************读取BMP085的压力******************/
/*
    0xF4 为BMP085 的数据储存地址  
    根据你的OSS 的值取的不同 压力的数据的地址也不相 
    OSS = 0(0x34)  为1(0x74) 为2(0xB4) 为3(0XF4)
    这里OSS取0
  */
long BMP085_Read_Pres(void)
{
  long press = 0;
  BMP_Write_byte(0xF4, 0x34);     //发送读压力指令
  IIC_Stop();
  delay_ms(6);                    //等待转换完成最低4.5ms
  press = BMP_read_byte(0xF6, 2); //读2个字节 因为压力的是19位的 地址0xF6(高8位) ,0xF7(低8位),0xF8(最低3位)
  press &= 0x0000FFFF;
  return press;
}
/***************读取BMP085的温度值***************/
/*
   根据OSS的值来确定 延时多少 OSS = 0(最低4.5ms) 为1（最低7.5ms）
   为2（最低13.5ms）,为3(最低25.5ms)
   这里OS取0
  */
short BMP085_Read_tempre(void)
{ 
  BMP_Write_byte(0xF4, 0X2E);      //发送读温度指令
  IIC_Stop();  
  delay_ms(6);                     //等待最低4.5ms的转换周期

  return BMP_read_byte(0xF6, 2);   //读取温度值
}

/*************根据算法解算BMP085的压力值*******************/
int BMP085_Conversion(_Bmp085Param * bmp085Param)
{
  long Ut = 0;
  long Up = 0;
  long b6 = 0, x1 = 0, x2 = 0, x3 = 0, b3 = 0, b5 = 0, p = 0;
  u32 b4 = 0, b7 = 0;

  Ut  = BMP085_Read_Pres();                    /* 读取气压*/
  Up  = BMP085_Read_tempre();                  /* 读取温度*/


  //计算b6
  x1 = (((int)Ut - (int)bmp085Param->ac6) * (int)bmp085Param->ac5) >> 15;
  x2 = ((int)bmp085Param->mc << 11) / (x1 + bmp085Param->md);
  b5 = x1 + x2;
  b6 = b5 - 4000;
  Ut = ((b5 + 8) >> 4);
 
  // 计算 B3
  x1 = (bmp085Param->b2 * (b6 * b6) >> 12) >> 11;
  x2 = (bmp085Param->ac2 * b6) >> 11;
  x3 = x1 + x2;
  b3 = (((((int)bmp085Param->ac1) * 4 + x3) << OSS) + 2) >> 2;

  // 计算 B4
  x1 = (bmp085Param->ac3 * b6) >> 13;
  x2 = (bmp085Param->b1 * ((b6 * b6) >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (bmp085Param->ac4 * (uint32_t)(x3 + 32768)) >> 15; 

  //计算 气压
  b7 = ((uint32_t)(Up - b3) * (50000 >> OSS));
  if (b7 < 0x80000000)
  {
    p = (b7 << 1) / b4;
  }
  else
  {
    p = (b7 / b4) << 1;
  }

  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  Up = p + ((x1 + x2 + 3791) >> 4);

  return (uint32_t)Up;
}

/**
  * @brief  获得海抜高度
  * @param  _Bmp085Param 初始化时读取的校检系数结构体      
  * @retval  当前海抜（米）             
  */
double BMP085_Get_Altitude(_Bmp085Param *bmp085Param)
{
	double altitude;
  long press = 0;
	press  = BMP085_Conversion(bmp085Param);			            //获取气压值
	altitude=44330.0*(1-pow((double)press/101325,1/5.255));  //根据芯片手册提供的公式计算海拔高度
	//altitude*=100;	 		                                   //转换成厘米单位的高度值，调用时再换算成带小数的高度值，提高精度
	return altitude;
}
