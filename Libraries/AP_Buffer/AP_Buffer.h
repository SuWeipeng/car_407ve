#ifndef __AP_BUFFER_H__
#define __AP_BUFFER_H__

#include <stdint.h>

#define AP_BUFFER_MAX_SIZE  (1024 * 10)

class AP_Buffer_Backend;

class AP_Buffer{
  friend class AP_Buffer_Backend;
  friend class AP_Buffer_Ring;
public:
  AP_Buffer();
  ~AP_Buffer(){};
  
  // get singleton
  static AP_Buffer *get_instance(void) {
    return _instance;
  }
  
  // buffer types
  typedef enum {
    RING,
    FIFO
  } buffer_type_t;
  
  void       init(buffer_type_t type);
  void       write(const void *pBuffer, uint16_t size);
  uint16_t   read(void);
  void*      read_buf_addr(void);
  uint16_t   buf_len(void) { return _buf.count; }
  
private:  
  typedef struct Buffer {
    uint8_t*  _buffer;
    uint16_t count;
  } _ap_buffer;  
  
  static AP_Buffer*       _instance;
  AP_Buffer_Backend*      _backend;
  
  _ap_buffer _buf;
};

#endif /* __AP_BUFFER_H__ */
