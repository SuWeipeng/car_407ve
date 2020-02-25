#ifndef __AP_BUFFER_BACKEND_H__
#define __AP_BUFFER_BACKEND_H__

#include "AP_Buffer.h"

class AP_Buffer_Backend{
public:
  AP_Buffer_Backend(AP_Buffer &instance);
  ~AP_Buffer_Backend(){};
  
  virtual void       write(const void *pBuffer, uint16_t size) = 0;
  virtual uint16_t   read(void) = 0;
  virtual void*      read_buf_addr(void) = 0;
  
protected:
  AP_Buffer &_frontend;
};

#endif /* __AP_BUFFER_BACKEND_H__ */
