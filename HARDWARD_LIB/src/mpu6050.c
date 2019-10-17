/*******************************************************************************
  @File   : mpu6050.c
  @Author : 罗涛
  @Date   : 2019年6月6日 22.18
  @Brief  : mpu6050驱动代码
  @Others : none 
  @History: none
  Modification: V1.0.0
  
*******************************************************************************/

#include "mpu6050.h"

#define DEFAULT_MPU_HZ (100)                      //定义DMP输出速度 最大50
#define q30 1073741824.0f                         //q30格式,long转float时的除数.
float q0 = 1.0f, q1 = 0.0f, q2 = 0.0f, q3 = 0.0f; //四元数
unsigned long sensor_timestamp;
short gyro[3], accel[3], sensors;
unsigned char more;
long quat[4];
//陀螺仪方向设置
static signed char gyro_orientation[9] = {1, 0, 0,
                                          0, 1, 0,
                                          0, 0, 1};
/**
  * @brief   获得陀螺仪的初始数据(带符号)
  * @param   gx     陀螺仪x轴的原始数据
	*          gy     陀螺仪y轴的原始数据
	           gz     陀螺仪z轴的原始数据
  * @retval  成功返回 1
	*          失败返回 0 
  */
/* EXT_SYNC_SET | FSYNC Bit Location
 * -------------+-------------------
 * 每个数据为2个字节
 * 0            | Input disabled
 * 1            | TEMP_OUT_L[0]
 * 2            | GYRO_XOUT_L[0]
 * 3            | GYRO_YOUT_L[0]     
 * 4            | GYRO_ZOUT_L[0]
 * 5            | ACCEL_XOUT_L[0]
 * 6            | ACCEL_YOUT_L[0]
 * 7            | ACCEL_ZOUT_L[0]
 */
uint8_t MPU_Get_Gyroscope(short *gx, short *gy, short *gz)
{
  uint8_t buf[6]; /* 接收缓冲区*/
  uint8_t state;  /* 读取状态 */
  state = IICDevice_ReadBytes(MPU_ADDR, MPU_GYRO_XOUTH_REG, 6, buf);
  if (state == true) /*读取成功*/
  {
    *gx = (((u16)buf[0] << 8) | buf[1]) / GYRO_PRE; /* 原始数据 / 量程*/
    *gy = (((u16)buf[2] << 8) | buf[3]) / GYRO_PRE; /* 姿态解算数据*/
    *gz = (((u16)buf[4] << 8) | buf[5]) / GYRO_PRE; /* 根据设定的量程,在头文件里面修改 GYRO_PRE陀螺仪量程*/
  }
  return state; /* 返回读取状态*/
}

/**
  * @brief   获得加速度的初始数据
  * @param   ax     加速度x轴的原始数据
	*          ay     加速度y轴的原始数据
	           az     加速度z轴的原始数据
  * @retval  成功返回 1
	*          失败返回 0 
*/
uint8_t MPU_Get_Accelerometer(short *ax, short *ay, short *az)
{
  uint8_t buf[6];                                                     /* 接收缓冲区 */
  uint8_t state;                                                      /* 读取状态 */
  state = IICDevice_ReadBytes(MPU_ADDR, MPU_ACCEL_XOUTH_REG, 6, buf); /* 读取ax,ay,az*/
  if (state == true)                                                  /*读取成功*/
  {
    *ax = (((u16)buf[0] << 8) | buf[1]) / ACCEL_PRE; /* 原始数据 / 量程 */
    *ay = (((u16)buf[2] << 8) | buf[3]) / ACCEL_PRE; /* 得到姿态解算数据 */
    *az = (((u16)buf[4] << 8) | buf[5]) / ACCEL_PRE; /* 根据设定的量程,在头文件里面修改 ACCEL_PRE角速度量程*/
  }

  return state; /* 返回读取状态*/
}

