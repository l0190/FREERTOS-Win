/***********************************
 * author: Jin Jia Bin
 * date: 2023-10-28
 ***********************************/
#ifndef __DATA_LINK_TASK_H
#define __DATA_LINK_TASK_H

//数据返回周期时间（单位ms）]
#define  PERIOD_HEARTBEAT	20
#define  PERIOD_STATUS		30
#define  PERIOD_SENSOR 		10
#define  PERIOD_RCDATA 		40
#define  PERIOD_POWER 		100
#define  PERIOD_MOTOR		40
#define  PERIOD_SENSOR2 	40
#define  PERIOD_SPEED   	50

static void receiveAndParseMavlinkPacket();
static void sendPeriod(void);

void qgcTxTask(void *param);
void qgcRxTask(void *param);

#endif