#include <Arduino.h>
#include "main.hpp"
#include "task_traffic.hpp"
#include "persistence.hpp"
#include "utils.hpp"

#define TEMP_GREEN_PIN 34
#define TEMP_YELLOW_PIN 35
#define TEMP_RED_PIN 32
#define HUMIDITY_GREEN_PIN 15
#define HUMIDITY_YELLOW_PIN 2
#define HUMIDITY_RED_PIN 4
#define LIGHT_GREEN_PIN 14
#define LIGHT_YELLOW_PIN 12
#define LIGHT_RED_PIN 13
#define CO2_GREEN_PIN 16
#define CO2_YELLOW_PIN 17
#define CO2_RED_PIN 19

void vTaskTraffic(void *pvParameters)
{
    TrafficParams_t *p = (TrafficParams_t *)pvParameters;
    DataItem_t xQueueItem;
    uint16_t min_val, max_val;
    uint8_t g_pin, y_pin, r_pin;

    pinMode(TEMP_GREEN_PIN, OUTPUT);
    pinMode(TEMP_YELLOW_PIN, OUTPUT);
    pinMode(TEMP_RED_PIN, OUTPUT);
    pinMode(HUMIDITY_GREEN_PIN, OUTPUT);
    pinMode(HUMIDITY_YELLOW_PIN, OUTPUT);
    pinMode(HUMIDITY_RED_PIN, OUTPUT);
    pinMode(LIGHT_GREEN_PIN, OUTPUT);
    pinMode(LIGHT_YELLOW_PIN, OUTPUT);
    pinMode(LIGHT_RED_PIN, OUTPUT);
    pinMode(CO2_GREEN_PIN, OUTPUT);
    pinMode(CO2_YELLOW_PIN, OUTPUT);
    pinMode(CO2_RED_PIN, OUTPUT);

    for (;;)
    {
        xQueueReceive(p->xTrafficQueue, &xQueueItem, portMAX_DELAY);

        switch (xQueueItem.dataType)
        {
        case DT_Temperature:
            min_val = retrieveMinTemp();
            max_val = retrieveMaxTemp();
            r_pin = TEMP_RED_PIN;
            y_pin = TEMP_YELLOW_PIN;
            g_pin = TEMP_GREEN_PIN;
            break;

        case DT_Humidity:
            min_val = retrieveMinHumidity();
            max_val = retrieveMaxHumidity();
            r_pin = HUMIDITY_RED_PIN;
            y_pin = HUMIDITY_YELLOW_PIN;
            g_pin = HUMIDITY_GREEN_PIN;
            break;

        case DT_Light:
            min_val = retrieveMinLight();
            max_val = retrieveMaxLight();
            r_pin = LIGHT_RED_PIN;
            y_pin = LIGHT_YELLOW_PIN;
            g_pin = LIGHT_GREEN_PIN;
            break;

        default:
            min_val = retrieveMinCO2();
            max_val = retrieveMaxCO2();
            r_pin = CO2_RED_PIN;
            y_pin = CO2_YELLOW_PIN;
            g_pin = CO2_GREEN_PIN;
            break;
        }

        digitalWrite(g_pin, LOW);
        digitalWrite(y_pin, LOW);
        digitalWrite(r_pin, LOW);

        // Set corresponding traffic light correctly
        if (xQueueItem.value > max_val || xQueueItem.value < min_val)
        {
            digitalWrite(r_pin, HIGH);
        }
        else if (isInUpperLowerPercentage(xQueueItem.value, min_val, max_val))
        {
            digitalWrite(y_pin, HIGH);
        }
        else
        {
            digitalWrite(g_pin, HIGH);
        }
    }
}