/*
Autor: Yves Savoy
Klassifizierung: Selbst erzeugt
*/

#ifndef _TASK_WLAN_H
#define _TASK_WLAN_H

#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/task.h>

typedef struct
{
} WlanParams_t;

void vTaskWlan(void *pvParameters);

#endif