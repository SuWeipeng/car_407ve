#ifndef __AP_MOTORS_H__
#define __AP_MOTORS_H__

#include <stm32f4xx_hal.h>

#define MOTORS_PWM_MIN         50
#define ENCODER_CNT_MAX        65535
#define MOTORS_ENCODER_LINE    30.0f
#define MOTORS_MAX_RPM         70.0f
#define MOTORS_REDUCTION_RATIO 48.0f
#define ENCODER_DELTA_MAX      300.0f
#define MOTORS_VCP_DEBUG       1

class AC_PID;

class AP_Motors
{
public:
  AP_Motors(TIM_HandleTypeDef* enc_tim,  // encoder timer
            int8_t             enc_dir,  // encoder direction
            GPIO_TypeDef*      dir_port, // L298N GPIO port
            uint16_t           pin_1,    // L298N in1
            uint16_t           pin_2,    // L298N in2
            TIM_HandleTypeDef* pwm_tim,  // pwm timer
            uint8_t            channel,  // pwm channel
            uint16_t           pwm_max,
            AC_PID*            pid);
  ~AP_Motors(){}
  
  void set_rpm(float rpm);
  
private:
  /* encoder */
  TIM_HandleTypeDef* _enc_tim;
  int8_t             _enc_dir;
  int32_t            _tick;
  int32_t            _tick_last;
  uint32_t           _last_millisecond;
  float              _rpm;
  float              _rpm_last;
  
  /* L298N */
  TIM_HandleTypeDef* _pwm_tim;
  uint8_t            _channel;
  uint16_t           _pwm_max;
  GPIO_TypeDef*      _dir_port;
  uint16_t           _pin_1;
  uint16_t           _pin_2;
  
  /* pid control */
  AC_PID*            _pid;
  
  void     _spin(int16_t pwm);
  float    _read_rpm();
  int16_t  _get_delta_tick();
};
#endif /* __AP_MOTORS_H__ */
