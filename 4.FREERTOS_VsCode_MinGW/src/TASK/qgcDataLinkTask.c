/***********************************
 * author: Jin Jia Bin
 * date: 2023-10-28
 ***********************************/
#include <stdbool.h>
#include "qgcDataLinkTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "MAVLINK/common/mavlink.h"

#include "DATALINK/udpServer.h"
#include "DATALINK/mavlinkSend.h"

/**
 * 地面站发送任务
 */
void qgcTxTask(void *param)
{
    while(1)
    {
        sendPeriod();
        vTaskDelay(1);
    }
}

/**
 * 地面站接受任务
 */
void qgcRxTask(void *param)
{
    udpServerInit("127.0.0.1",14555);
    while(1)
    {
        receiveAndParseMavlinkPacket();
        vTaskDelay(1);
    }
}



/**
 * 周期性发送数据
 */
static void sendPeriod(void)
{
    static uint16_t count_ms = 1;
    if(!(count_ms % PERIOD_HEARTBEAT))
    {
        MavlinkSendHeartbeat();
       //  printf("发送心跳包 \n");
    }
    if(!(count_ms % PERIOD_STATUS))
    {
        MavlinkSendAttitude();
    }
    if(!(count_ms % PERIOD_SENSOR))
    {

    }
    if(!(count_ms % PERIOD_RCDATA))
    {

    }
    if(!(count_ms % PERIOD_POWER))
    {

    }
    if(!(count_ms % PERIOD_MOTOR))
    {

    }
    if(!(count_ms % PERIOD_SENSOR2))
    {

    }
    if(++count_ms>=65535)
        count_ms = 1;
}


char simulatorBuff[256];
/**
 * 解析数据
 */
static void receiveAndParseMavlinkPacket() {
    int dataLen;
    udp_rcv(simulatorBuff,&dataLen);
    static mavlink_message_t mavMsg;
    static mavlink_status_t  mavStatus;
    // 解析一整个包
    for (int i = 0; i < dataLen; ++i) {
        if(mavlink_parse_char(0, simulatorBuff[i], &mavMsg, &mavStatus) == true)
        {
            // 解析数据即可
            switch (mavMsg.msgid) {
                case MAVLINK_MSG_ID_HEARTBEAT:
                {
                    printf("receive heartbeat packet! \n");
                    // 要回复一个心跳包；
                    break;
                }
                case MAVLINK_MSG_ID_GLOBAL_POSITION_INT:
                {
                    // 转换成经纬度和速度
                    static mavlink_global_position_int_t positionInt;
                    mavlink_msg_global_position_int_decode(&mavMsg,&positionInt);
                    //mavMsg
                    printf("lat:%d lon:%d\n",positionInt.lat,positionInt.lon);
                    // 要回复一个心跳包；
                    break;
                }
                case MAVLINK_MSG_ID_GLOBAL_POSITION_INT_COV:
                {
                    // 转换成经纬度和速度
                    static mavlink_global_position_int_cov_t positionIntCov;
                    mavlink_msg_global_position_int_decode(&mavMsg,&positionIntCov);
                    //mavMsg
                    printf("lat:%d lon:%d\n",positionIntCov.lat,positionIntCov.lon);
                    // 要回复一个心跳包；
                    break;
                }

            }
        }
    }


}