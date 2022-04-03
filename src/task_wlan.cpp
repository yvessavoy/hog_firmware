#include <WiFi.h>
#include <string.h>
#include "task_wlan.hpp"
#include "main.hpp"
#include "utils.hpp"
#include "persistence.hpp"

WiFiServer server(80);
char header[500];
uint16_t header_idx;
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

char ssid[32];
char password[63];
char grafana_url[255];
char custom_name[50];
char d_ssid[32];
char d_password[63];
char s_ssid[32];
char s_password[63];
char d_grafana_url[255];
char d_custom_name[50];
uint8_t details_received = 0;

const char *html =
    "<!DOCTYPE html><html>"
    "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}</style></head>"
    "<body><h1>Homeoffice Guard</h1>"
    "<form method=\"GET\">"
    "<p>WLAN Name</p>"
    "<input name=\"wlan_name\" type=\"text\">"
    "<p>WLAN Passwort</p>"
    "<input name=\"wlan_password\" type=\"password\">"
    "<p>Grafana Server URL</p>"
    "<input name=\"grafana_url\" type=\"text\">"
    "<p>Benutzerdefinierter Geraetename</p>"
    "<input name=\"custom_name\" type=\"text\">"
    "<p></p>"
    "<input type=\"Submit\" value=\"Senden\">"
    "</form>"
    "</body></html>";

const char *ok_html =
    "<!DOCTYPE html><html>"
    "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"
    "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}</style></head>"
    "<body><h1>Homeoffice Guard</h1>"
    "<p>Verbindung wird hergestellt. Du kannst diese Seite schliessen!</p>"
    "</body></html>";

void vTaskWlan(void *pvParameters)
{
    // Setup wlan connection if previously enabled
    retrieveWlanSsid(s_ssid);
    retrieveWlanPassword(s_password);
    if (s_ssid[0] != '\0')
    {
        WiFi.begin(s_ssid, s_password);
        vTaskDelay(10000 / portTICK_PERIOD_MS);
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.print("WiFi-Connection failed: ");
            Serial.println(WiFi.status());
        }
        else
        {
            xEventGroupSetBits(xEventGroup, WLAN_OK_BIT);
        }
    }

    for (;;)
    {
        xEventGroupWaitBits(xEventGroup, WLAN_START_BIT, pdTRUE, pdTRUE, portMAX_DELAY);

        WiFi.softAP("Homeoffice Guard", NULL);
        vTaskDelay(500 / portTICK_PERIOD_MS);
        ap_ip = WiFi.softAPIP();
        server.begin();
        xEventGroupSetBits(xEventGroup, AP_IP_AVAILABLE_BIT);

        for (;;)
        {
            WiFiClient client = server.available();

            if (client)
            {
                currentTime = millis();
                previousTime = currentTime;
                String currentLine = ""; // make a String to hold incoming data from the client
                header_idx = 0;
                while (client.connected() && currentTime - previousTime <= timeoutTime)
                { // loop while the client's connected
                    currentTime = millis();
                    if (client.available())
                    {                           // if there's bytes to read from the client,
                        char c = client.read(); // read a byte, then
                        Serial.write(c);        // print it out the serial monitor
                        header[header_idx] = c;
                        header_idx++;
                        if (c == '\n')
                        { // if the byte is a newline character
                            // if the current line is blank, you got two newline characters in a row.
                            // that's the end of the client HTTP request, so send a response:
                            if (currentLine.length() == 0)
                            {
                                // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                                // and a content-type so the client knows what's coming, then a blank line:
                                client.println("HTTP/1.1 200 OK");
                                client.println("Content-type:text/html");
                                client.println("Connection: close");
                                client.println();

                                if (strstr(header, "/?"))
                                {
                                    client.println(ok_html);

                                    getSsidFromGetRequest(header, ssid);
                                    getPasswordFromGetRequest(header, password);
                                    getGrafanaUrlFromGetRequest(header, grafana_url);
                                    getCustomNameFromGetRequest(header, custom_name);

                                    html_decode(ssid, d_ssid);
                                    html_decode(password, d_password);
                                    html_decode(grafana_url, d_grafana_url);
                                    html_decode(custom_name, d_custom_name);

                                    storeWlanSsid(d_ssid);
                                    storeWlanPassword(d_password);
                                    storeGrafanaUrl(d_grafana_url);
                                    storeCustomName(d_custom_name);

                                    details_received = 1;
                                }
                                else
                                {
                                    client.println(html);
                                }

                                // The HTTP response ends with another blank line
                                client.println();
                                // Break out of the while loop
                                break;
                            }
                            else
                            { // if you got a newline, then clear currentLine
                                currentLine = "";
                            }
                        }
                        else if (c != '\r')
                        {                     // if you got anything else but a carriage return character,
                            currentLine += c; // add it to the end of the currentLine
                        }
                    }
                }
            }

            if (details_received)
            {
                client.flush();
                client.stop();
                server.end();
                WiFi.softAPdisconnect(true);
                break;
            }
        }

        WiFi.begin(ssid, password);
        vTaskDelay(8000 / portTICK_PERIOD_MS);
        if (WiFi.status() != WL_CONNECTED)
        {
            Serial.print("WLAN connection failed: ");
            Serial.println(WiFi.status());
        }
        else
        {
            xEventGroupSetBits(xEventGroup, WLAN_OK_BIT);
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}