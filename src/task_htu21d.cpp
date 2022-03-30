#include "main.hpp"
#include "task_htu21d.hpp"
#include "Adafruit_HTU21DF.h"
#include "persistence.hpp"
#include <HardwareSerial.h>

Adafruit_HTU21DF htu = Adafruit_HTU21DF();

void vTaskHtu21d(void *pvParameter)
{
    Htu21dParams_t *p = (Htu21dParams_t *)pvParameter;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t millies;
    DataItem_t xQueueItem;
    TempHumQueueItem_t tempHumItem;
    TickType_t xLastWakeTime = xTaskGetTickCount();

    xEventGroupSetBits(xEventGroup, TEMP_SENSOR_OK_BIT | HUM_SENSOR_OK_BIT);

    // Check if sensor is reachable through I2C
    while (!htu.begin())
    {
        Serial.println("HTU21D-Sensor not found, retrying...");
        xEventGroupClearBits(xEventGroup, TEMP_SENSOR_OK_BIT | HUM_SENSOR_OK_BIT);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    for (;;)
    {
        float temp = htu.readTemperature();
        float rel_hum = htu.readHumidity();

        if (temp != 0.0f)
        {
            xEventGroupSetBits(xEventGroup, TEMP_SENSOR_OK_BIT);
            xQueueItem.dataType = DT_Temperature;
            xQueueItem.value = temp;
            xQueueSend(p->xDataQueue, &xQueueItem, portMAX_DELAY);
        }
        else
        {
            xEventGroupClearBits(xEventGroup, TEMP_SENSOR_OK_BIT);
        }

        if (rel_hum != 0.0f)
        {
            xEventGroupSetBits(xEventGroup, HUM_SENSOR_OK_BIT);
            xQueueItem.dataType = DT_Humidity;
            xQueueItem.value = rel_hum;
            xQueueSend(p->xDataQueue, &xQueueItem, portMAX_DELAY);
        }
        else
        {
            xEventGroupClearBits(xEventGroup, HUM_SENSOR_OK_BIT);
        }

        if (temp != 0.0f && rel_hum != 0.0f)
        {
            tempHumItem.temperature = temp;
            tempHumItem.humidity = rel_hum;
            xQueueSend(p->xTempHumQueue, &tempHumItem, portMAX_DELAY);
        }

        minutes = retrieveTimerMinutes();
        seconds = retrieveTimerSeconds();
        millies = ((minutes * 60) + seconds) * 1000;
        vTaskDelayUntil(&xLastWakeTime, millies / portTICK_PERIOD_MS);
    }
}