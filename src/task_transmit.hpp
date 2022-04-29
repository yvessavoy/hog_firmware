/*
Autor: Yves Savoy
Klassifizierung: Selbst erzeugt
*/

#ifndef _TASK_TRANSMIT_H
#define _TASK_TRANSMIT_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

typedef struct
{
    QueueHandle_t xDataQueue;
    QueueHandle_t xQueueUi;
    QueueHandle_t xTrafficQueue;
} TransmitDataParams_t;

void vTaskTransmitData(void *pvParameters);

#endif