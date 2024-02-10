
#include "FreeRTOS/include/FreeRTOS.h"
#include "FreeRTOS/include/task.h"
#include "src/DATALINK/udpServer.h"
#include "src/TASK/qgcDataLinkTask.h"
#include "src/TASK/rcInputTask.h"
#include "src/TASK/simulatorDataLinkTask.h"



int main() {

//    xTaskCreate(qgcTxTask, "qgcTxTask", 1000, NULL, 1, NULL);
//    xTaskCreate(qgcRxTask, "qgcRxTask", 1000, NULL, 1, NULL);
//
//    xTaskCreate(rcInputTask, "rcInputTask", 1000, NULL, 2, NULL);
    setbuf(stdout, NULL); // 禁用缓冲区,printf 立即输入到控制台
    xTaskCreate(simulatorRxTask, "simulatorRxTask", 1000, NULL, 1, NULL);
    xTaskCreate(simulatorTxTask, "simulatorTxTask", 1000, NULL, 1, NULL);


    vTaskStartScheduler();
    return 0;
}