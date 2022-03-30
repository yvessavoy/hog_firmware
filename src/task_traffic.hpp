#ifndef _TASK_TRAFFIC_H
#define _TASK_TRAFFIC_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

typedef struct
{
    QueueHandle_t xTrafficQueue;
} TrafficParams_t;

void vTaskTraffic(void *pvParameters);

#endif