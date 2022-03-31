#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <GxEPD2_BW.h>
#include <WiFi.h>

#include "main.hpp"
#include "task_ui.hpp"
#include "task_htu21d.hpp"
#include "task_bh1750.hpp"
#include "task_transmit.hpp"
#include "task_sgp40.hpp"
#include "task_traffic.hpp"
#include "task_wlan.hpp"
#include "persistence.hpp"

QueueHandle_t xDataQueue;
QueueHandle_t xQueueUi;
QueueHandle_t xTempHumQueue;
QueueHandle_t xTrafficQueue;
Htu21dParams_t htu21dParams;
TransmitDataParams_t transmitParams;
Sgp40Params_t sgp40Params;
TrafficParams_t trafficParams;
IPAddress ap_ip;
EventGroupHandle_t xEventGroup;

void setup()
{
  Serial.begin(115200);
  vTaskDelay(500 / portTICK_PERIOD_MS);

  // Init I2C-bus
  Wire.begin();

  // Check if there is anything in the flash memory,
  // and if not, fill it with default values
  initPersistency();
  if (retrieveMinTemp() == 0xff)
  {
    Serial.println("Flash empty, init it");
    storeMinTemp(21);
    storeMaxTemp(26);
    storeMinHumidity(30);
    storeMaxHumidity(60);
    storeMinLight(500);
    storeMaxLight(9999);
    storeMinCO2(0);
    storeMaxCO2(999);
    storeTimer(1, 0);
  }

  xDataQueue = xQueueCreate(10, sizeof(DataItem_t));
  xQueueUi = xQueueCreate(10, sizeof(DataItem_t));
  xTrafficQueue = xQueueCreate(10, sizeof(DataItem_t));
  xTempHumQueue = xQueueCreate(10, sizeof(TempHumQueueItem_t));
  xEventGroup = xEventGroupCreate();

  if (xDataQueue == NULL || xQueueUi == NULL || xTempHumQueue == NULL || xTrafficQueue == NULL)
  {
    Serial.println("One or more queues could not be created");
    vTaskDelay(portMAX_DELAY);
  }

  transmitParams.xDataQueue = xDataQueue;
  transmitParams.xQueueUi = xQueueUi;
  transmitParams.xTrafficQueue = xTrafficQueue;

  sgp40Params.xDataQueue = xDataQueue;
  sgp40Params.xTempHumQueue = xTempHumQueue;

  htu21dParams.xDataQueue = xDataQueue;
  htu21dParams.xTempHumQueue = xTempHumQueue;

  trafficParams.xTrafficQueue = xTrafficQueue;

  xTaskCreate(vTaskUi, "task_ui", configMINIMAL_STACK_SIZE + 1500, NULL, 3, NULL);
  xTaskCreate(vTaskUiReceiveData, "task_ui_receive", configMINIMAL_STACK_SIZE + 100, (void *)xQueueUi, 3, NULL);
  xTaskCreate(vTaskTransmitData, "task_transmit_data", configMINIMAL_STACK_SIZE + 2000, (void *)&transmitParams, 2, NULL);
  xTaskCreate(vTaskSgp40, "task_sgp40", configMINIMAL_STACK_SIZE + 500, (void *)&sgp40Params, 2, NULL);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  xTaskCreate(vTaskBh1750, "task_bh1750", configMINIMAL_STACK_SIZE + 500, (void *)xDataQueue, 2, NULL);
  vTaskDelay(500 / portTICK_PERIOD_MS);
  xTaskCreate(vTaskHtu21d, "task_htu21d", configMINIMAL_STACK_SIZE + 300, (void *)&htu21dParams, 2, NULL);
  xTaskCreate(vTaskTraffic, "task_traffic", configMINIMAL_STACK_SIZE + 200, (void *)&trafficParams, 2, NULL);
  xTaskCreate(vTaskWlan, "task_wlan", configMINIMAL_STACK_SIZE + 1500, NULL, 3, NULL);
}

void loop()
{
  vTaskDelay(portMAX_DELAY);
}