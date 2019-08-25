#include "nrf_mavlink.h"
#include "MY_NRF24.h"
#include "usb_device.h"

#define _ABS_(x) (((x)>0) ? x : -x)
#define NRF_VCP_DEBUG 0

ap_t       mav_data;
vel_target vel;

static uint32_t last_timestamp;

void update_mavlink(void)
{
  uint8_t myTxData[32];
  uint8_t AckPayload[32];
  mavlink_message_t msg;
  uint32_t timestamp = HAL_GetTick();

  mav_data.mode = 0;
  mavlink_msg_simple_pack(0,0,&msg,mav_data.value);
  int len = mavlink_msg_to_send_buffer(myTxData, &msg);
  
  if(_ABS_(timestamp - last_timestamp) > 1000){
    memset(&vel, 0, sizeof(vel_target));
    mav_data.com = 1;
  } else {
    mav_data.com = 0;
  }
          
  if(NRF24_write(myTxData, len)) {
    NRF24_read(AckPayload, 32);
    uint8_t i;
    mavlink_message_t msg_receive;
    mavlink_status_t mav_status;
    for(i=0; i<32; i++) {
      if(mavlink_parse_char(0, AckPayload[i], &msg_receive, &mav_status)) {
        
        last_timestamp = timestamp;
          
        switch (msg_receive.msgid) {
        case MAVLINK_MSG_ID_VELOCITY: {
          mavlink_velocity_t packet;
          mavlink_msg_velocity_decode(&msg_receive, &packet);

          vel.vel_x = packet.vel_x;
          vel.vel_y = packet.vel_y;
          vel.rad_z = packet.rad_z;
          
#if NRF_VCP_DEBUG
          char TxBuf[32];
          sprintf(TxBuf, "vel_x:%.2f, vel_y:%.2f, rad_z:%.2f\r\n", vel.vel_x, vel.vel_y, vel.rad_z);
          VCPSend((uint8_t *)TxBuf, strlen(TxBuf));
#endif
          break;
        }
        }
      }
    }
  }
}
