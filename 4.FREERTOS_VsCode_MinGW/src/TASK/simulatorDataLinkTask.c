/***********************************
 * author: Jin Jia Bin
 * date: 2023-10-28
 ***********************************/
#include <stdbool.h>
#include "simulatorDataLinkTask.h"
#include "qgcDataLinkTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "MAVLINK/common/mavlink.h"

#include "DATALINK/udpServer.h"
#include "DATALINK/mavlinkSend.h"


/**
 * 地面站发送任务
 */
void simulatorTxTask(void *param)
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
void simulatorRxTask(void *param)
{
    udpServerInit("127.0.0.1",14561);
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
        //MavlinkSendAttitude();
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


char buff[256] ={0};
/**
 * 解析数据
 */
static void receiveAndParseMavlinkPacket() {
    int dataLen;

    memset(buff,0x00,sizeof(buff));
    udp_rcv(buff,&dataLen);
    static mavlink_message_t mavMsg;
    static mavlink_status_t  mavStatus;
    // 解析一整个包
    for (int i = 0; i < dataLen; ++i) {
        if (mavlink_parse_char(0, buff[i], &mavMsg, &mavStatus) == true) {
            printf("mesId: %d \n",mavMsg.msgid);
            switch (mavMsg.msgid) {
                case MAVLINK_MSG_ID_HEARTBEAT:
                {
                    //printf("receive heartbeat packet! \n");
                    // 要回复一个心跳包；
                    // MavlinkSendHeartbeat();
                    break;
                }
                case MAVLINK_MSG_ID_HIL_SENSOR:{
                    static mavlink_hil_sensor_t hilSensor;
                    mavlink_msg_hil_sensor_decode(&mavMsg,&hilSensor);
                    //mavMsg
                    printf("lat:%f lon:%f\n",hilSensor.xacc,hilSensor.yacc);
                    // 要回复一个心跳包；
                    break;
                }
                case MAVLINK_MSG_ID_HIL_GPS:{
                    static mavlink_hil_gps_t hilGps;
                    mavlink_msg_hil_gps_decode(&mavMsg,&hilGps);
                    //mavMsg
                    printf("lat:%d lon:%d\n",hilGps.lon,hilGps.lat);
                    // 要回复一个心跳包；
                    break;
                }


            }
        }

    }
    // 清空buffer

}
