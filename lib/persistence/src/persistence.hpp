#ifndef _PERSISTENCE_H
#define _PERSISTENCE_H

#include <stdint.h>

#define EEPROM_SIZE 419
#define WLAN_SSID_ADDR 0
#define WLAN_PW_ADDR 33
#define MIN_TEMP_ADDR 99
#define MAX_TEMP_ADDR 100
#define MIN_HUMIDITY_ADDR 101
#define MAX_HUMIDITY_ADDR 102
#define MIN_LIGHT_ADDR 103
#define MAX_LIGHT_ADDR 105
#define MIN_CO2_ADDR 107
#define MAX_CO2_ADDR 109
#define GRAFANA_URL_ADDR 111
#define TIMER_MIN_ADDR 367
#define TIMER_SEC_ADDR 368
#define CUSTOM_NAME_ADDR 369

void initPersistency();
void clearPersistency();

void storeMinTemp(uint8_t temp);
void storeMaxTemp(uint8_t temp);
void storeMinHumidity(uint8_t humidity);
void storeMaxHumidity(uint8_t humidity);
void storeMinLight(uint16_t light);
void storeMaxLight(uint16_t light);
void storeMinCO2(uint16_t co2);
void storeMaxCO2(uint16_t co2);
uint8_t retrieveMinTemp();
uint8_t retrieveMaxTemp();
uint8_t retrieveMinHumidity();
uint8_t retrieveMaxHumidity();
uint16_t retrieveMinLight();
uint16_t retrieveMaxLight();
uint16_t retrieveMinCO2();
uint16_t retrieveMaxCO2();

void storeWlanSsid(char ssid[32]);
void storeWlanPassword(char password[63]);
void retrieveWlanSsid(char *ssid);
void retrieveWlanPassword(char *password);

void storeGrafanaUrl(char url[255]);
void retrieveGrafanaUrl(char *url);

void storeTimer(uint8_t minutes, uint8_t seconds);
uint8_t retrieveTimerMinutes();
uint8_t retrieveTimerSeconds();

void storeCustomName(char custom_name[50]);
void retrieveCustomName(char *custom_name);

#endif