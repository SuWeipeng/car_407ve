#include "nrf_mavlink.h"
#include "AC_Base.h"
#include "Logger.h"

extern vel_target vel;

Mecanum_4wd *base;

#if (defined(__GNUC__)) && defined(__cplusplus)
extern "C" {
#endif
void setup(void)
{
  base = new Mecanum_4wd();
  for(uint8_t i=0;i<10;i++){
    Write_Test(i,i);
  }
}

void loop(void)
{
  float vel_x = vel.vel_x;  // x max 0.104f
  float vel_y = vel.vel_y;  // y max 0.104f
  float rad_z = vel.rad_z;  // z max 0.7f
  
  base->vel2rpm(vel_x, vel_y, rad_z);
}

#if (defined(__GNUC__)) && defined(__cplusplus)
}
#endif
