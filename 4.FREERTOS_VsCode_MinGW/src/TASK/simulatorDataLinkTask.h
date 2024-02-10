/***********************************
 * author: Jin Jia Bin
 * date: 2023-10-28
 ***********************************/
#ifndef __SIMULATOR_DATA_LINK_TASK_H
#define __SIMULATOR_DATA_LINK_TASK_H



static void receiveAndParseMavlinkPacket();
static void sendPeriod(void);

void simulatorTxTask(void *param);
void simulatorRxTask(void *param);

#endif