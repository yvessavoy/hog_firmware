/*
Autor: Yves Savoy
Klassifizierung: Selbst erzeugt
*/

#include <unity.h>
#include "utils.hpp"

char *request =
    "GET /?wlan_name=MySSID&wlan_password=MyPassword&grafana_url=https://grafana.com HTTP/1.1"
    "Host: 192.168.4.1"
    "User-Agent: Mozilla/5.0 (Android 12; Mobile; rv:98.0) Gecko/98.0 Firefox/98.0"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8"
    "Accept-Language: de-CH"
    "Accept-Encoding: gzip, deflate"
    "Connection: keep-alive"
    "Referer: http://192.168.4.1/"
    "Upgrade-Insecure-Requests: 1";

void test_get_ssid()
{
    char ssid[255];
    getSsidFromGetRequest(request, ssid);
    TEST_ASSERT_EQUAL_STRING("MySSID", ssid);
}

void test_get_password()
{
    char password[63];
    getPasswordFromGetRequest(request, password);
    TEST_ASSERT_EQUAL_STRING("MyPassword", password);
}

void test_get_grafana_url()
{
    char url[255];
    getGrafanaUrlFromGetRequest(request, url);
    TEST_ASSERT_EQUAL_STRING("https://grafana.com", url);
}

void test_percentage_lower()
{
    TEST_ASSERT_EQUAL(1, isInUpperLowerPercentage(5, 0, 100));
}

void test_percentage_higher()
{
    TEST_ASSERT_EQUAL(1, isInUpperLowerPercentage(46, 0, 50));
}

void test_percentage_lower_edge()
{
    TEST_ASSERT_EQUAL(0, isInUpperLowerPercentage(10, 0, 100));
}

void test_percentage_higher_edge()
{
    TEST_ASSERT_EQUAL(0, isInUpperLowerPercentage(90, 0, 100));
}

void test_percentage_not_in_range()
{
    TEST_ASSERT_EQUAL(0, isInUpperLowerPercentage(20, 0, 100));
}

void test_html_decode()
{
    char expected[50] = "http://192.168.1.3:3001";
    char actual[50];
    html_decode("http%3A%2F%2F192.168.1.3%3A3001", actual);
    TEST_ASSERT_EQUAL_STRING(expected, actual);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_get_ssid);
    RUN_TEST(test_get_password);
    RUN_TEST(test_get_grafana_url);
    RUN_TEST(test_percentage_lower);
    RUN_TEST(test_percentage_higher);
    RUN_TEST(test_percentage_lower_edge);
    RUN_TEST(test_percentage_higher_edge);
    RUN_TEST(test_percentage_not_in_range);
    RUN_TEST(test_html_decode);
    UNITY_END();

    return 0;
}