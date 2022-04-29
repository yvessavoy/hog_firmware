/*
Autor: Yves Savoy
Klassifizierung: Selbst erzeugt
*/

#ifndef _TASK_MQ135_H
#define _TASK_MQ135_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

typedef struct
{
    QueueHandle_t xDataQueue;
    QueueHandle_t xTempHumQueue;
} Sgp40Params_t;

void vTaskSgp40(void *pvParameters);

#endif