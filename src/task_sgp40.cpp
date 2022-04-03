#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include "task_sgp40.hpp"
#include "main.hpp"
#include "persistence.hpp"
#include "Adafruit_SGP40.h"

Adafruit_SGP40 sgp;

void vTaskSgp40(void *pvParameters)
{
    Sgp40Params_t *p = (Sgp40Params_t *)pvParameters;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t millies;
    DataItem_t xQueueItem;
    TempHumQueueItem_t tempHumItem;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    int32_t voc;

    xEventGroupSetBits(xEventGroup, CO2_SENSOR_OK_BIT);

    while (!sgp.begin())
    {
        Serial.println("SGP40-Sensor not found, retrying...");
        xEventGroupClearBits(xEventGroup, CO2_SENSOR_OK_BIT);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    Serial.println("SGP40-Sensor OK");

    // Preheat time of SGP40: 10s
    vTaskDelay(10000 / portTICK_PERIOD_MS);

    for (;;)
    {
        xQueueReceive(p->xTempHumQueue, &tempHumItem, portMAX_DELAY);

        voc = sgp.measureVocIndex(tempHumItem.temperature, tempHumItem.humidity);
        if (voc != 0)
        {
            xEventGroupSetBits(xEventGroup, CO2_SENSOR_OK_BIT);
            xQueueItem.dataType = DT_CO2;
            xQueueItem.value = voc;
            xQueueSend(p->xDataQueue, &xQueueItem, portMAX_DELAY);
        }
        else
        {
            xEventGroupClearBits(xEventGroup, CO2_SENSOR_OK_BIT);
        }

        minutes = retrieveTimerMinutes();
        seconds = retrieveTimerSeconds();
        millies = ((minutes * 60) + seconds) * 1000;
        vTaskDelayUntil(&xLastWakeTime, millies / portTICK_PERIOD_MS);
    }
}