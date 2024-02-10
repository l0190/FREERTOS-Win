#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
/*
使用钩子函数的前提:
    定义configUSE_IDLE_HOOK为1
    实现vApplicationIdleHook函数
*/
//define configUSE_IDLE_HOOK 1
/*
配置任务调度器的调度算法:确定哪个就绪态任务可以切换到运行态
FreeRTOSConfig.h文件
    configUSE_PREEMPTION
    configUSE_TIME_SLICING
    configUSE_TICKLESS_IDLE
*/
void vTask1(void *pvParameters);
void vTask2(void *pvParameters);

int main(void)
{
    //创建任务(函数指针,任务名,栈大小,传入参数,优先级,任务句柄)
    //任务句柄就是xTaskCreate创建后执行的任务的指针
    xTaskCreate(&vTask1, "Task 1", 1024, NULL, 1, NULL);
    xTaskCreate(&vTask2, "Task 2", 1024, NULL, 1, NULL);
    /*启动任务调度器*/
    vTaskStartScheduler();
    
    return 0;
}
/*
任务是一个函数,这个函数不能返回,同一个函数可以用来创建多个任务
任务与任务内部相互独立,尽量使用局部变量,将命名空间相互独立开来
每个任务都有自己独立的栈:
    任务A的局部变量放在任务A的栈里、任务B的局部变量放在任务B的栈里
    不同任务的局部变量,有自己的副本
*/
void vTask1(void *pvParameters)
{
    for (;;)
    {
        printf("Task 1 running\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    //删除任务,输入为null表示删除自己.删除指定任务需要输入任务句柄
    //vTaskDelay(NULL);
}

void vTask2(void *pvParameters)
{
    for (;;)
    {
        printf("Task 2\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

