#if defined(USE_RTTHREAD)
#include <entry.h>

rt_thread_t mav_thread = RT_NULL;

void update_mavlink(void* parameter);

int mavlink_start(void)
{
  RTT_CREATE(mav,update_mavlink,RT_NULL,2048,6,20);
}

#endif
