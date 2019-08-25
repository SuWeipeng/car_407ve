#include "nrf_mavlink.h"
#include "AC_Base.h"

extern vel_target vel;

Mecanum_4wd *base;

#if (defined(__GNUC__) || defined(__CC_ARM)) && defined(__cplusplus)
extern "C" {
#endif
void setup(void)
{
  base = new Mecanum_4wd();
}

void loop(void)
{
  float x = vel.vel_x; // max 0.0685f
  float y = vel.vel_y; // max 0.0685f
  float z = vel.rad_z; // max 0.82f
  base->vel2rpm(x, y, z);
}

#if (defined(__GNUC__) || defined(__CC_ARM)) && defined(__cplusplus)
}
#endif
