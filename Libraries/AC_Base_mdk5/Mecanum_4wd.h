#ifndef __MECANUM_4WD_H__
#define __MECANUM_4WD_H__

#include <stm32f4xx_hal.h>
#include <AP_Motors.h>
#include <AC_PID.h>

#if defined(USE_RTTHREAD)
#include "Semaphore.h"
using namespace rtthread;
#endif

#define BASE_TYPE           1 // 0-Small, 1-Middle
#if BASE_TYPE == 0
#define HALF_BASE_LENGTH_M  0.075f
#define HALF_BASE_WIDTH_M   0.070f
#define P                   1.2f
#define I                   5.0f
#define D                   0.3f
#define FF                  0.1f
#define IMAX                200.0f
#define FLTT                1.0f
#define FLTE                1.0f
#define FLTD                0.85f
#define DT                  0.02f
#elif BASE_TYPE == 1
#define HALF_BASE_LENGTH_M  0.122f
#define HALF_BASE_WIDTH_M   0.120f
#define P                   0.5f
#define I                   2.5f
#define D                   0.0f
#define FF                  0.0f
#define IMAX                200.0f
#define FLTT                1.0f
#define FLTE                1.0f
#define FLTD                0.85f
#define DT                  0.02f
#endif

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
  
#if defined(USE_RTTHREAD)
  void log_write_base();
#endif

private:
  AP_Motors _motor1_fr;
  AP_Motors _motor2_fl;
  AP_Motors _motor3_bl;
  AP_Motors _motor4_br;
  AC_PID    _pid_1;
  AC_PID    _pid_2;
  AC_PID    _pid_3;
  AC_PID    _pid_4;
  
  float     _motor1_fr_rpm, _motor2_fl_rpm, _motor3_bl_rpm, _motor4_br_rpm;
  
#if defined(USE_RTTHREAD)
  Semaphore _log_sem;
#endif
};
#endif /*__MECANUM_4WD_H__*/
