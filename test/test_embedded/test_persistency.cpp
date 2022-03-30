#include <Arduino.h>
#include <unity.h>
#include "persistence.hpp"

void test_store_and_get_temperature()
{
    uint8_t min_temp = 5;
    uint8_t max_temp = 10;

    storeMinTemp(min_temp);
    TEST_ASSERT_EQUAL(min_temp, retrieveMinTemp());

    storeMaxTemp(max_temp);
    TEST_ASSERT_EQUAL(max_temp, retrieveMaxTemp());
}

void test_store_and_get_humidity()
{
    uint8_t min_humidity = 10;
    uint8_t max_humidity = 80;

    storeMinHumidity(min_humidity);
    TEST_ASSERT_EQUAL(min_humidity, retrieveMinHumidity());

    storeMaxHumidity(max_humidity);
    TEST_ASSERT_EQUAL(max_humidity, retrieveMaxHumidity());
}

void test_store_and_get_light()
{
    uint16_t min_light = 700;
    uint16_t max_light = 9999;

    storeMinLight(min_light);
    TEST_ASSERT_EQUAL(min_light, retrieveMinLight());

    storeMaxLight(max_light);
    TEST_ASSERT_EQUAL(max_light, retrieveMaxLight());
}

void test_store_and_get_co2()
{
    uint16_t min_co2 = 10;
    uint16_t max_co2 = 1500;

    storeMinCO2(min_co2);
    TEST_ASSERT_EQUAL(min_co2, retrieveMinCO2());

    storeMaxCO2(max_co2);
    TEST_ASSERT_EQUAL(max_co2, retrieveMaxCO2());
}

void test_store_and_get_wlan_ssid()
{
    char ssid[7] = "MyWLAN";
    char new_ssid[32];

    storeWlanSsid(ssid);
    retrieveWlanSsid(new_ssid);
    TEST_ASSERT_EQUAL_STRING(ssid, new_ssid);
}

void test_store_and_get_wlan_password()
{
    char password[8] = "Secure!";
    char new_password[63];

    storeWlanPassword(password);
    retrieveWlanPassword(new_password);
    TEST_ASSERT_EQUAL_STRING(password, new_password);
}

void test_store_and_get_grafana_url()
{
    char url[34] = "https://myserver.com/grafana:8080";
    char new_url[255];

    storeGrafanaUrl(url);
    retrieveGrafanaUrl(new_url);
    TEST_ASSERT_EQUAL_STRING(url, new_url);
}

void test_store_and_get_timer_values()
{
    uint8_t minutes = 15;
    uint8_t seconds = 49;

    storeTimer(minutes, seconds);
    TEST_ASSERT_EQUAL(minutes, retrieveTimerMinutes());
    TEST_ASSERT_EQUAL(seconds, retrieveTimerSeconds());
}

void setup()
{
    delay(2000);
    initPersistency();

    UNITY_BEGIN();
    RUN_TEST(test_store_and_get_temperature);
    RUN_TEST(test_store_and_get_humidity);
    RUN_TEST(test_store_and_get_light);
    RUN_TEST(test_store_and_get_co2);
    RUN_TEST(test_store_and_get_wlan_ssid);
    RUN_TEST(test_store_and_get_wlan_password);
    RUN_TEST(test_store_and_get_grafana_url);
    RUN_TEST(test_store_and_get_timer_values);
    UNITY_END();

    clearPersistency();
}

void loop()
{
}