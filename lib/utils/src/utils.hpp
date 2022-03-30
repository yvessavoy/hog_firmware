#ifndef _UTILS_H
#define _UTILS_H

void getSsidFromGetRequest(char *request, char *ssid);
void getPasswordFromGetRequest(char *request, char *password);
void getGrafanaUrlFromGetRequest(char *request, char *url);
void html_decode(char *source, char *target);

int isInUpperLowerPercentage(int val, int min, int max);

#endif