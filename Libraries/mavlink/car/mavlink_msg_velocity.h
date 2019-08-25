#pragma once
// MESSAGE VELOCITY PACKING

#define MAVLINK_MSG_ID_VELOCITY 2

MAVPACKED(
typedef struct __mavlink_velocity_t {
 float vel_x; /*<  m/s*/
 float vel_y; /*<  m/s*/
 float rad_z; /*<  rad/s*/
}) mavlink_velocity_t;

#define MAVLINK_MSG_ID_VELOCITY_LEN 12
#define MAVLINK_MSG_ID_VELOCITY_MIN_LEN 12
#define MAVLINK_MSG_ID_2_LEN 12
#define MAVLINK_MSG_ID_2_MIN_LEN 12

#define MAVLINK_MSG_ID_VELOCITY_CRC 54
#define MAVLINK_MSG_ID_2_CRC 54



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_VELOCITY { \
    2, \
    "VELOCITY", \
    3, \
    {  { "vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_velocity_t, vel_x) }, \
         { "vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_velocity_t, vel_y) }, \
         { "rad_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_velocity_t, rad_z) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_VELOCITY { \
    "VELOCITY", \
    3, \
    {  { "vel_x", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_velocity_t, vel_x) }, \
         { "vel_y", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_velocity_t, vel_y) }, \
         { "rad_z", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_velocity_t, rad_z) }, \
         } \
}
#endif

/**
 * @brief Pack a velocity message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param vel_x  m/s
 * @param vel_y  m/s
 * @param rad_z  rad/s
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_velocity_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float vel_x, float vel_y, float rad_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VELOCITY_LEN];
    _mav_put_float(buf, 0, vel_x);
    _mav_put_float(buf, 4, vel_y);
    _mav_put_float(buf, 8, rad_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VELOCITY_LEN);
#else
    mavlink_velocity_t packet;
    packet.vel_x = vel_x;
    packet.vel_y = vel_y;
    packet.rad_z = rad_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VELOCITY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VELOCITY;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_VELOCITY_MIN_LEN, MAVLINK_MSG_ID_VELOCITY_LEN, MAVLINK_MSG_ID_VELOCITY_CRC);
}

/**
 * @brief Pack a velocity message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param vel_x  m/s
 * @param vel_y  m/s
 * @param rad_z  rad/s
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_velocity_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float vel_x,float vel_y,float rad_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VELOCITY_LEN];
    _mav_put_float(buf, 0, vel_x);
    _mav_put_float(buf, 4, vel_y);
    _mav_put_float(buf, 8, rad_z);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VELOCITY_LEN);
#else
    mavlink_velocity_t packet;
    packet.vel_x = vel_x;
    packet.vel_y = vel_y;
    packet.rad_z = rad_z;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VELOCITY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VELOCITY;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_VELOCITY_MIN_LEN, MAVLINK_MSG_ID_VELOCITY_LEN, MAVLINK_MSG_ID_VELOCITY_CRC);
}

/**
 * @brief Encode a velocity struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param velocity C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_velocity_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_velocity_t* velocity)
{
    return mavlink_msg_velocity_pack(system_id, component_id, msg, velocity->vel_x, velocity->vel_y, velocity->rad_z);
}

/**
 * @brief Encode a velocity struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param velocity C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_velocity_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_velocity_t* velocity)
{
    return mavlink_msg_velocity_pack_chan(system_id, component_id, chan, msg, velocity->vel_x, velocity->vel_y, velocity->rad_z);
}

/**
 * @brief Send a velocity message
 * @param chan MAVLink channel to send the message
 *
 * @param vel_x  m/s
 * @param vel_y  m/s
 * @param rad_z  rad/s
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_velocity_send(mavlink_channel_t chan, float vel_x, float vel_y, float rad_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VELOCITY_LEN];
    _mav_put_float(buf, 0, vel_x);
    _mav_put_float(buf, 4, vel_y);
    _mav_put_float(buf, 8, rad_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VELOCITY, buf, MAVLINK_MSG_ID_VELOCITY_MIN_LEN, MAVLINK_MSG_ID_VELOCITY_LEN, MAVLINK_MSG_ID_VELOCITY_CRC);
#else
    mavlink_velocity_t packet;
    packet.vel_x = vel_x;
    packet.vel_y = vel_y;
    packet.rad_z = rad_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VELOCITY, (const char *)&packet, MAVLINK_MSG_ID_VELOCITY_MIN_LEN, MAVLINK_MSG_ID_VELOCITY_LEN, MAVLINK_MSG_ID_VELOCITY_CRC);
#endif
}

/**
 * @brief Send a velocity message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_velocity_send_struct(mavlink_channel_t chan, const mavlink_velocity_t* velocity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_velocity_send(chan, velocity->vel_x, velocity->vel_y, velocity->rad_z);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VELOCITY, (const char *)velocity, MAVLINK_MSG_ID_VELOCITY_MIN_LEN, MAVLINK_MSG_ID_VELOCITY_LEN, MAVLINK_MSG_ID_VELOCITY_CRC);
#endif
}

#if MAVLINK_MSG_ID_VELOCITY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_velocity_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float vel_x, float vel_y, float rad_z)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, vel_x);
    _mav_put_float(buf, 4, vel_y);
    _mav_put_float(buf, 8, rad_z);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VELOCITY, buf, MAVLINK_MSG_ID_VELOCITY_MIN_LEN, MAVLINK_MSG_ID_VELOCITY_LEN, MAVLINK_MSG_ID_VELOCITY_CRC);
#else
    mavlink_velocity_t *packet = (mavlink_velocity_t *)msgbuf;
    packet->vel_x = vel_x;
    packet->vel_y = vel_y;
    packet->rad_z = rad_z;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VELOCITY, (const char *)packet, MAVLINK_MSG_ID_VELOCITY_MIN_LEN, MAVLINK_MSG_ID_VELOCITY_LEN, MAVLINK_MSG_ID_VELOCITY_CRC);
#endif
}
#endif

#endif

// MESSAGE VELOCITY UNPACKING


/**
 * @brief Get field vel_x from velocity message
 *
 * @return  m/s
 */
static inline float mavlink_msg_velocity_get_vel_x(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field vel_y from velocity message
 *
 * @return  m/s
 */
static inline float mavlink_msg_velocity_get_vel_y(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field rad_z from velocity message
 *
 * @return  rad/s
 */
static inline float mavlink_msg_velocity_get_rad_z(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a velocity message into a struct
 *
 * @param msg The message to decode
 * @param velocity C-struct to decode the message contents into
 */
static inline void mavlink_msg_velocity_decode(const mavlink_message_t* msg, mavlink_velocity_t* velocity)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    velocity->vel_x = mavlink_msg_velocity_get_vel_x(msg);
    velocity->vel_y = mavlink_msg_velocity_get_vel_y(msg);
    velocity->rad_z = mavlink_msg_velocity_get_rad_z(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_VELOCITY_LEN? msg->len : MAVLINK_MSG_ID_VELOCITY_LEN;
        memset(velocity, 0, MAVLINK_MSG_ID_VELOCITY_LEN);
    memcpy(velocity, _MAV_PAYLOAD(msg), len);
#endif
}
