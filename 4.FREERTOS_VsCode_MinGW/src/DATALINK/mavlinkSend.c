/***********************************
 * author: Jin Jia Bin
 * date: 2023-10-28
 ***********************************/
#include "mavlinkSend.h"
#include "common/mavlink.h"
#include "udpServer.h"

void  MavlinkSendHeartbeat()
{
    mavlink_message_t msg;
    mavlink_heartbeat_t heartbeat;
    uint8_t msgLength;
    uint8_t msgBuffer[MAVLINK_MAX_PAYLOAD_LEN+10];

    //消息负载赋值
    heartbeat.type          = MAV_TYPE_QUADROTOR;
    heartbeat.autopilot     = MAV_AUTOPILOT_PX4;    //设置飞控类型为PX4，以便能使用QGroudControl地面站
    heartbeat.base_mode     = MAV_MODE_FLAG_AUTO_ENABLED;

    heartbeat.base_mode |= MAV_MODE_MANUAL_ARMED;

    heartbeat.custom_mode   = 0x0001 << 16;

    heartbeat.system_status = MAV_STATE_STANDBY;

    //mavlink组帧
    mavlink_msg_heartbeat_encode(MAVLINK_SYSTEM_ID, MAVLINK_COMPONENT_ID, &msg, &heartbeat);
    //消息帧格式化
    msgLength = mavlink_msg_to_send_buffer(msgBuffer, &msg);
    //发送消息帧
    udpSendData(msgBuffer,msgLength);
}

/**
 * 姿态信息的消息包
 */
void MavlinkSendAttitude()
{
    mavlink_message_t msg;
    mavlink_attitude_t attitude;
    uint8_t msgLength;
    uint8_t msgBuffer[MAVLINK_MAX_PAYLOAD_LEN+10];

    //消息负载赋值 获取当前时间
    attitude.time_boot_ms = 0;
    attitude.roll         = 0.1;
    attitude.pitch        = 0.1;
    attitude.yaw          = 10;
    attitude.rollspeed    = 12;
    attitude.pitchspeed   = 1;
    attitude.yawspeed     = 1;

    //mavlink组帧
    mavlink_msg_attitude_encode(MAVLINK_SYSTEM_ID, MAVLINK_COMPONENT_ID, &msg, &attitude);
    //消息帧格式化
    msgLength = mavlink_msg_to_send_buffer(msgBuffer, &msg);
    //发送消息帧
    udpSendData(msgBuffer,msgLength);
}
