/*
Autor: Yves Savoy
Klassifizierung: Selbst erzeugt
*/

#ifndef _TASK_UI_H
#define _TASK_UI_H

#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/event_groups.h>

typedef struct
{
} UiParams_t;

void vTaskUiReceiveData(void *pvParameter);
void vTaskUi(void *pvParameter);

#endif