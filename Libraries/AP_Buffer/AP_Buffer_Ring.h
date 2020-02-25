#ifndef __AP_BUFFER_RING_H__
#define __AP_BUFFER_RING_H__

#include "AP_Buffer_Backend.h"

class AP_Buffer_Ring : public AP_Buffer_Backend{
public:
  AP_Buffer_Ring(AP_Buffer &instance, void* buffer);
  ~AP_Buffer_Ring(){};
  
  virtual void       write(const void *pBuffer, uint16_t size);
  virtual uint16_t   read(void);
  virtual void*      read_buf_addr(void);
  
private:
  void* _head;
  void* _tail;
  const void* _copy_tail;
};

#endif /* __AP_BUFFER_RING_H__ */
