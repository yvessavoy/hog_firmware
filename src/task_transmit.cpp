#include <Arduino.h>
#include <HTTPClient.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "main.hpp"
#include "task_transmit.hpp"
#include "persistence.hpp"

void vTaskTransmitData(void *pvParameters)
{
    TransmitDataParams_t *p = (TransmitDataParams_t *)pvParameters;
    DataItem_t xQueueItem;
    char url[255];
    char stored_url[255];
    char post_data[255];
    HTTPClient http;
    uint8_t post_data_length;
    char tech_device_name[13];
    char custom_device_name[50];

    retrieveCustomName(custom_device_name);
    uint64_t chipid = ESP.getEfuseMac();
    snprintf(tech_device_name, 13, "%04X%08X", (uint16_t)(chipid >> 32), (uint32_t)chipid);

    for (;;)
    {
        xQueueReceive(p->xDataQueue, &xQueueItem, portMAX_DELAY);

        xQueueSend(p->xQueueUi, &xQueueItem, portMAX_DELAY);
        xQueueSend(p->xTrafficQueue, &xQueueItem, portMAX_DELAY);

        // Check if WLAN is active
        if (xEventGroupGetBits(xEventGroup) & WLAN_OK_BIT)
        {
            retrieveGrafanaUrl(stored_url);
            snprintf(url, 255, "%s/measurements", stored_url);

            switch (xQueueItem.dataType)
            {
            case DT_Temperature:
                snprintf(post_data, 255, "type=%s&value=%.2f&tech_device_name=%s&custom_device_name=%s", "temperature", xQueueItem.value, tech_device_name, custom_device_name);
                break;
            case DT_Humidity:
                snprintf(post_data, 255, "type=%s&value=%.2f&tech_device_name=%s&custom_device_name=%s", "humidity", xQueueItem.value, tech_device_name, custom_device_name);
                break;
            case DT_Light:
                snprintf(post_data, 255, "type=%s&value=%.2f&tech_device_name=%s&custom_device_name=%s", "light", xQueueItem.value, tech_device_name, custom_device_name);
                break;
            case DT_CO2:
                snprintf(post_data, 255, "type=%s&value=%.2f&tech_device_name=%s&custom_device_name=%s", "co2", xQueueItem.value, tech_device_name, custom_device_name);
                break;
            default:
                break;
            }

            http.begin(url);
            http.addHeader("Content-Type", "application/x-www-form-urlencoded");
            for (post_data_length = 0; post_data[post_data_length] != '\0'; ++post_data_length)
                ;
            int responseCode = http.POST((uint8_t *)&post_data, post_data_length);
            if (responseCode == 200)
            {
                xEventGroupSetBits(xEventGroup, SERVER_REACHABLE);
            }
            else
            {
                xEventGroupClearBits(xEventGroup, SERVER_REACHABLE);
                Serial.print("HTTP Response Code: ");
                Serial.println(responseCode);
            }
            http.end();
        }
    }
}