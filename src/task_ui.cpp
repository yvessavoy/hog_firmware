#include <GxEPD2_BW.h>
#include <WiFi.h>

#include "task_ui.hpp"
#include "ui.hpp"
#include "main.hpp"
#include "persistence.hpp"

#define CS_PIN 5
#define DC_PIN 25
#define RST_PIN 33
#define BUSY_PIN 27
#define BTN_LEFT_UP_PIN 15
#define BTN_RIGHT_DOWN_PIN 4
#define BTN_ENTER 2
#define ISR_MIN_TIME_PASSED 200

GxEPD2_BW<GxEPD2_290_T94_V2, GxEPD2_290_T94_V2::HEIGHT> display(GxEPD2_290_T94_V2(CS_PIN, DC_PIN, RST_PIN, BUSY_PIN));

typedef enum
{
    State_Home,
    State_Settings,
    State_WLAN,
    State_Timer,
    State_Values
} States;

EventBits_t xEventBits;
BaseType_t xHigherPriorityTaskWoken = pdFALSE;
SemaphoreHandle_t xSemaphore;
unsigned long btn1LastInterrupt;
unsigned long btn2LastInterrupt;
unsigned long btn3LastInterrupt;
uint8_t wlan_disconnect_yes = 0;

// Measurements for home screen
Measurements_t measurements;
uint8_t valueUpdateNeeded = 0xff;

void BTN1_ISR()
{
    if (millis() - btn1LastInterrupt > ISR_MIN_TIME_PASSED)
    {
        xHigherPriorityTaskWoken = pdFALSE;
        xEventGroupSetBitsFromISR(xEventGroup, BTN_1_PRESSED, &xHigherPriorityTaskWoken);
        btn1LastInterrupt = millis();
    }
}

void BTN2_ISR()
{
    if (millis() - btn2LastInterrupt > ISR_MIN_TIME_PASSED)
    {
        xHigherPriorityTaskWoken = pdFALSE;
        xEventGroupSetBitsFromISR(xEventGroup, BTN_2_PRESSED, &xHigherPriorityTaskWoken);
        btn2LastInterrupt = millis();
    }
}

void BTN3_ISR()
{
    if (millis() - btn3LastInterrupt > ISR_MIN_TIME_PASSED)
    {
        xHigherPriorityTaskWoken = pdFALSE;
        xEventGroupSetBitsFromISR(xEventGroup, BTN_3_PRESSED, &xHigherPriorityTaskWoken);
        btn3LastInterrupt = millis();
    }
}

void vTaskUiReceiveData(void *pvParameter)
{
    QueueHandle_t *dataQueue = (QueueHandle_t *)pvParameter;
    DataItem_t xQueueItem;
    EventBits_t eb;

    while (xSemaphore == NULL)
        vTaskDelay(1 / portTICK_PERIOD_MS);

    for (;;)
    {
        xQueueReceive(dataQueue, &xQueueItem, portMAX_DELAY);
        if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
        {
            valueUpdateNeeded |= (1 << xQueueItem.dataType);
            eb = xEventGroupGetBits(xEventGroup);

            // Check WLAN status
            if ((eb & WLAN_OK_BIT) && (WiFi.status() == WL_CONNECTED) && (eb & SERVER_REACHABLE) && measurements.wlan_status == 0)
            {
                valueUpdateNeeded |= (1 << DT_WlanStatus);
                measurements.wlan_status = 1;
                strcpy(measurements.error_code, " ");
            }

            if (measurements.wlan_status == 1 && (!(eb & WLAN_OK_BIT) || !(eb & SERVER_REACHABLE) || WiFi.status() != WL_CONNECTED))
            {
                valueUpdateNeeded |= (1 << DT_WlanStatus);
                measurements.wlan_status = 0;
            }

            // Check if sensor status is OK
            if ((eb & TEMP_SENSOR_OK_BIT) && (eb & HUM_SENSOR_OK_BIT) && (eb & LIGHT_SENSOR_OK_BIT) && (eb & CO2_SENSOR_OK_BIT) && measurements.sensor_status == 0)
            {
                valueUpdateNeeded |= (1 << DT_SensorStatus);
                measurements.sensor_status = 1;
                strcpy(measurements.error_code, " ");
            }

            // Check if sensor status is NOK
            if (measurements.sensor_status == 1 && (!(eb & TEMP_SENSOR_OK_BIT) || !(eb & HUM_SENSOR_OK_BIT) || !(eb & LIGHT_SENSOR_OK_BIT) || !(eb & CO2_SENSOR_OK_BIT)))
            {
                valueUpdateNeeded |= (1 << DT_SensorStatus);
                measurements.sensor_status = 0;
            }

            // Set correct error text
            if (!(eb & TEMP_SENSOR_OK_BIT))
            {
                strcpy(measurements.error_code, "S001");
            }
            else if (!(eb & HUM_SENSOR_OK_BIT))
            {
                strcpy(measurements.error_code, "S002");
            }
            else if (!(eb & LIGHT_SENSOR_OK_BIT))
            {
                strcpy(measurements.error_code, "S003");
            }
            else if (!(eb & CO2_SENSOR_OK_BIT))
            {
                strcpy(measurements.error_code, "S004");
            }
            else if (WiFi.status() == WL_NO_SSID_AVAIL)
            {
                strcpy(measurements.error_code, "W001");
            }
            else if (WiFi.status() == WL_CONNECT_FAILED)
            {
                strcpy(measurements.error_code, "W002");
            }
            else if (!(eb & SERVER_REACHABLE))
            {
                strcpy(measurements.error_code, "W003");
            }

            switch (xQueueItem.dataType)
            {
            case DT_Temperature:
                measurements.temperature = xQueueItem.value;
                break;

            case DT_Humidity:
                measurements.humidity = xQueueItem.value;
                break;

            case DT_Light:
                measurements.light = xQueueItem.value;
                break;

            case DT_CO2:
                measurements.co2 = xQueueItem.value;
                break;

            default:
                break;
            }
            xSemaphoreGive(xSemaphore);
        }
        xEventGroupSetBits(xEventGroup, NEW_DATA_BIT);
    }
}

