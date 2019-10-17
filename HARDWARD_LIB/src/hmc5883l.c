/*******************************************************************************
//  @File   : hmc5883l.c
//  @Author : 罗涛
//  @Date   : 2019年6月4日 23.37
//  @Brief  : hmc5883l驱动
//  @Others : none 
//  @History: none
//  Modification: V1.0.0
    hmc5883l 最大输出频率为160hz
		hmc一款三轴地磁计
*******************************************************************************/

#include "hmc5883l.h"

/**
  * @brief  HMC5883l 初始化
  * @param  None
  * @retval None
  */
void HMC5883L_init(void)                  //HMC5883L地磁计驱动初始化
{ 
      uint8_t res;
	    while(res != 0x48)                            /* 检测hmc5883l*/
	   {
		  res = IICDevice_ReadByte(HMC5883L_Addr,0x0a); 
		  printf("HMCAerror\r\n");           
		  delay_ms(100);                              /*延时100ms,再次检测*/
	   }
       
	printf("HMC388l OK....\r\n");                   /*检测到hmc5883l */       
	IICDevice_WriteByte(HMC5883L_Addr,0x00,0x78);   /*采样平均8次，75HZ输出频率*/
	delay_ms(2);
	IICDevice_WriteByte(HMC5883L_Addr,0x01,0x20);   /*量程正负1.9Ga*/
	delay_ms(2);
  IICDevice_WriteByte(HMC5883L_Addr,0x02,0x00);   /*默认0x00*/
	delay_ms(2);
}

/**
  * @brief  获得HML388L    三轴地磁数据
  * @param  _Gemag         三轴数据结构体 
  * @retval  返回读取状态  fasle 读取失败
                           true  读取成功
  */
 uint8_t  HMC5883L_get_magnetic(_Gemag *gemag) //得到地磁计值
{
	  uint8_t buff[6] = {0};
    uint8_t state = true;
    state = IICDevice_ReadBytes(HMC5883L_Addr,X_MSB_REG,6,buff); /* 读取三轴地磁数据*/
     
    gemag->x = (uint16_t)buff[0]<<8 | buff[1];     
    gemag->y = (uint16_t)buff[2]<<8 | buff[3];
    gemag->z = (uint16_t)buff[4]<<8 | buff[5];
     
   return state;                                                /*返回读取状态*/
}