/**
  * @brief   读取mpu6050内部温度
  * @param   None
  * @retval  返回读取的放大100倍的温度
*/
short MPU_Get_temprature(void)
{
  uint8_t buf[2];
  short raw;
  float temp;
  IICDevice_ReadBytes(MPU_ADDR, MPU_TEMP_OUTH_REG, 2, buf); /*读取温度*/
  raw = ((u16)buf[0] << 8 | buf[1]);                        /*合并2个字节*/
  temp = 36.53 + ((double)raw / 340);                       /*根据手册进行温度转换*/
  return temp * 100;
}
/**
  * @brief   设置陀螺仪的量程
  * @param   fsr
  * 0 = +/- 250 degrees/sec
  * 1 = +/- 500 degrees/sec
  * 2 = +/- 1000 degrees/sec
  * 3 = +/- 2000 degrees/sec
  * @retval  成功返回 1
	*          失败返回 0 
*/
uint8_t MPU_Set_Gyro_Fsr(uint8_t fsr)
{
  return IICDevice_WriteByte(MPU_ADDR, MPU_GYRO_CFG_REG, fsr << 3);
}

/**
  * @brief   设置加速度的量程
  * @param   fsr
  * 0 = +/- 2g
  * 1 = +/- 4g
  * 2 = +/- 8g
  * 3 = +/- 16g
  * @retval  成功返回 1
	*          失败返回 0 
*/
uint8_t MPU_Set_Accel_Fsr(uint8_t fsr)
{
  return IICDevice_WriteByte(MPU_ADDR, MPU_ACCEL_CFG_REG, fsr << 3);
}
/**
  * @brief   设置mpu6050的低通滤波
  * @param   None
  * @retval  
*/
uint8_t MPU_Set_LPF(u16 lpf)
{
  uint8_t data = 0;
  if (lpf >= 188)
    data = 1;
  else if (lpf >= 98)
    data = 2;
  else if (lpf >= 42)
    data = 3;
  else if (lpf >= 20)
    data = 4;
  else if (lpf >= 10)
    data = 5;
  else
    data = 6;

  return IICDevice_WriteByte(MPU_ADDR, MPU_CFG_REG, data); //设置数字低通滤波器
}
/**
  * @brief   设置mpu6050的采样率
  * @param   rate 4~1000hz 
  * @retval  
*/
uint8_t MPU_Set_Rate(u16 rate)
{
  uint8_t data;
  if (rate > 1000)
    rate = 1000;
  if (rate < 4)
    rate = 4;
  data = 10000 / (rate - 1);
  data = IICDevice_WriteByte(MPU_ADDR, MPU_SAMPLE_RATE_REG, data);
  return MPU_Set_LPF(rate / 2);
}
/**
  * @brief   mpu6050初始化
  * @param   None
  * @retval  None  
*/
uint8_t MPU_Init(void)
{
  uint8_t state;
  IIC_Init();
  IICDevice_WriteByte(MPU_ADDR, MPU_PWR_MGMT1_REG, 0x80); //复位mpu6050
  delay_ms(100);
  IICDevice_WriteByte(MPU_ADDR, MPU_PWR_MGMT1_REG, 0x00); //唤醒mpu6050
  state = IICDevice_ReadByte(MPU_ADDR, MPU_DEVICE_ID_REG);
  printf("state = %X\r\n", state);
  while (state != 0x68) /* 检测mpu6050链接 */
  {
    printf("MPU6050error\r\n"); /* 等待mpu6050链接*/
    return false;               /*未检测到MPU6056 退出*/
  }
  printf("MPU6050 OK....\r\n");                           /* 检测到mpu6050*/
  MPU_Set_Gyro_Fsr(3);                                    //陀螺仪传感器,±2000dps
  MPU_Set_Accel_Fsr(0);                                   //设置加速度，±2g
  MPU_Set_Rate(50);                                       //设置采样频率为50
  IICDevice_WriteByte(MPU_ADDR, MPU_INT_EN_REG,    0x00);  //关闭所有的中断
  IICDevice_WriteByte(MPU_ADDR, MPU_USER_CTRL_REG, 0x00);  //主IIC模式关闭
  IICDevice_WriteByte(MPU_ADDR, MPU_FIFO_EN_REG,   0x00);  //关闭FIFO
  IICDevice_WriteByte(MPU_ADDR, MPU_INTBP_CFG_REG, 0x80);  //INF引脚低电平有效
  //IICDevice_WriteByte(MPU_ADDR, MPU_INTBP_CFG_REG, 0x02);//开启旁路模式,hm388l连接的主IIC上 仅限集成陀螺仪和hm388l,如果单纯使用陀螺仪可以屏蔽此代码
  IICDevice_WriteByte(MPU_ADDR, MPU_PWR_MGMT1_REG, 0x01);  //设置CLKSEL，PLL，X轴为参考
  IICDevice_WriteByte(MPU_ADDR, MPU_PWR_MGMT2_REG, 0x00);  //加速度与陀螺仪都工作
  return true;                                             /* mpu6050初始化成功*/
}

