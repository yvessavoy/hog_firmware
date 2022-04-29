/*
Autor: Yves Savoy
Klassifizierung: Selbst erzeugt
*/

#include <string.h>
#include <ctype.h>
#include "utils.hpp"

#define PERCENTAGE 10

char *ptr;

char from_hex(char ch)
{
    return isdigit(ch) ? ch - '0' : tolower(ch) - 'a' + 10;
}

void html_decode(char *source, char *target)
{
    while (*source)
    {
        if (*source == '%')
        {
            if (source[1] && source[2])
            {
                *target++ = from_hex(source[1]) << 4 | from_hex(source[2]);
                source += 2;
            }
        }
        else if (*source == '+')
        {
            *target++ = ' ';
        }
        else
        {
            *target++ = *source;
        }
        source++;
    }
    *target = '\0';
}

int isInUpperLowerPercentage(int val, int min, int max)
{
    int range = max - min;
    float percentage_range = range / 100.0 * PERCENTAGE;
    if ((val < min + percentage_range) || (val > max - percentage_range))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void getSsidFromGetRequest(char *request, char *ssid)
{
    ptr = strstr(request, "wlan_name=") + 10;
    for (int i = 0; i < 32; i++)
    {
        if (*(ptr + i) == '&' || *(ptr + i) == ' ')
        {
            break;
        }
        ssid[i] = *(ptr + i);
    }
}
void getPasswordFromGetRequest(char *request, char *password)
{
    ptr = strstr(request, "wlan_password=") + 14;
    for (int i = 0; i < 63; i++)
    {
        if (*(ptr + i) == '&' || *(ptr + i) == ' ')
        {
            break;
        }
        password[i] = *(ptr + i);
    }
}
void getGrafanaUrlFromGetRequest(char *request, char *url)
{
    ptr = strstr(request, "grafana_url=") + 12;
    for (int i = 0; i < 255; i++)
    {
        if (*(ptr + i) == '&' || *(ptr + i) == ' ')
        {
            break;
        }
        url[i] = *(ptr + i);
    }
}

void getCustomNameFromGetRequest(char *request, char *name)
{
    ptr = strstr(request, "custom_name=") + 12;
    for (int i = 0; i < 50; i++)
    {
        if (*(ptr + i) == '&' || *(ptr + i) == ' ')
        {
            break;
        }
        name[i] = *(ptr + i);
    }
}