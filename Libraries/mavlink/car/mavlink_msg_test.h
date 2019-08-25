#pragma once
// MESSAGE TEST PACKING

#define MAVLINK_MSG_ID_TEST 1

MAVPACKED(
typedef struct __mavlink_test_t {
 float data32; /*<  4 byte*/
 uint16_t data16; /*<  2 byte*/
 uint8_t data8; /*<  1 byte*/
}) mavlink_test_t;

#define MAVLINK_MSG_ID_TEST_LEN 7
#define MAVLINK_MSG_ID_TEST_MIN_LEN 7
#define MAVLINK_MSG_ID_1_LEN 7
#define MAVLINK_MSG_ID_1_MIN_LEN 7

#define MAVLINK_MSG_ID_TEST_CRC 42
#define MAVLINK_MSG_ID_1_CRC 42



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TEST { \
    1, \
    "TEST", \
    3, \
    {  { "data8", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_test_t, data8) }, \
         { "data16", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_test_t, data16) }, \
         { "data32", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_test_t, data32) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TEST { \
    "TEST", \
    3, \
    {  { "data8", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_test_t, data8) }, \
         { "data16", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_test_t, data16) }, \
         { "data32", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_test_t, data32) }, \
         } \
}
#endif

/**
 * @brief Pack a test message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param data8  1 byte
 * @param data16  2 byte
 * @param data32  4 byte
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_test_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t data8, uint16_t data16, float data32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TEST_LEN];
    _mav_put_float(buf, 0, data32);
    _mav_put_uint16_t(buf, 4, data16);
    _mav_put_uint8_t(buf, 6, data8);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TEST_LEN);
#else
    mavlink_test_t packet;
    packet.data32 = data32;
    packet.data16 = data16;
    packet.data8 = data8;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TEST;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
}

/**
 * @brief Pack a test message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param data8  1 byte
 * @param data16  2 byte
 * @param data32  4 byte
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_test_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t data8,uint16_t data16,float data32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TEST_LEN];
    _mav_put_float(buf, 0, data32);
    _mav_put_uint16_t(buf, 4, data16);
    _mav_put_uint8_t(buf, 6, data8);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TEST_LEN);
#else
    mavlink_test_t packet;
    packet.data32 = data32;
    packet.data16 = data16;
    packet.data8 = data8;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TEST;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
}

/**
 * @brief Encode a test struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param test C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_test_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_test_t* test)
{
    return mavlink_msg_test_pack(system_id, component_id, msg, test->data8, test->data16, test->data32);
}

/**
 * @brief Encode a test struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param test C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_test_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_test_t* test)
{
    return mavlink_msg_test_pack_chan(system_id, component_id, chan, msg, test->data8, test->data16, test->data32);
}

/**
 * @brief Send a test message
 * @param chan MAVLink channel to send the message
 *
 * @param data8  1 byte
 * @param data16  2 byte
 * @param data32  4 byte
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_test_send(mavlink_channel_t chan, uint8_t data8, uint16_t data16, float data32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TEST_LEN];
    _mav_put_float(buf, 0, data32);
    _mav_put_uint16_t(buf, 4, data16);
    _mav_put_uint8_t(buf, 6, data8);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, buf, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#else
    mavlink_test_t packet;
    packet.data32 = data32;
    packet.data16 = data16;
    packet.data8 = data8;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, (const char *)&packet, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#endif
}

/**
 * @brief Send a test message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_test_send_struct(mavlink_channel_t chan, const mavlink_test_t* test)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_test_send(chan, test->data8, test->data16, test->data32);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, (const char *)test, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#endif
}

#if MAVLINK_MSG_ID_TEST_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This varient of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_test_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t data8, uint16_t data16, float data32)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, data32);
    _mav_put_uint16_t(buf, 4, data16);
    _mav_put_uint8_t(buf, 6, data8);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, buf, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#else
    mavlink_test_t *packet = (mavlink_test_t *)msgbuf;
    packet->data32 = data32;
    packet->data16 = data16;
    packet->data8 = data8;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TEST, (const char *)packet, MAVLINK_MSG_ID_TEST_MIN_LEN, MAVLINK_MSG_ID_TEST_LEN, MAVLINK_MSG_ID_TEST_CRC);
#endif
}
#endif

#endif

// MESSAGE TEST UNPACKING


/**
 * @brief Get field data8 from test message
 *
 * @return  1 byte
 */
static inline uint8_t mavlink_msg_test_get_data8(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field data16 from test message
 *
 * @return  2 byte
 */
static inline uint16_t mavlink_msg_test_get_data16(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field data32 from test message
 *
 * @return  4 byte
 */
static inline float mavlink_msg_test_get_data32(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Decode a test message into a struct
 *
 * @param msg The message to decode
 * @param test C-struct to decode the message contents into
 */
static inline void mavlink_msg_test_decode(const mavlink_message_t* msg, mavlink_test_t* test)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    test->data32 = mavlink_msg_test_get_data32(msg);
    test->data16 = mavlink_msg_test_get_data16(msg);
    test->data8 = mavlink_msg_test_get_data8(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TEST_LEN? msg->len : MAVLINK_MSG_ID_TEST_LEN;
        memset(test, 0, MAVLINK_MSG_ID_TEST_LEN);
    memcpy(test, _MAV_PAYLOAD(msg), len);
#endif
}
