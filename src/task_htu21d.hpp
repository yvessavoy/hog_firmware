#ifndef _TASK_HTU21D_H
#define _TASK_HTU21D_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

typedef struct
{
    QueueHandle_t xDataQueue;
    QueueHandle_t xTempHumQueue;
} Htu21dParams_t;

void vTaskHtu21d(void *pvParameter);

#endif