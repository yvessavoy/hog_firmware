/*
Autor: Yves Savoy
Klassifizierung: Selbst erzeugt
*/

#include <Wire.h>
#include <BH1750.h>
#include "task_bh1750.hpp"
#include "persistence.hpp"
#include "main.hpp"

BH1750 bh_sensor(0x23);

void vTaskBh1750(void *pvParameters)
{
    QueueHandle_t *xDataQueue = (QueueHandle_t *)pvParameters;
    TickType_t xLastWakeTime = xTaskGetTickCount();
    uint8_t minutes;
    uint8_t seconds;
    uint16_t millies;
    DataItem_t xQueueItem;

    xEventGroupSetBits(xEventGroup, LIGHT_SENSOR_OK_BIT);
    while (!bh_sensor.begin(BH1750::CONTINUOUS_HIGH_RES_MODE))
    {
        Serial.println("BH1750-Sensor not found, retrying...");
        xEventGroupClearBits(xEventGroup, LIGHT_SENSOR_OK_BIT);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    Serial.println("BH1750-Sensor OK");

    for (;;)
    {
        if (bh_sensor.measurementReady())
        {
            float lux = bh_sensor.readLightLevel();

            if (lux == -1 || lux == -2)
            {
                xEventGroupClearBits(xEventGroup, LIGHT_SENSOR_OK_BIT);
            }
            else
            {
                xEventGroupSetBits(xEventGroup, LIGHT_SENSOR_OK_BIT);
                xQueueItem.dataType = DT_Light;
                xQueueItem.value = lux;
                xQueueSend(xDataQueue, &xQueueItem, portMAX_DELAY);
            }
        }

        minutes = retrieveTimerMinutes();
        seconds = retrieveTimerSeconds();
        millies = ((minutes * 60) + seconds) * 1000;
        vTaskDelayUntil(&xLastWakeTime, millies / portTICK_PERIOD_MS);
    }
}