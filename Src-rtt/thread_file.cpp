#if defined(USE_RTTHREAD)
#include <entry.h>
#include "fatfs.h"
#include "AP_Buffer.h"
#include "AC_Base.h"

#define LOG_FILE_NAME "log.bin"

FATFS fs;
FATFS *pfs;
FIL fil;
DWORD fre_clust;
uint32_t totalSpace, freeSpace;
FRESULT fres;
UINT br, bw;

extern Mecanum_4wd *base;
extern AP_Buffer *buffer;

rt_thread_t file_thread = RT_NULL;

void file_log_entry (void* parameter);

extern "C"
int file_start(void)
{
  FRESULT res;
 
  if(f_mount(&fs, "", 0) != FR_OK){
    rt_kputs("f_mount error in file_start() \r\n");
    return 1;
  }

  res = f_open(&fil, LOG_FILE_NAME, FA_CREATE_NEW | FA_WRITE); 
  if(res == FR_OK){
    rt_kputs("f_open error in file_start() \r\n");
    f_close(&fil);
  } else if(res == FR_EXIST){
    f_unlink(LOG_FILE_NAME);
  }
  if(f_mount(NULL, "", 1) != FR_OK){
    rt_kputs("unmount error in file_start() \r\n");
    return 2;
  }
  
  RTT_CREATE(file,file_log_entry,RT_NULL,1024,1,20);
  return 0;
}

void file_log_entry (void* parameter){
#if defined ( __GNUC__ )
  return;
#endif
  uint16_t read_size;
  while(1){
    base->take_sem();
    rt_enter_critical();
    /* Mount SD Card */
    if(f_mount(&fs, "", 0) != FR_OK){
      rt_kputs("f_mount error\r\n");
      return;
    }
    
    /* Open file to write */
    if(f_open(&fil, LOG_FILE_NAME, FA_OPEN_APPEND | FA_WRITE) != FR_OK){
      rt_kputs("f_open error\r\n");
    }
    
    /* Check freeSpace space */
    if(f_getfree("", &fre_clust, &pfs) != FR_OK){
      rt_kputs("f_getfree error\r\n");    
      return;
    }
    
    totalSpace = (uint32_t)((pfs->n_fatent - 2) * pfs->csize * 0.5);
    freeSpace = (uint32_t)(fre_clust * pfs->csize * 0.5);
    
    /* free space is less than 1kb */
    if(freeSpace < 1){
      rt_kputs("freeSpace error\r\n");    
      return;
    }
    
    /* Writing*/
    read_size = buffer->read();
    if(read_size>0){
      f_write (&fil, buffer->read_buf_addr(), read_size, &bw);
    }
    
    /* Close file */
    if(f_close(&fil) != FR_OK){
      rt_kputs("f_close error\r\n");    
      return;
    }
    
    /* Unmount SDCARD */
    if(f_mount(NULL, "", 1) != FR_OK){
      rt_kputs("unmount error\r\n");   
      return;
    }
    
    rt_exit_critical();
    
    rt_thread_delay(1);
  }
}

#endif