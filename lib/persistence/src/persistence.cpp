#include "persistence.hpp"
#include <EEPROM.h>

void initPersistency()
{
    EEPROM.begin(EEPROM_SIZE);
}

void clearPersistency()
{
    EEPROM.write(MIN_TEMP_ADDR, 0xff);
    EEPROM.commit();
}

void storeMinTemp(uint8_t temp)
{
    EEPROM.write(MIN_TEMP_ADDR, temp);
    EEPROM.commit();
}

void storeMaxTemp(uint8_t temp)
{
    EEPROM.write(MAX_TEMP_ADDR, temp);
    EEPROM.commit();
}

void storeMinHumidity(uint8_t humidity)
{
    EEPROM.write(MIN_HUMIDITY_ADDR, humidity);
    EEPROM.commit();
}

void storeMaxHumidity(uint8_t humidity)
{
    EEPROM.write(MAX_HUMIDITY_ADDR, humidity);
    EEPROM.commit();
}

void storeMinLight(uint16_t light)
{
    EEPROM.write(MIN_LIGHT_ADDR, (light >> 8));
    EEPROM.write(MIN_LIGHT_ADDR + 1, (light & 0xFF));
    EEPROM.commit();
}

void storeMaxLight(uint16_t light)
{
    EEPROM.write(MAX_LIGHT_ADDR, (light >> 8));
    EEPROM.write(MAX_LIGHT_ADDR + 1, (light & 0xFF));
    EEPROM.commit();
}

void storeMinCO2(uint16_t co2)
{
    EEPROM.write(MIN_CO2_ADDR, (co2 >> 8));
    EEPROM.write(MIN_CO2_ADDR + 1, (co2 & 0xFF));
    EEPROM.commit();
}

void storeMaxCO2(uint16_t co2)
{
    EEPROM.write(MAX_CO2_ADDR, (co2 >> 8));
    EEPROM.write(MAX_CO2_ADDR + 1, (co2 & 0xFF));
    EEPROM.commit();
}

uint8_t retrieveMinTemp()
{
    return EEPROM.read(MIN_TEMP_ADDR);
}

uint8_t retrieveMaxTemp()
{
    return EEPROM.read(MAX_TEMP_ADDR);
}

uint8_t retrieveMinHumidity()
{
    return EEPROM.read(MIN_HUMIDITY_ADDR);
}

uint8_t retrieveMaxHumidity()
{
    return EEPROM.read(MAX_HUMIDITY_ADDR);
}

uint16_t retrieveMinLight()
{
    uint8_t msb = EEPROM.read(MIN_LIGHT_ADDR);
    uint8_t lsb = EEPROM.read(MIN_LIGHT_ADDR + 1);
    return (msb << 8) + lsb;
}

uint16_t retrieveMaxLight()
{
    uint8_t msb = EEPROM.read(MAX_LIGHT_ADDR);
    uint8_t lsb = EEPROM.read(MAX_LIGHT_ADDR + 1);
    return (msb << 8) + lsb;
}

uint16_t retrieveMinCO2()
{
    uint8_t msb = EEPROM.read(MIN_CO2_ADDR);
    uint8_t lsb = EEPROM.read(MIN_CO2_ADDR + 1);
    return (msb << 8) + lsb;
}

uint16_t retrieveMaxCO2()
{
    uint8_t msb = EEPROM.read(MAX_CO2_ADDR);
    uint8_t lsb = EEPROM.read(MAX_CO2_ADDR + 1);
    return (msb << 8) + lsb;
}

void storeWlanSsid(char ssid[32])
{
    for (uint8_t i = 0; i < 32; i++)
    {
        EEPROM.write(WLAN_SSID_ADDR + i, ssid[i]);
    }
    EEPROM.commit();
}

void storeWlanPassword(char password[63])
{
    for (uint8_t i = 0; i < 63; i++)
    {
        EEPROM.write(WLAN_PW_ADDR + i, password[i]);
    }
    EEPROM.commit();
}

void retrieveWlanSsid(char *ssid)
{
    for (uint8_t i = 0; i < 32; i++)
    {
        ssid[i] = EEPROM.read(WLAN_SSID_ADDR + i);
    }
}

void retrieveWlanPassword(char *password)
{
    for (uint8_t i = 0; i < 63; i++)
    {
        password[i] = EEPROM.read(WLAN_PW_ADDR + i);
    }
}

void storeGrafanaUrl(char url[255])
{
    for (uint8_t i = 0; i < 255; i++)
    {
        EEPROM.write(GRAFANA_URL_ADDR + i, url[i]);
    }
    EEPROM.commit();
}

void retrieveGrafanaUrl(char *url)
{
    for (uint8_t i = 0; i < 255; i++)
    {
        url[i] = EEPROM.read(GRAFANA_URL_ADDR + i);
    }
}

void storeTimer(uint8_t minutes, uint8_t seconds)
{
    EEPROM.write(TIMER_MIN_ADDR, minutes);
    EEPROM.write(TIMER_SEC_ADDR, seconds);
    EEPROM.commit();
}

uint8_t retrieveTimerMinutes()
{
    return EEPROM.read(TIMER_MIN_ADDR);
}

uint8_t retrieveTimerSeconds()
{
    return EEPROM.read(TIMER_SEC_ADDR);
}

void storeCustomName(char custom_name[50])
{
    for (uint8_t i = 0; i < 50; i++)
    {
        EEPROM.write(CUSTOM_NAME_ADDR + i, custom_name[i]);
    }
    EEPROM.commit();
}

void retrieveCustomName(char *custom_name)
{
    for (uint8_t i = 0; i < 50; i++)
    {
        custom_name[i] = EEPROM.read(CUSTOM_NAME_ADDR + i);
    }
}