#ifndef _MAIN_H
#define _MAIN_H

#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <WiFi.h>

typedef enum
{
    DT_Temperature,
    DT_Humidity,
    DT_Light,
    DT_CO2,
    DT_SensorStatus,
    DT_WlanStatus,
    DT_BatteryStatus,
} DataType_t;

typedef struct
{
    DataType_t dataType;
    float value;
} DataItem_t;

typedef struct
{
    float temperature;
    float humidity;
} TempHumQueueItem_t;

extern IPAddress ap_ip;
extern EventGroupHandle_t xEventGroup;

// Event group bits
#define BTN_1_PRESSED (1 << 0)
#define BTN_2_PRESSED (1 << 1)
#define BTN_3_PRESSED (1 << 2)
#define NEW_DATA_BIT (1 << 3)
#define WLAN_START_BIT (1 << 4)
#define AP_IP_AVAILABLE_BIT (1 << 5)
#define WLAN_OK_BIT (1 << 6)
#define TEMP_SENSOR_OK_BIT (1 << 7)
#define HUM_SENSOR_OK_BIT (1 << 8)
#define LIGHT_SENSOR_OK_BIT (1 << 9)
#define CO2_SENSOR_OK_BIT (1 << 10)
#define SERVER_REACHABLE (1 << 11)

#endif