/**
  * @brief  空函数,未用到
  * @param  无
  * @retval 无
  */
void mget_ms(unsigned long *time)
{
}
//方向转换
unsigned short inv_row_2_scale(const signed char *row)
{
  unsigned short b;

  if (row[0] > 0)
    b = 0;
  else if (row[0] < 0)
    b = 4;
  else if (row[1] > 0)
    b = 1;
  else if (row[1] < 0)
    b = 5;
  else if (row[2] > 0)
    b = 2;
  else if (row[2] < 0)
    b = 6;
  else
    b = 7; // error
  return b;
}

//陀螺仪方向控制
unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
  unsigned short scalar;

  scalar = inv_row_2_scale(mtx);
  scalar |= inv_row_2_scale(mtx + 3) << 3;
  scalar |= inv_row_2_scale(mtx + 6) << 6;

  return scalar;
}

//MPU6050自检
u8 run_self_test(void)
{
  int result;
  long gyro[3], accel[3];
  result = mpu_run_self_test(gyro, accel);
  if (result == 0x7)
  {
    float sens;
    unsigned short accel_sens;
    mpu_get_gyro_sens(&sens);
    gyro[0] = (long)(gyro[0] * sens);
    gyro[1] = (long)(gyro[1] * sens);
    gyro[2] = (long)(gyro[2] * sens);
    dmp_set_gyro_bias(gyro);
    mpu_get_accel_sens(&accel_sens);
    accel[0] *= accel_sens;
    accel[1] *= accel_sens;
    accel[2] *= accel_sens;
    dmp_set_accel_bias(accel);
    return 0;
  }
  else
    return 1;
}

/**
  * @brief  DPM初始化：当采用MPU6050的DMP做解算时用本函数初始化MPU6050
  * @param  无
  * @retval 无
  */
void MPU6050_DMP_Init(void)
{
  delay_ms(100);

  if (MPU_Init()) //初始化MPU6050
  {
    /* 设置所需要的传感器 */
    if (!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
      printf("mpu_set_sensor complete ......\r\n");

    /* 设置FIFO */
    if (!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))
      printf("mpu_configure_fifo complete ......\r\n");

    /* 设置采样率 */
    if (!mpu_set_sample_rate(DEFAULT_MPU_HZ))
      printf("mpu_set_sample_rate complete ......\r\n");

    /* 加载dmp固件 */
    if (!dmp_load_motion_driver_firmware())
      printf("dmp_load_motion_driver_firmware complete ......\r\n");

    /* 设置陀螺仪方向 */
    if (!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))
      printf("dmp_set_orientation complete ......\r\n");

    /* 设置dmp功能 */
    if (!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP | DMP_FEATURE_ANDROID_ORIENT |
                            DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL))
      printf("dmp_enable_feature complete ......\r\n");

    /* 设置DMP输出速率 */
    if (!dmp_set_fifo_rate(DEFAULT_MPU_HZ))
      printf("dmp_set_fifo_rate complete ......\r\n");

//    /* 自检 */
//    if (!run_self_test())
//      printf("run_self_test complete ......\r\n");

    /* 使能DMP */
    if (!mpu_set_dmp_state(1))
      printf("mpu_set_dmp_state complete ......\r\n");
  }
}
void MPU6050_DMP_EulerianAngle(float *pitch, float *roll, float *yaw)
{
  dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors, &more);

  if (sensors & INV_WXYZ_QUAT)
  {
    q0 = quat[0] / q30; //q30格式转换为浮点数
    q1 = quat[1] / q30;
    q2 = quat[2] / q30;
    q3 = quat[3] / q30;

    //计算得到俯仰角/横滚角/航向角
    *pitch = asin(-2 * q1 * q3 + 2 * q0 * q2) * 57.3;                                    // pitch
    *roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 57.3;     // roll
    *yaw = atan2(2 * (q1 * q2 + q0 * q3), q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3) * 57.3; //yaw
  }
}
