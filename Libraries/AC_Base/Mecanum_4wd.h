#ifndef __MECANUM_4WD_H__
#define __MECANUM_4WD_H__

#include <stm32f4xx_hal.h>
#include <AP_Motors.h>
#include <AC_PID.h>

#if defined(USE_RTTHREAD)
#include "Semaphore.h"
using namespace rtthread;
#endif

#define BASE_TYPE           1 // 0-Small, 1-Middle, 2-Test
#if BASE_TYPE == 0
#define HALF_BASE_LENGTH_M  0.075f
#define HALF_BASE_WIDTH_M   0.080f
#define P                   0.5f
#define I                   2.5f
#define D                   0.0f
#define FF                  0.0f
#define IMAX                200.0f
#define FLTT                0.0f
#define FLTE                0.0f
#define FLTD                0.85f
#define DT                  0.02f
#elif BASE_TYPE == 1
#define HALF_BASE_LENGTH_M  0.122f
#define HALF_BASE_WIDTH_M   0.120f
#define P                   0.75f
#define I                   3.5f
#define D                   0.0f
#define FF                  0.0f
#define IMAX                200.0f
#define FLTT                0.0f
#define FLTE                20.0f
#define FLTD                0.85f
#define DT                  0.02f
#elif BASE_TYPE == 2
#define HALF_BASE_LENGTH_M  0.122f
#define HALF_BASE_WIDTH_M   0.120f
#define P                   0.3f
#define I                   5.0f
#define D                   0.0f
#define FF                  0.0f
#define IMAX                200.0f
#define FLTT                0.0f
#define FLTE                0.0f
#define FLTD                0.85f
#define DT                  0.02f
#endif

#define WHEEL_DIAMETER_M    0.096f   
#define WHEEL_RADIUS_M      (WHEEL_DIAMETER_M / 2.0f)
#define MECANUM_VCP_DEBUG   0
#define PWM_RPM_TEST_ENABLE 0

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
  void take_sem(void) { _file_sem.wait(RT_WAITING_FOREVER); }
#endif

private:
  AP_Motors _motor1_fr{&htim3, 1, GPIOC, GPIO_PIN_1, GPIO_PIN_3, &htim5, TIM_CHANNEL_4, 99, &_pid_1};
  AP_Motors _motor2_fl{&htim1, 1, GPIOE, GPIO_PIN_2, GPIO_PIN_4, &htim5, TIM_CHANNEL_1, 99, &_pid_2};
  AP_Motors _motor3_bl{&htim4, 1, GPIOE, GPIO_PIN_3, GPIO_PIN_5, &htim5, TIM_CHANNEL_2, 99, &_pid_3};
  AP_Motors _motor4_br{&htim8, 1, GPIOC, GPIO_PIN_0, GPIO_PIN_2, &htim5, TIM_CHANNEL_3, 99, &_pid_4};
  AC_PID    _pid_1{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  AC_PID    _pid_2{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  AC_PID    _pid_3{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  AC_PID    _pid_4{P, I, D, FF, IMAX, FLTT, FLTE, FLTD, DT};
  
  float     _motor1_fr_rpm, _motor2_fl_rpm, _motor3_bl_rpm, _motor4_br_rpm;
  
#if defined(USE_RTTHREAD)
  Semaphore _log_sem;
  Semaphore _file_sem;
#endif
 
#if PWM_RPM_TEST_ENABLE == 1
private:
  void      _pwm_rpm_test();
#endif
};
#endif /*__MECANUM_4WD_H__*/