void vTaskUi(void *pvParameter)
{
    States state = State_Home;
    States_Settings state_settings = Settings_WLAN;
    States_Values state_values = Val_MaxTemp;
    EventBits_t eventBits;
    uint8_t min_selected = 1;
    xSemaphore = xSemaphoreCreateMutex();

    // Retrieve currently stored user values
    OptValues_t optValues;
    optValues.minTemp = retrieveMinTemp();
    optValues.maxTemp = retrieveMaxTemp();
    optValues.minHum = retrieveMinHumidity();
    optValues.maxHum = retrieveMaxHumidity();
    optValues.minLight = retrieveMinLight();
    optValues.maxLight = retrieveMaxLight();
    optValues.minCO2 = retrieveMinCO2();
    optValues.maxCO2 = retrieveMaxCO2();

    // Receive timer values
    TimerValue_t timerValue;
    timerValue.minutes = retrieveTimerMinutes();
    timerValue.seconds = retrieveTimerSeconds();
    measurements.battery_level = 100;

    setupDisplay(&display);
    drawHomeLayout(&display);

    // Setup button pins and interrupts
    pinMode(BTN_LEFT_UP_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(BTN_LEFT_UP_PIN), BTN1_ISR, RISING);

    pinMode(BTN_RIGHT_DOWN_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(BTN_RIGHT_DOWN_PIN), BTN2_ISR, RISING);

    pinMode(BTN_ENTER, INPUT);
    attachInterrupt(digitalPinToInterrupt(BTN_ENTER), BTN3_ISR, RISING);

    for (;;)
    {
        eventBits = xEventGroupWaitBits(xEventGroup, BTN_1_PRESSED | BTN_2_PRESSED | BTN_3_PRESSED | NEW_DATA_BIT | AP_IP_AVAILABLE_BIT, pdTRUE, pdFALSE, portMAX_DELAY);

        switch (state)
        {
        case State_Home:
            if ((eventBits & BTN_3_PRESSED))
            {
                drawSettingsLayout(&display);
                state = State_Settings;
                setActiveSettingsItem(&display, state_settings);
            }
            else if ((eventBits & NEW_DATA_BIT))
            {
                if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
                {
                    updateHomeValues(&display, &measurements, valueUpdateNeeded);
                    xSemaphoreGive(xSemaphore);
                }
            }
            break;

        case State_Settings:
            if ((eventBits & BTN_1_PRESSED) && state_settings != Settings_WLAN)
            {
                switch (state_settings)
                {
                case Settings_Timer:
                    state_settings = Settings_WLAN;
                    break;
                case Settings_Values:
                    state_settings = Settings_Timer;
                    break;
                default:
                    state_settings = Settings_Values;
                    break;
                }
                setActiveSettingsItem(&display, state_settings);
            }

            if ((eventBits & BTN_2_PRESSED) && state_settings != Settings_Home)
            {
                switch (state_settings)
                {
                case Settings_WLAN:
                    state_settings = Settings_Timer;
                    break;
                case Settings_Timer:
                    state_settings = Settings_Values;
                    break;
                case Settings_Values:
                    state_settings = Settings_Home;
                    break;
                default:
                    break;
                }
                setActiveSettingsItem(&display, state_settings);
            }

            if ((eventBits & BTN_3_PRESSED))
            {
                switch (state_settings)
                {
                case Settings_WLAN:
                    state = State_WLAN;
                    drawWlanLayout(&display);
                    wlan_disconnect_yes = 0;
                    if ((xEventGroupGetBits(xEventGroup) & WLAN_OK_BIT))
                    {
                        drawWlanActive(&display, wlan_disconnect_yes);
                    }
                    else
                    {
                        xEventGroupSetBits(xEventGroup, WLAN_START_BIT);
                    }
                    break;

                case Settings_Timer:
                    state = State_Timer;
                    drawTimerLayout(&display, &timerValue);
                    min_selected = 1;
                    break;

                case Settings_Values:
                    state = State_Values;
                    drawValuesLayout(&display, &optValues);
                    setActiveValuesItem(&display, state_values, &optValues);
                    break;

                default:
                    state = State_Home;
                    if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
                    {
                        drawHomeLayout(&display);
                        updateHomeValues(&display, &measurements, valueUpdateNeeded);
                        xSemaphoreGive(xSemaphore);
                    }
                    break;
                }
            }

            break;

        case State_WLAN:
            if ((eventBits & BTN_1_PRESSED) && (xEventGroupGetBits(xEventGroup) & WLAN_OK_BIT))
            {
                if (wlan_disconnect_yes == 0)
                {
                    wlan_disconnect_yes = 1;
                    drawWlanActive(&display, wlan_disconnect_yes);
                }
            }

            if ((eventBits & BTN_2_PRESSED) && (xEventGroupGetBits(xEventGroup) & WLAN_OK_BIT))
            {
                if (wlan_disconnect_yes == 1)
                {
                    wlan_disconnect_yes = 0;
                    drawWlanActive(&display, wlan_disconnect_yes);
                }
            }

            if ((eventBits & BTN_3_PRESSED))
            {
                if (wlan_disconnect_yes && WiFi.status() == WL_CONNECTED && (xEventGroupGetBits(xEventGroup) & WLAN_OK_BIT))
                {
                    WiFi.disconnect();
                    xEventGroupClearBits(xEventGroup, WLAN_OK_BIT);
                    storeWlanSsid("");
                    storeWlanPassword("");
                }

                state = State_Settings;
                drawSettingsLayout(&display);
                setActiveSettingsItem(&display, state_settings);
            }

            if ((eventBits & AP_IP_AVAILABLE_BIT))
            {
                updateWlanIP(&display, &ap_ip);
            }
            break;

        case State_Timer:
            if ((eventBits & BTN_1_PRESSED))
            {
                if (min_selected)
                {
                    if (timerValue.minutes - 1 < 0)
                    {
                        timerValue.minutes = 59;
                    }
                    else
                    {
                        timerValue.minutes--;
                    }
                }
                else
                {
                    if (timerValue.seconds - 1 < 0)
                    {
                        timerValue.seconds = 59;
                    }
                    else
                    {
                        timerValue.seconds--;
                    }
                }

                updateTimerValue(&display, &timerValue, min_selected);
            }

            if ((eventBits & BTN_2_PRESSED))
            {
                if (min_selected)
                {
                    if (timerValue.minutes + 1 > 59)
                    {
                        timerValue.minutes = 0;
                    }
                    else
                    {
                        timerValue.minutes++;
                    }
                }
                else
                {
                    if (timerValue.seconds + 1 > 59)
                    {
                        timerValue.seconds = 0;
                    }
                    else
                    {
                        timerValue.seconds++;
                    }
                }

                updateTimerValue(&display, &timerValue, min_selected);
            }

            if ((eventBits & BTN_3_PRESSED))
            {
                if (min_selected)
                {
                    min_selected = 0;
                    updateTimerValue(&display, &timerValue, min_selected);
                }
                else
                {
                    storeTimer(timerValue.minutes, timerValue.seconds);
                    state = State_Settings;
                    drawSettingsLayout(&display);
                    setActiveSettingsItem(&display, state_settings);
                }
            }
            break;

        case State_Values:
            if ((eventBits & BTN_1_PRESSED))
            {
                switch (state_values)
                {
                case Val_MaxTemp:
                    if (optValues.maxTemp - 1 > optValues.minTemp)
                        optValues.maxTemp--;
                    break;
                case Val_MinTemp:
                    if (optValues.minTemp - 1 >= 0)
                        optValues.minTemp--;
                    break;
                case Val_MaxHum:
                    if (optValues.maxHum - 1 > optValues.minHum)
                        optValues.maxHum--;
                    break;
                case Val_MinHum:
                    if (optValues.minHum - 1 >= 0)
                        optValues.minHum--;
                    break;
                case Val_MaxLight:
                    if (optValues.maxLight - 1 > optValues.minLight)
                        optValues.maxLight--;
                    break;
                case Val_MinLight:
                    if (optValues.minLight - 1 >= 0)
                        optValues.minLight--;
                    break;
                case Val_MaxCO2:
                    if (optValues.maxCO2 - 1 > optValues.minCO2)
                        optValues.maxCO2--;
                    break;
                case Val_MinCO2:
                    if (optValues.minCO2 - 1 >= 0)
                        optValues.minCO2--;
                    break;
                }
                setActiveValuesItem(&display, state_values, &optValues);
            }

            if ((eventBits & BTN_2_PRESSED))
            {
                switch (state_values)
                {
                case Val_MaxTemp:
                    if (optValues.maxTemp + 1 < 255)
                        optValues.maxTemp++;
                    break;
                case Val_MinTemp:
                    if (optValues.minTemp + 1 <= optValues.maxTemp)
                        optValues.minTemp++;
                    break;
                case Val_MaxHum:
                    if (optValues.maxHum + 1 < 255)
                        optValues.maxHum++;
                    break;
                case Val_MinHum:
                    if (optValues.minHum + 1 <= optValues.maxHum)
                        optValues.minHum++;
                    break;
                case Val_MaxLight:
                    if (optValues.maxLight + 1 < 10000)
                        optValues.maxLight++;
                    break;
                case Val_MinLight:
                    if (optValues.minLight + 1 <= optValues.maxLight)
                        optValues.minLight++;
                    break;
                case Val_MaxCO2:
                    if (optValues.maxCO2 + 1 < 10000)
                        optValues.maxCO2++;
                    break;
                case Val_MinCO2:
                    if (optValues.minCO2 + 1 <= optValues.maxCO2)
                        optValues.minCO2++;
                    break;
                }
                setActiveValuesItem(&display, state_values, &optValues);
            }

            if ((eventBits & BTN_3_PRESSED))
            {
                switch (state_values)
                {
                case Val_MaxTemp:
                    storeMaxTemp(optValues.maxTemp);
                    state_values = Val_MinTemp;
                    break;
                case Val_MinTemp:
                    storeMinTemp(optValues.minTemp);
                    state_values = Val_MaxHum;
                    break;
                case Val_MaxHum:
                    storeMaxHumidity(optValues.maxHum);
                    state_values = Val_MinHum;
                    break;
                case Val_MinHum:
                    storeMinHumidity(optValues.minHum);
                    state_values = Val_MaxLight;
                    break;
                case Val_MaxLight:
                    storeMaxLight(optValues.maxLight);
                    state_values = Val_MinLight;
                    break;
                case Val_MinLight:
                    storeMinLight(optValues.minLight);
                    state_values = Val_MaxCO2;
                    break;
                case Val_MaxCO2:
                    storeMaxCO2(optValues.maxCO2);
                    state_values = Val_MinCO2;
                    break;
                case Val_MinCO2:
                    storeMinCO2(optValues.minCO2);
                    state_values = Val_MaxTemp;
                    state = State_Settings;
                    drawSettingsLayout(&display);
                    setActiveSettingsItem(&display, state_settings);
                    break;
                default:
                    state_values = Val_MaxTemp;
                    break;
                }

                if (state == State_Values)
                {
                    setActiveValuesItem(&display, state_values, &optValues);
                }
            }
            break;
        }
    }
}