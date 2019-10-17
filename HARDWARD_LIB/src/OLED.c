/*******************************************************************************
  @File   : OLED.c
  @Author : 罗涛
  @Date   : 2019年6月6日 20.28
  @Brief  : OLED显示驱动
  @Others : none 
  @History: none
  @Modification: V1.0.0
   4.使用操作见Example.txt
 */
/* Includes ----------------------------------------------------------------------------------------*/
#include "oled.h"
#include "codetab.h"
/*Defines -----------------------------------------------------------------------------------------*/

/*Variables ---------------------------------------------------------------------------------------*/

/*Functions ---------------------------------------------------------------------------------------*/

/**
  * @brief  OLED模拟SPI初始化
  * @param  None
  * @retval None
  */
void OLED_SPI_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; //定义结构体变量

  RCC_APB2PeriphClockCmd(OLED_CLK_RCC, ENABLE); /* 配置CLK引脚*/
  GPIO_InitStructure.GPIO_Pin = OLED_CLK_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(OLED_CLK_PORT, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(OLED_CS_RCC, ENABLE); /* 配置CS引脚*/
  GPIO_InitStructure.GPIO_Pin = OLED_CS_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(OLED_CS_PORT, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(OLED_DC_RCC, ENABLE); /* 配置DC引脚 */
  GPIO_InitStructure.GPIO_Pin = OLED_DC_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(OLED_DC_PORT, &GPIO_InitStructure);

  RCC_APB2PeriphClockCmd(OLED_MOSI_RCC, ENABLE); /* 配置MOSI引脚 */
  GPIO_InitStructure.GPIO_Pin = OLED_MOSI_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(OLED_MOSI_PORT, &GPIO_InitStructure);
}

/**
  * @brief  OLED写数据
  * @param  data；写的数据
  * @retval 无
  */
void OLED_SPIWriteDate(uint8_t data)
{
  uint8_t i = 0;
  OLED_DC_OUT_H();
  for (i = 0; i < 8; i++)
  {
    OLED_CLK_OUT_L();
    if (data & 0x80)
    {
      OLED_MOSI_OUT_H();
    }
    else
    {
      OLED_MOSI_OUT_L();
    }
    OLED_CLK_OUT_H();
    data <<= 1;
  }
}

/**
  * @brief  OLED写命令
  * @param  cmd；写的命令
  * @retval 无
  */
void OLED_SPIWriteCmd(uint8_t cmd)
{
  uint8_t i = 0;
  OLED_DC_OUT_L();
  for (i = 0; i < 8; i++)
  {
    OLED_CLK_OUT_L();
    if (cmd & 0x80)
    {
      OLED_MOSI_OUT_H();
    }
    else
    {
      OLED_MOSI_OUT_L();
    }
    OLED_CLK_OUT_H();
    cmd <<= 1;
  }
}

/**
  * @brief  OLED写数据
  * @param  data；写的数据
  * @retval 无
  */
void OLED_WriteDate(uint8_t data)
{
#ifdef  OLED_IIC /* 如果使用的IIC接口的OELD */
        IICDevice_WriteByte(0x78, 0x40, data);
#endif
    
    
#ifdef  OLED_SPI /* 如果使用的是SPI接口的OLED*/
        OLED_SPIWriteDate(data);
#endif
}

/**
  * @brief  OLED写命令
  * @param  cmd；写的命令
  * @retval 无
  */
void OLED_WriteCmd(uint8_t cmd)
{
uint16_t state = 1;
#ifdef   OLED_IIC /* 如果使用的是IIC接口的OLED*/
         state = IICDevice_WriteByte(0x78,0x00,cmd);
 	       if(state == 0)
		     printf("oled error\r\n");
    
#endif
    
#ifdef   OLED_SPI /* 如果使用的是SPI接口的OLED*/
         OLED_SPIWriteCmd(cmd);

#endif

}

/**
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
#ifdef  OLED_IIC           /* 如果使用的是SPI接口的OLED*/
        IIC_Init();        
#endif
    
#ifdef  OLED_SPI            /* 如果使用的是SPI接口的OLED*/
        OLED_SPI_Init();
#endif
  
	  GPIO_InitTypeDef GPIO_InitStructure;
	
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);         /* 配置SDA引脚*/
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_12;        
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);	
  
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
  delay_ms(200);
  GPIO_SetBits(GPIOB,GPIO_Pin_12);
	
  OLED_WriteCmd(0xAE); //display off
  OLED_WriteCmd(0x20); //Set Memory Addressing Mode
  OLED_WriteCmd(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
  OLED_WriteCmd(0xb0); //Set Page Start Address for Page Addressing Mode,0-7
  OLED_WriteCmd(0xc8); //Set COM Output Scan Direction
  OLED_WriteCmd(0x00); //---set low column address
  OLED_WriteCmd(0x10); //---set high column address
  OLED_WriteCmd(0x40); //--set start line address
  OLED_WriteCmd(0x81); //--set contrast control register
  OLED_WriteCmd(0xff); //???? 0x00~0xff
  OLED_WriteCmd(0xa1); //--set segment re-map 0 to 127
  OLED_WriteCmd(0xa6); //--set normal display
  OLED_WriteCmd(0xa8); //--set multiplex ratio(1 to 64)
  OLED_WriteCmd(0x3F); //
  OLED_WriteCmd(0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
  OLED_WriteCmd(0xd3); //-set display offset
  OLED_WriteCmd(0x00); //-not offset
  OLED_WriteCmd(0xd5); //--set display clock divide ratio/oscillator frequency
  OLED_WriteCmd(0xf0); //--set divide ratio
  OLED_WriteCmd(0xd9); //--set pre-charge period
  OLED_WriteCmd(0x22); //
  OLED_WriteCmd(0xda); //--set com pins hardware configuration
  OLED_WriteCmd(0x12);
  OLED_WriteCmd(0xdb); //--set vcomh
  OLED_WriteCmd(0x20); //0x20,0.77xVcc
  OLED_WriteCmd(0x8d); //--set DC-DC enable
  OLED_WriteCmd(0x14); //
  OLED_WriteCmd(0xaf); //--turn on oled panel
  OLED_CLS();
  OLED_SetPos(0, 0);
}

/**
  * @brief  OLED设置起点位置
  * @param  x 横坐标   0~127
  *         y 纵坐标   0~7
  * @retval 无
  */
void OLED_SetPos(uint8_t x, uint8_t y)
{
  OLED_WriteCmd(0xb0 + y);
  OLED_WriteCmd(((x & 0xf0) >> 4) | 0x10);
  OLED_WriteCmd((x & 0x0f) | 0x01);
}

/**
  * @brief  OLED全屏填充
  * @param  fill_data；填充命令
  * @retval 无
  */
void OLED_Fill(uint8_t fill_data)
{
  uint8_t m, n;
  for (m = 0; m < 8; m++)
  {
    OLED_WriteCmd(0xb0 + m); //page0-page1
    OLED_WriteCmd(0x00);     //low column start address
    OLED_WriteCmd(0x10);     //high column start address
    for (n = 0; n < 128; n++)
    {
      OLED_WriteDate(fill_data);
    }
  }
}

/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void OLED_CLS(void)
{
  OLED_Fill(0x00);
}

/**
  * @brief  OLED唤醒
  * @param  无
  * @retval 无
  */
void OLED_ON(void)
{
  OLED_WriteCmd(0X8D); //设置电荷泵
  OLED_WriteCmd(0X14); //开启电荷泵
  OLED_WriteCmd(0XAF); //OLED唤醒
}

/**
  * @brief  OLED休眠
  * @param  无
  * @retval 无
  */
void OLED_OFF(void)
{
  OLED_WriteCmd(0X8D); //设置电荷泵
  OLED_WriteCmd(0X10); //关闭电荷泵
  OLED_WriteCmd(0XAE); //OLED休眠
}

/**
  * @brief  OLED绘制一个点
  * @param  x ；横坐标  0~127
  *         y ；纵坐标  0~7
  * @retval 无
  */
void OLED_PutPixel(uint8_t x, uint8_t y)
{
  uint8_t data1; //data1当前点的数据

  OLED_SetPos(x, y);
  data1 = 0x01 << (y % 8);
  OLED_WriteCmd(0xb0 + (y >> 3));
  OLED_WriteCmd(((x & 0xf0) >> 4) | 0x10);
  OLED_WriteCmd((x & 0x0f) | 0x00);
  OLED_WriteDate(data1);
}

/**
  * @brief  OLED显示ASCII字符  有6*8和8*16大小可选
  * @param  x    横坐标  0~127
  *			    y    纵坐标  0~7
  *			   ch    字符
  *    TextSize  字符大小  1 6X8  
  *                      2 8X16
  * @retval 无
  */
void OLED_ShowStr(uint8_t x, uint8_t y, uint8_t ch[], uint8_t TextSize)
{
  uint8_t c = 0, i = 0, j = 0;
  switch (TextSize)
  {
  case 1:
  {
    while (ch[j] != '\0')
    {
      c = ch[j] - 32;
      if (x > 126)
      {
        x = 0;
        y++;
      }
      OLED_SetPos(x, y);
      for (i = 0; i < 6; i++)
        OLED_WriteDate(F6x8[c][i]);
      x += 6;
      j++;
    }
  }
  break;
  case 2:
  {
    while (ch[j] != '\0')
    {
      c = ch[j] - 32;
      if (x > 120)
      {
        x = 0;
        y++;
      }
      OLED_SetPos(x, y);
      for (i = 0; i < 8; i++)
        OLED_WriteDate(F8X16[c * 16 + i]);
      OLED_SetPos(x, y + 1);
      for (i = 0; i < 8; i++)
        OLED_WriteDate(F8X16[c * 16 + i + 8]);
      x += 8;
      j++;
    }
  }
  break;
  }
}

/**
  * @brief  OLED在指定的地址显示整数数字
  * @param  x        横坐标   0~127
  *		      y        纵坐标   0~7
  *			   Number    要显示的数字字符
  *        TextSize  字体大小  1 6X8 
  *                           2 8X16
  *			   N         字符长度  0 < N < 11 (1~9999999999)  
  * @retval 无
  */
void OLED_ShowNum(uint8_t x, uint8_t y, uint8_t Number, uint8_t TextSize, int N)
{
  uint8_t ch[10] = {0};
  int n;

  if (N < 1)
    N = 1;
  if (N > 10)
    N = 10;

  for (n = (N - 1); n >= 0; n--)
  {
    ch[n] = Number % 10 + '0';
    Number = Number / 10;
  }

  OLED_ShowStr(x, y, ch, TextSize);
}

/**
  * @brief  OLED在指定的地址显示浮点数数字
  * @param  x   横坐标          0~127
  *			    y   纵坐标          0~7
  *			 real   要显示的数字字符
  *  TextSize   字体大小  1 6X8  
  *                      2 8X16
  *			   N    小数点后几位  0 < N < 5  
  * @retval 无
  */
void OLED_Show_FloatNum(uint8_t x, uint8_t y, double real, uint8_t TextSize, uint8_t N)
{
  uint8_t i_Count = 1;
  uint8_t n[12] = {0};
  u16 real_decimal = 0;
  int real_int = 0;
  long j = 1;
  double decimal = 0;

  if (real < 0)
  {
    real_int = (int)(-real);
  }
  else
  {
    real_int = (int)real;
  }

  decimal = real - real_int;
  real_decimal = decimal * 1e4;
  while (real_int / 10 / j != 0)
  {
    j = j * 10;
    i_Count++;
  }
  n[0] = (real_int / 10000) % 10;
  n[1] = (real_int / 1000) % 10;
  n[2] = (real_int / 100) % 10;
  n[3] = (real_int / 10) % 10;
  n[4] = (real_int / 1) % 10;
  n[5] = '.';
  n[6] = (real_decimal / 1000) % 10;
  n[7] = (real_decimal / 100) % 10;
  n[8] = (real_decimal / 10) % 10;
  n[9] = real_decimal % 10;
  n[6 + N] = '\0';
  for (j = 0; j < 10; j++)
    n[j] = n[j] + 16 + 32;
  if (real < 0)
  {
    i_Count += 1;
    n[5 - i_Count] = '-';
  }
  n[5] = '.';
  n[6 + N] = '\0';
  OLED_ShowStr(x, y, &n[5 - i_Count], TextSize);
}

/**
  * @brief  OLED显示汉字  16*16 
  * @param  x   横坐标
  *         y   纵坐标
  *			    N   汉字
  * @retval 无
  */
void OLED_ShowCN(uint8_t x, uint8_t y, uint8_t N)
{
  uint8_t wm = 0;
  u16 adder = 32 * N;
  OLED_SetPos(x, y);
  for (wm = 0; wm < 16; wm++)
  {
    OLED_WriteDate(F16x16[adder]);
    adder += 1;
  }
  OLED_SetPos(x, y + 1);
  for (wm = 0; wm < 16; wm++)
  {
    OLED_WriteDate(F16x16[adder]);
    adder += 1;
  }
}

/**
  * @brief  OLED显示图片
  * @param  同上，不做简述
  * @retval 无
  */
void OLED_ShowBMP(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t BMP[])
{
  unsigned int j = 0;
  unsigned char x, y;

  if (y1 % 8 == 0)
    y = y1 / 8;
  else
    y = y1 / 8 + 1;
  for (y = y0; y < y1; y++)
  {
    OLED_SetPos(x0, y);
    for (x = x0; x < x1; x++)
    {
      OLED_WriteDate(BMP[j++]);
    }
  }
}

/*---------------------------------------------- End ------------------------------------------------*/
