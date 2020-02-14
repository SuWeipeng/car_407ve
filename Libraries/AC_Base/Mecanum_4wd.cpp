#include <vectorN.h>
#include "Mecanum_4wd.h"
#include "usb_device.h"
#include "Logger.h"
#if PWM_RPM_TEST_ENABLE == 1
#include <stm32f4xx_hal.h>
#include "mavlink.h"

extern UART_HandleTypeDef huart1;
#endif

typedef VectorN<float,3> Vector3f;

static float r1[3] = { 1,  1,  (HALF_BASE_LENGTH_M+HALF_BASE_WIDTH_M)};
static float r2[3] = { 1, -1, -(HALF_BASE_LENGTH_M+HALF_BASE_WIDTH_M)};
static float r3[3] = { 1,  1, -(HALF_BASE_LENGTH_M+HALF_BASE_WIDTH_M)};
static float r4[3] = { 1, -1,  (HALF_BASE_LENGTH_M+HALF_BASE_WIDTH_M)};

static Vector3f _r1(r1),_r2(r2),_r3(r3),_r4(r4);

Mecanum_4wd::Mecanum_4wd()
: _motor1_fr_rpm(0)
, _motor2_fl_rpm(0)
, _motor3_bl_rpm(0)
, _motor4_br_rpm(0)
#if defined(USE_RTTHREAD)
, _log_sem("log",0)
#endif
{}

Mecanum_4wd::~Mecanum_4wd()
{}

void Mecanum_4wd::vel2rpm(float& vel_x, float& vel_y, float& rad_z)
{
  double scale = 1;
  float  vel[3] = {vel_x * 60, vel_y * 60, rad_z * 60}; // m/s -> m/min, rad/s -> rad/min
  Vector3f _vel(vel);
  
  /* check rpm max  */
  while(1)
  {
    _motor1_fr_rpm = (_r1 * _vel) / WHEEL_RADIUS_M;
    _motor2_fl_rpm = (_r2 * _vel) / WHEEL_RADIUS_M;
    _motor3_bl_rpm = (_r3 * _vel) / WHEEL_RADIUS_M;
    _motor4_br_rpm = (_r4 * _vel) / WHEEL_RADIUS_M;
    if(fabsf(_motor1_fr_rpm) <= MOTORS_MAX_RPM 
    && fabsf(_motor2_fl_rpm) <= MOTORS_MAX_RPM
    && fabsf(_motor3_bl_rpm) <= MOTORS_MAX_RPM
    && fabsf(_motor4_br_rpm) <= MOTORS_MAX_RPM)
    {
      break;
    }
    scale -= 0.0333334;
    _vel  *= scale;
  }
  
  run();
}

void Mecanum_4wd::run()
{
  _motor1_fr.set_rpm(_motor1_fr_rpm);
  _motor2_fl.set_rpm(_motor2_fl_rpm);
  _motor3_bl.set_rpm(_motor3_bl_rpm);
  _motor4_br.set_rpm(_motor4_br_rpm);
#if defined(USE_RTTHREAD)
  _log_sem.release();
#endif
#if PWM_RPM_TEST_ENABLE == 1
  _pwm_rpm_test();
#endif
}

void Mecanum_4wd::stop()
{
  _motor1_fr.set_rpm(0);
  _motor2_fl.set_rpm(0);
  _motor3_bl.set_rpm(0);
  _motor4_br.set_rpm(0);
}

#if defined(USE_RTTHREAD)
void Mecanum_4wd::log_write_base()
{
  _log_sem.wait(RT_WAITING_FOREVER);

  rt_enter_critical();
  
  Write_PID(LOG_PIDW1_MSG, &_motor1_fr.get_pid()->get_pid_info());
  Write_PID(LOG_PIDW2_MSG, &_motor2_fl.get_pid()->get_pid_info());
  Write_PID(LOG_PIDW3_MSG, &_motor3_bl.get_pid()->get_pid_info());
  Write_PID(LOG_PIDW4_MSG, &_motor4_br.get_pid()->get_pid_info());
  
  Write_Encoder(LOG_ENC1_MSG, _motor1_fr.get_delta_tick(), _motor1_fr.get_tick(), _motor1_fr.get_delta_min(), _motor1_fr.get_delta_ms());
  Write_Encoder(LOG_ENC2_MSG, _motor2_fl.get_delta_tick(), _motor2_fl.get_tick(), _motor2_fl.get_delta_min(), _motor2_fl.get_delta_ms());
  Write_Encoder(LOG_ENC3_MSG, _motor3_bl.get_delta_tick(), _motor3_bl.get_tick(), _motor3_bl.get_delta_min(), _motor3_bl.get_delta_ms());
  Write_Encoder(LOG_ENC4_MSG, _motor4_br.get_delta_tick(), _motor4_br.get_tick(), _motor4_br.get_delta_min(), _motor4_br.get_delta_ms());
  
  Write_PWM(_motor1_fr.get_pwm(), _motor2_fl.get_pwm(), _motor3_bl.get_pwm(), _motor4_br.get_pwm());

  rt_exit_critical();
}
#endif

#if PWM_RPM_TEST_ENABLE == 1
void Mecanum_4wd::_pwm_rpm_test()
{
  mavlink_message_t msg;
  int len = 0;
  uint8_t myTxData[32];
  
  mavlink_msg_pwm_rpm_pack(0, 0, &msg, _motor1_fr.get_pwm(), _motor1_fr.get_rpm());
  len = mavlink_msg_to_send_buffer( myTxData, &msg );
  HAL_UART_Transmit(&huart1,myTxData,len,10);
}
#endif
