#pragma once
// MESSAGE SIMPLE PACKING

#define MAVLINK_MSG_ID_SIMPLE 0

MAVPACKED(
typedef struct __mavlink_simple_t {
 uint8_t data; /*<  data bit mask*/
}) mavlink_simple_t;

#define MAVLINK_MSG_ID_SIMPLE_LEN 1
#define MAVLINK_MSG_ID_SIMPLE_MIN_LEN 1
#define MAVLINK_MSG_ID_0_LEN 1
#define MAVLINK_MSG_ID_0_MIN_LEN 1

#define MAVLINK_MSG_ID_SIMPLE_CRC 221
#define MAVLINK_MSG_ID_0_CRC 221



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SIMPLE { \
    0, \
    "SIMPLE", \
    1, \
    {  { "data", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_simple_t, data) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SIMPLE { \
    "SIMPLE", \
    1, \
    {  { "data", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_simple_t, data) }, \
         } \
}
#endif

/**
 * @brief Pack a simple message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param data  data bit mask
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simple_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMPLE_LEN];
    _mav_put_uint8_t(buf, 0, data);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMPLE_LEN);
#else
    mavlink_simple_t packet;
    packet.data = data;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMPLE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMPLE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SIMPLE_MIN_LEN, MAVLINK_MSG_ID_SIMPLE_LEN, MAVLINK_MSG_ID_SIMPLE_CRC);
}

/**
 * @brief Pack a simple message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param data  data bit mask
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_simple_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMPLE_LEN];
    _mav_put_uint8_t(buf, 0, data);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SIMPLE_LEN);
#else
    mavlink_simple_t packet;
    packet.data = data;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SIMPLE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SIMPLE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SIMPLE_MIN_LEN, MAVLINK_MSG_ID_SIMPLE_LEN, MAVLINK_MSG_ID_SIMPLE_CRC);
}

/**
 * @brief Encode a simple struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param simple C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simple_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_simple_t* simple)
{
    return mavlink_msg_simple_pack(system_id, component_id, msg, simple->data);
}

/**
 * @brief Encode a simple struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param simple C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_simple_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_simple_t* simple)
{
    return mavlink_msg_simple_pack_chan(system_id, component_id, chan, msg, simple->data);
}

/**
 * @brief Send a simple message
 * @param chan MAVLink channel to send the message
 *
 * @param data  data bit mask
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_simple_send(mavlink_channel_t chan, uint8_t data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SIMPLE_LEN];
    _mav_put_uint8_t(buf, 0, data);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMPLE, buf, MAVLINK_MSG_ID_SIMPLE_MIN_LEN, MAVLINK_MSG_ID_SIMPLE_LEN, MAVLINK_MSG_ID_SIMPLE_CRC);
#else
    mavlink_simple_t packet;
    packet.data = data;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMPLE, (const char *)&packet, MAVLINK_MSG_ID_SIMPLE_MIN_LEN, MAVLINK_MSG_ID_SIMPLE_LEN, MAVLINK_MSG_ID_SIMPLE_CRC);
#endif
}

/**
 * @brief Send a simple message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_simple_send_struct(mavlink_channel_t chan, const mavlink_simple_t* simple)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_simple_send(chan, simple->data);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMPLE, (const char *)simple, MAVLINK_MSG_ID_SIMPLE_MIN_LEN, MAVLINK_MSG_ID_SIMPLE_LEN, MAVLINK_MSG_ID_SIMPLE_CRC);
#endif
}

#if MAVLINK_MSG_ID_SIMPLE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_simple_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, data);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMPLE, buf, MAVLINK_MSG_ID_SIMPLE_MIN_LEN, MAVLINK_MSG_ID_SIMPLE_LEN, MAVLINK_MSG_ID_SIMPLE_CRC);
#else
    mavlink_simple_t *packet = (mavlink_simple_t *)msgbuf;
    packet->data = data;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SIMPLE, (const char *)packet, MAVLINK_MSG_ID_SIMPLE_MIN_LEN, MAVLINK_MSG_ID_SIMPLE_LEN, MAVLINK_MSG_ID_SIMPLE_CRC);
#endif
}
#endif

#endif

// MESSAGE SIMPLE UNPACKING


/**
 * @brief Get field data from simple message
 *
 * @return  data bit mask
 */
static inline uint8_t mavlink_msg_simple_get_data(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a simple message into a struct
 *
 * @param msg The message to decode
 * @param simple C-struct to decode the message contents into
 */
static inline void mavlink_msg_simple_decode(const mavlink_message_t* msg, mavlink_simple_t* simple)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    simple->data = mavlink_msg_simple_get_data(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SIMPLE_LEN? msg->len : MAVLINK_MSG_ID_SIMPLE_LEN;
        memset(simple, 0, MAVLINK_MSG_ID_SIMPLE_LEN);
    memcpy(simple, _MAV_PAYLOAD(msg), len);
#endif
}
