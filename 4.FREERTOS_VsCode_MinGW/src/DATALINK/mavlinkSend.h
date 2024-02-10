/***********************************
 * author: Jin Jia Bin
 * date: 2023-10-28
 ***********************************/
#ifndef __MY_MAVLINK_SEND_H
#define __MY_MAVLINK_SEND_H


#define MAVLINK_SYSTEM_ID       1
#define MAVLINK_COMPONENT_ID    MAV_COMP_ID_AUTOPILOT1


void MavlinkSendHeartbeat(void);
void MavlinkSendAttitude(void);
#endif