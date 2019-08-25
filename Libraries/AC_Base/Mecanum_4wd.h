#ifndef __MECANUM_4WD_H__
#define __MECANUM_4WD_H__

#include <stm32f4xx_hal.h>
#include <AP_Motors.h>
#include <AC_PID.h>

#define HALF_BASE_LENGTH_M  0.075f
#define HALF_BASE_WIDTH_M   0.070f
#define WHEEL_DIAMETER_M    0.096f   
#define WHEEL_RADIUS_M      (WHEEL_DIAMETER_M / 2.0f)
#define MECANUM_VCP_DEBUG   0

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim8;

class Mecanum_4wd
{
public:
  Mecanum_4wd();
  ~Mecanum_4wd();
  
  void run();
  void stop();
  void vel2rpm(float& vel_x, float& vel_y, float& rad_z);

private:
  AP_Motors _motor1_fr{&htim3, 1, GPIOC, GPIO_PIN_1, GPIO_PIN_3, &htim5, TIM_CHANNEL_4, 99, &_pid_1};
  AP_Motors _motor2_fl{&htim1, 1, GPIOE, GPIO_PIN_2, GPIO_PIN_4, &htim5, TIM_CHANNEL_1, 99, &_pid_2};
  AP_Motors _motor3_bl{&htim4, 1, GPIOE, GPIO_PIN_3, GPIO_PIN_5, &htim5, TIM_CHANNEL_2, 99, &_pid_3};
  AP_Motors _motor4_br{&htim8, 1, GPIOC, GPIO_PIN_0, GPIO_PIN_2, &htim5, TIM_CHANNEL_3, 99, &_pid_4};
  AC_PID    _pid_1{1.2f, 1.2f, 0.0f, 0.0f, 95.0f, 1.0f, 1.0f, 0.85f, 0.02f};
  AC_PID    _pid_2{1.2f, 1.2f, 0.0f, 0.0f, 95.0f, 1.0f, 1.0f, 0.85f, 0.02f};
  AC_PID    _pid_3{1.2f, 1.2f, 0.0f, 0.0f, 95.0f, 1.0f, 1.0f, 0.85f, 0.02f};
  AC_PID    _pid_4{1.2f, 1.2f, 0.0f, 0.0f, 95.0f, 1.0f, 1.0f, 0.85f, 0.02f};
  
  float     _motor1_fr_rpm, _motor2_fl_rpm, _motor3_bl_rpm, _motor4_br_rpm;
};
#endif /*__MECANUM_4WD_H__*/
