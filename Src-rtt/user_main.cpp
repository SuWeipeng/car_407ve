#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <stdlib.h>
#include "nrf_mavlink.h"
#include "AC_Base.h"
#include "Logger.h"
#include "AP_Buffer.h"

#if BASE_TYPE == 0
#define DELAY_MS 50
#elif BASE_TYPE == 1
#define DELAY_MS 50
#elif BASE_TYPE == 2
#define DELAY_MS 30
#endif

using namespace rtthread;

extern vel_target vel;

Mecanum_4wd *base;
AP_Buffer *buffer;

extern "C" {
void setup(void)
{
  base = new Mecanum_4wd();
  buffer = new AP_Buffer();
  buffer->init(AP_Buffer::RING);
  Log_Init();
}

void loop(void* parameter)
{
  while(1)
  {
    float vel_x = vel.vel_x;  // x max 0.104f
    float vel_y = vel.vel_y;  // y max 0.104f
    float rad_z = vel.rad_z;  // z max 0.7f

    base->vel2rpm(vel_x, vel_y, rad_z);
    rt_thread_delay(DELAY_MS);
  }
}

} // extern "C"
