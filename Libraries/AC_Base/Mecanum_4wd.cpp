#include <vectorN.h>
#include "Mecanum_4wd.h"
#include "usb_device.h"

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
}

void Mecanum_4wd::stop()
{
  _motor1_fr.set_rpm(0);
  _motor2_fl.set_rpm(0);
  _motor3_bl.set_rpm(0);
  _motor4_br.set_rpm(0);
}
