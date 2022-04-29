/*
Autor: Yves Savoy
Klassifizierung: Selbst erzeugt
*/

#ifndef _UI_H
#define _UI_H

#include <GxEPD2_BW.h>
#include <WiFi.h>

typedef GxEPD2_BW<GxEPD2_290_T94_V2, GxEPD2_290_T94_V2::HEIGHT> Display;

typedef enum
{
    Settings_WLAN,
    Settings_Timer,
    Settings_Values,
    Settings_Home,
} States_Settings;

typedef enum
{
    TempHigh,
    TempLow,
    HumidityHigh,
    HumidityLow,
    LightHigh,
    LightLow,
    Co2Bad,
    None
} MeasurementType_t;

typedef enum
{
    Val_MaxTemp,
    Val_MinTemp,
    Val_MaxHum,
    Val_MinHum,
    Val_MaxLight,
    Val_MinLight,
    Val_MaxCO2,
    Val_MinCO2
} States_Values;

typedef struct
{
    uint8_t minTemp;
    uint8_t maxTemp;
    uint8_t minHum;
    uint8_t maxHum;
    uint16_t minLight;
    uint16_t maxLight;
    uint16_t minCO2;
    uint16_t maxCO2;
} OptValues_t;

typedef struct
{
    uint8_t minutes;
    uint8_t seconds;
} TimerValue_t;

typedef struct
{
    float temperature;
    float humidity;
    float light;
    float co2;
    uint8_t sensor_status;
    uint8_t wlan_status;
    uint8_t battery_level;
    char error_code[5];
} Measurements_t;

// Setup the display (calls drawLayout for initialisation);
// Display-parameter has to be NULL for it to be initialized
void setupDisplay(Display *display);

// Draw the layout (lines, text, etc.) without any values; Overwrite anything currently on the screen
// Display-parameter needs to be initialized
void drawHomeLayout(Display *display);
void drawSettingsLayout(Display *display);
void drawValuesLayout(Display *display, OptValues_t *optValues);
void drawWlanLayout(Display *display);
void drawTimerLayout(Display *display, TimerValue_t *timerValue);

// Draw updated values
// Display-parameter needs to be initialized
void drawTemperature(Display *display, float temperature);
void drawHumidity(Display *display, float humidity);
void drawLight(Display *display, float light);
void drawCO2Density(Display *display, float co2);
void drawBatteryLevel(Display *display, int batteryLevel);
void drawWlanStatus(Display *display, int status);   // status = 0 -> Error / failed, status = 1 -> all OK
void drawSensorStatus(Display *display, int status); // status = 0 -> Error / failed, status = 1 -> all OK
void drawErrorCode(Display *display, char code[4]);
void clearErrorCode(Display *display);

// Menu moving
void setActiveSettingsItem(Display *display, States_Settings option);
void setActiveValuesItem(Display *display, States_Values option, OptValues_t *optValues);
void updateTimerValue(Display *display, TimerValue_t *timerValue, uint8_t min_selected);
void updateHomeValues(Display *display, Measurements_t *measurements, uint8_t dataType);
void updateWlanIP(Display *display, IPAddress *ip);
void drawWlanActive(Display *display, uint8_t wlan_disconnect_yes);
void drawMeasurement(Display *display, MeasurementType_t measurement_type);

#endif