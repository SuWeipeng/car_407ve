#include "AC_Base.h"

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
  float x = 0.0f; // max 0.0685f
  float y = 0.0f; // max 0.0685f
  float z = 0.0f; // max 0.82f
  base->vel2rpm(x, y, z);
}

#if (defined(__GNUC__) || defined(__CC_ARM)) && defined(__cplusplus)
}
#endif
