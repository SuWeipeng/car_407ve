#include <entry.h>
#include "AP_Buffer.h"
#include "AP_Buffer_Ring.h"

using namespace rtthread;

static uint8_t ap_buffer[AP_BUFFER_MAX_SIZE];

AP_Buffer *AP_Buffer::_instance;

AP_Buffer::AP_Buffer()
: _backend(NULL)
{
  _buf._buffer = ap_buffer;
  _buf.count = 0;
  _instance = this;
}

void
AP_Buffer::init(buffer_type_t type)
{
  switch(type){
  case RING:{
    _backend = new AP_Buffer_Ring(*this, _buf._buffer);
    break;
  }
  case FIFO:{
    break;
  }
  }
}

void
AP_Buffer::write(const void *pBuffer, uint16_t size)
{
  if(_backend != NULL){
    _backend -> write(pBuffer, size);
  }
}

uint16_t
AP_Buffer::read(void)
{
  uint16_t ret = 0;
  if(_backend != NULL){
    ret = _backend -> read();
  }
  return ret;
}

void*      
AP_Buffer::read_buf_addr(void)
{
  void* ret = NULL;
  if(_backend != NULL){
    ret = _backend -> read_buf_addr();
  }
  return ret;
}