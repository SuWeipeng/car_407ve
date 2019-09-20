#if defined(USE_RTTHREAD)
#include "AC_Base.h"

extern Mecanum_4wd *base;

rt_thread_t log_thread = RT_NULL;

extern "C"
void log_thread_entry(void* parameter)
{
  while(1) {
    base->log_write_base();
    rt_thread_delay(1);
  }
}
#endif
