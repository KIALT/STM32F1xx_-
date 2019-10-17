/*******************************************************************************
  @File   : LCD_device.c
  @Author : 罗涛
  @Date   : 2019年6月2日 22.00
  @Brief  : LCD设备驱动
  @Others : None
  @History: 此函数目前只支持12864串行
            由于12864并行和1602需要大量的IO
            操作繁琐，这里就不写了 
  Modification: V1.0.0
*******************************************************************************/
#include "LCD_device.h"

/**
  * @brief  LCD发送一个字节数据
  * @param  data 发送的数据
  * @retval None
  */
void LCD_SendByte(uint8_t date)
{
  uint8_t i;
  for (i = 0; i < 8; i++)
  {
    SCK_OUT_L();
    delay_us(10);
    if (date & 0x80)
    {
      SID_OUT_H();
      delay_us(10);
    }
    else
    {
      SID_OUT_L();
      delay_us(10);
    }
    date <<= 1;
    delay_us(10);
    SCK_OUT_H();
  }
    SCK_OUT_L();
    delay_us(10);
}

/**
  * @brief  对LCD发送数据
  * @param  data 发送的数据
  * @retval None
  */
void LCD_Writedata(uint8_t date)
{
  CS_OUT_H();
  LCD_SendByte(0xfa);             /* 发送写数据指令*/
  LCD_SendByte(0xf0 & date);      /* 串行发送数据 每次只发高4位,低四位值为0*/
  LCD_SendByte(0xf0 & date << 4); /* 每次8位数据 分两次发送  先发高四位 在低四位*/
  delay_ms(5);                    /* 由于 串行的速度是并行的8分之1 ，所以短暂延时让12864有处理的时间*/
  CS_OUT_L();
}

/**
  * @brief  对LCD发送指令
  * @param  data 发送的数据
  * @retval None
  */
void LCD_WriteCmd(uint8_t cmdcode)
{
  CS_OUT_H();
  LCD_SendByte(0xf8);                /* 发送写指令 指令 */
  LCD_SendByte(0xf0 & cmdcode);      /* 高四位 */
  LCD_SendByte(0xf0 & cmdcode << 4); /* 低四位 */
  delay_ms(10);
  CS_OUT_L();
}

/**
  * @brief   选择LCD第一个字的位置
  * @param   x     横坐标 1~4
  *          y     纵坐标
  * @retval None
  */
void LCD_pos(char x, char y)
{
  uint8_t pos;
  switch (x)
  {
  case 1:
    pos = 0x80 + y; /* 第一行 */
    break;
  case 2:
    pos = 0x90 + y; /* 第二行 */
    break;
  case 3:
    pos = 0x88 + y; /* 第三行 */
    break;
  case 4:
    pos = 0x98 + y; /* 第四行 */
    break;
  }
  LCD_WriteCmd(pos); /* 发位置*/
}

/**
  * @brief   清空整个屏幕的数据
  * @param   None
  * @retval  None
  */
void LCD_clean(void)
{
  LCD_WriteCmd(0x30); /* 基础指令 */
  delay_ms(10);
  LCD_WriteCmd(0x01); /* 清除整个屏幕*/
  delay_ms(10);
}
/**
  * @brief   初始化LCD
  * @param   None
  * @retval  None
  */
void LCD_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  RCC_APB2PeriphClockCmd(SID_RCC, ENABLE); /* 初始化时钟*/
  RCC_APB2PeriphClockCmd(SCK_RCC, ENABLE);
  RCC_APB2PeriphClockCmd(CS_RCC, ENABLE);

  GPIO_InitStruct.GPIO_Pin   = CS_PIN; /* 配置CS*/
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(CS_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = SID_PIN; /* 配置SID*/
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SID_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin   = SCK_PIN; /* 配置SCK */
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SCK_PORT, &GPIO_InitStruct);

  LCD_WriteCmd(0x30); //选择基本指令集
  delay_ms(10);
  LCD_WriteCmd(0x0c); //开显示(无游标、不反白)
  delay_ms(10);
  LCD_WriteCmd(0x01); //清除显示，并且设定地址指针为00H
  delay_ms(10);
  LCD_WriteCmd(0x06); //游标的移动方向及指定显示的移位
  delay_ms(10);
  LCD_clean(); /*清空屏幕，准备显示数据*/
}

/**
  * @brief   LCD数据写入
  * @param   str  要显示的字符串
  * @retval  None
  */
void Display(char *str)
{
  while (*str != '\0')
  {
    LCD_Writedata(*str++); /* 循环写入数据 */
    delay_ms(2);           /* 等待数据处理完成*/
  }
}
/**
  * @brief   LCD显示
  * @param   x   显示数据的起始位置横坐标
  *          y   显示数据的起始位置纵坐标
  *          fomat 数据的类型
  *          ...   对应fomat格式的参数
  * @retval  None
  */
void LCD12864_Display(char x, char y, char *fomat, ...)
{
  char buffer[BUFF_SIZE] = {0}; /*申请一个缓冲区*/
  va_list ap;                   /* 定义一个指向上面...栈中指针 */
  va_start(ap, fomat);          /* 开启获取栈的数据 */
  vsprintf(buffer, fomat, ap);  /* 将栈中的数据按键fomat格式转换成字符串放在缓冲区*/

  LCD_pos(x, y);   /* 发送显示位置 */
  Display(buffer); /* 显示buffer中的数据 */
  va_end(ap);      /* 结束参数获取 */
}

/**
  * @brief   字符串插入函数
  * @param   str1   被插入的字符串
  *          str2   插入内容
  *          index  插入位置  
  * @retval  None
  */
bool strinsert(int index, char *str1,char *str2)
{ 
  uint8_t nlen1 = strlen(str1);         /*计算str1的大小*/
	uint8_t nlen2 = strlen(str2);         /*计算str2大小*/
	
	if(nlen1 < nlen2 + index)
	{
		return false;                     /*拷贝目标空间不够*/
	}
	char *temp = (char*)malloc(sizeof(uint8_t) * (nlen1 + nlen2 +1));  /*申请一个str1加str2大小的空间*/
	memcpy(temp,str1,index);                                           /*先拷贝str1前index个字符到temp里面*/
	memcpy(temp+index,str2,nlen2);                                     /*拷贝str2*/
	memcpy(temp+index +nlen2,str1+index,nlen1 - index);                /*将剩下的str1的字符拷贝到str1中*/
	memcpy(str1,temp,nlen1 + nlen2);                                   /*复制temp到str1*/
	str1[nlen1 + nlen2] = 0;
	
	free(temp);                                                        /*释放temp*/
	return true;                                                       /*拷贝成功*/
}