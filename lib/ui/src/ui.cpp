#include <string.h>
#include "ui.hpp"

// Bitmaps for symbols
#define SYMBOL_ROWS 15
#define SYMBOL_COLS 11

int ARROW_UP[SYMBOL_ROWS][SYMBOL_COLS] = {
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
};

int ARROW_DOWN[SYMBOL_ROWS][SYMBOL_COLS] = {
    {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
};

int TICK[SYMBOL_ROWS][SYMBOL_COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int CROSS[SYMBOL_ROWS][SYMBOL_COLS] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int BATTERY[SYMBOL_ROWS][SYMBOL_COLS] = {
    {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
};

char buf[10];
int x, y, w, h;
char *TEMP_HIGH_TEXT = "! Heizung abschalten / Fenster oeffnen";
char *TEMP_LOW_TEXT = "! Heizung einschalten / Fenster schliessen";
char *HUM_HIGH_TEXT = "! Durchzug herstellen";
char *HUM_LOW_TEXT = "! Durchzug herstellen";
char *LIGHT_HIGH_TEXT = "! Licht dimmen";
char *LIGHT_LOW_TEXT = "! Licht einschalten";
char *AIR_QUALITY_LOW = "! Fenster oeffnen & lueften";

void drawArray(Display *display, uint16_t x, uint16_t y, int data[SYMBOL_ROWS][SYMBOL_COLS], uint16_t color)
{
    for (int row = 0; row < SYMBOL_ROWS; row++)
    {
        for (int col = 0; col < SYMBOL_COLS; col++)
        {
            if (data[row][col] == 1)
            {
                display->drawPixel(x + col, y + row, color);
            }
        }
    }
}

void setActiveValuesItem(Display *display, States_Values option, OptValues_t *optValues)
{
    display->setTextSize(2);
    display->firstPage();

    if (option == Val_MaxTemp)
    {
        display->setPartialWindow(5, 55, 67, 25);
        do
        {
            display->fillRect(5, 55, 67, 25, GxEPD_BLACK);
            display->setTextColor(GxEPD_WHITE);
            display->setCursor(23, 60);
            display->print(optValues->maxTemp);

            drawArray(display, 8, 60, ARROW_UP, GxEPD_WHITE);
        } while (display->nextPage());
    }

    if (option == Val_MinTemp)
    {
        display->setPartialWindow(5, 55, 67, 25);
        do
        {
            display->fillRect(5, 55, 67, 25, GxEPD_WHITE);
            display->setTextColor(GxEPD_BLACK);
            display->setCursor(23, 60);
            display->print(optValues->maxTemp);

            drawArray(display, 8, 60, ARROW_UP, GxEPD_BLACK);
        } while (display->nextPage());

        display->setPartialWindow(5, 90, 67, 25);
        do
        {
            display->fillRect(5, 90, 67, 25, GxEPD_BLACK);
            display->setTextColor(GxEPD_WHITE);
            display->setCursor(23, 95);
            display->print(optValues->minTemp);
            drawArray(display, 8, 95, ARROW_DOWN, GxEPD_WHITE);
        } while (display->nextPage());
    }

    if (option == Val_MaxHum)
    {
        display->setPartialWindow(5, 90, 67, 25);
        do
        {
            display->fillRect(5, 90, 67, 25, GxEPD_WHITE);
            display->setTextColor(GxEPD_BLACK);
            display->setCursor(23, 95);
            display->print(optValues->minTemp);
            drawArray(display, 8, 95, ARROW_DOWN, GxEPD_BLACK);
        } while (display->nextPage());

        display->setPartialWindow(79, 55, 67, 25);
        do
        {
            display->fillRect(79, 55, 67, 25, GxEPD_BLACK);
            display->setTextColor(GxEPD_WHITE);
            display->setCursor(97, 60);
            display->print(optValues->maxHum);

            drawArray(display, 82, 60, ARROW_UP, GxEPD_WHITE);
        } while (display->nextPage());
    }

    if (option == Val_MinHum)
    {
        display->setPartialWindow(79, 55, 67, 25);
        do
        {
            display->fillRect(79, 55, 67, 25, GxEPD_WHITE);
            display->setTextColor(GxEPD_BLACK);
            display->setCursor(97, 60);
            display->print(optValues->maxHum);

            drawArray(display, 82, 60, ARROW_UP, GxEPD_BLACK);
        } while (display->nextPage());

        display->setPartialWindow(79, 90, 67, 25);
        do
        {
            display->fillRect(79, 90, 67, 25, GxEPD_BLACK);
            display->setTextColor(GxEPD_WHITE);
            display->setCursor(97, 95);
            display->print(optValues->minHum);
            drawArray(display, 82, 95, ARROW_DOWN, GxEPD_WHITE);
        } while (display->nextPage());
    }

    if (option == Val_MaxLight)
    {
        display->setPartialWindow(79, 90, 67, 25);
        do
        {
            display->fillRect(79, 90, 67, 25, GxEPD_WHITE);
            display->setTextColor(GxEPD_BLACK);
            display->setCursor(97, 95);
            display->print(optValues->minHum);
            drawArray(display, 82, 95, ARROW_DOWN, GxEPD_BLACK);
        } while (display->nextPage());

        display->setPartialWindow(153, 55, 67, 25);
        do
        {
            display->fillRect(153, 55, 67, 25, GxEPD_BLACK);
            display->setTextColor(GxEPD_WHITE);
            display->setCursor(171, 60);
            display->print(optValues->maxLight);

            drawArray(display, 156, 60, ARROW_UP, GxEPD_WHITE);
        } while (display->nextPage());
    }

    if (option == Val_MinLight)
    {
        display->setPartialWindow(153, 55, 67, 25);
        do
        {
            display->fillRect(153, 55, 67, 25, GxEPD_WHITE);
            display->setTextColor(GxEPD_BLACK);
            display->setCursor(171, 60);
            display->print(optValues->maxLight);

            drawArray(display, 156, 60, ARROW_UP, GxEPD_BLACK);
        } while (display->nextPage());

        display->setPartialWindow(153, 90, 67, 25);
        do
        {
            display->fillRect(153, 90, 67, 25, GxEPD_BLACK);
            display->setTextColor(GxEPD_WHITE);
            display->setCursor(171, 95);
            display->print(optValues->minLight);
            drawArray(display, 156, 95, ARROW_DOWN, GxEPD_WHITE);
        } while (display->nextPage());
    }

    if (option == Val_MaxCO2)
    {
        display->setPartialWindow(153, 90, 67, 25);
        do
        {
            display->fillRect(153, 90, 67, 25, GxEPD_WHITE);
            display->setTextColor(GxEPD_BLACK);
            display->setCursor(171, 95);
            display->print(optValues->minLight);
            drawArray(display, 156, 95, ARROW_DOWN, GxEPD_BLACK);
        } while (display->nextPage());

        display->setPartialWindow(227, 55, 67, 25);
        do
        {
            display->fillRect(227, 55, 67, 25, GxEPD_BLACK);
            display->setTextColor(GxEPD_WHITE);
            display->setCursor(245, 60);
            display->print(optValues->maxCO2);

            drawArray(display, 230, 60, ARROW_UP, GxEPD_WHITE);
        } while (display->nextPage());
    }

    if (option == Val_MinCO2)
    {
        display->setPartialWindow(227, 55, 67, 25);
        do
        {
            display->fillRect(227, 55, 67, 25, GxEPD_WHITE);
            display->setTextColor(GxEPD_BLACK);
            display->setCursor(245, 60);
            display->print(optValues->maxCO2);

            drawArray(display, 230, 60, ARROW_UP, GxEPD_BLACK);
        } while (display->nextPage());

        display->setPartialWindow(227, 90, 67, 25);
        do
        {
            display->fillRect(227, 90, 67, 25, GxEPD_BLACK);
            display->setTextColor(GxEPD_WHITE);
            display->setCursor(245, 95);
            display->print(optValues->minCO2);
            drawArray(display, 230, 95, ARROW_DOWN, GxEPD_WHITE);
        } while (display->nextPage());
    }
}

void setActiveSettingsItem(Display *display, States_Settings option)
{
    display->setTextSize(1);
    display->setTextColor(GxEPD_BLACK);

    if (option == Settings_Timer)
    {
        display->firstPage();
        display->setPartialWindow(2, 33, 200, 8);
        do
        {
            display->setCursor(2, 33);
            display->print("WLAN konfigurieren");
        } while (display->nextPage());
    }

    if (option == Settings_WLAN || option == Settings_Values)
    {
        display->firstPage();
        display->setPartialWindow(2, 60, 200, 8);
        do
        {
            display->setCursor(2, 60);
            display->print("Timer konfigurieren");
        } while (display->nextPage());
    }

    if (option == Settings_Timer || option == Settings_Home)
    {
        display->firstPage();
        display->setPartialWindow(2, 86, 200, 8);
        do
        {
            display->setCursor(2, 86);
            display->print("Optimalwerte konfigurieren");
        } while (display->nextPage());
    }

    if (option == Settings_Values)
    {
        display->firstPage();
        display->setPartialWindow(2, 112, 200, 8);
        do
        {
            display->setCursor(2, 112);
            display->print("Zurueck zum Startbildschirm");
        } while (display->nextPage());
    }

    switch (option)
    {
    case Settings_Timer:
        display->setPartialWindow(2, 60, 200, 8);

        display->firstPage();
        do
        {
            display->setCursor(2, 60);
            display->print("> Timer konfigurieren");
        } while (display->nextPage());
        break;

    case Settings_Values:
        display->setPartialWindow(2, 86, 200, 8);

        display->firstPage();
        do
        {
            display->setCursor(2, 86);
            display->print("> Optimalwerte konfigurieren");
        } while (display->nextPage());
        break;

    case Settings_Home:
        display->setPartialWindow(2, 112, 200, 8);

        display->firstPage();
        do
        {
            display->setCursor(2, 112);
            display->print("> Zurueck zum Startbildschirm");
        } while (display->nextPage());
        break;

    default:
        display->setPartialWindow(2, 33, 200, 8);

        display->firstPage();
        do
        {
            display->setCursor(2, 33);
            display->print("> WLAN konfigurieren");
        } while (display->nextPage());

        break;
    }

    display->setTextColor(GxEPD_BLACK);
}

void setupDisplay(Display *display)
{
    display->init();
    display->setRotation(1);
    display->setTextColor(GxEPD_BLACK);
}

void drawHomeLayout(Display *display)
{
    display->setFullWindow();
    display->clearScreen();
    display->firstPage();
    display->setTextColor(GxEPD_BLACK);
    do
    {
        display->drawLine(0, 24, 296, 24, GxEPD_BLACK);
        display->drawLine(0, 76, 296, 76, GxEPD_BLACK);

        display->drawLine(74, 26, 74, 124, GxEPD_BLACK);
        display->drawLine(148, 26, 148, 124, GxEPD_BLACK);
        display->drawLine(222, 26, 222, 124, GxEPD_BLACK);

        display->setTextSize(2);
        display->setCursor(2, 2);
        display->print("Homeoffice Guard");

        display->setTextSize(1);
        display->setCursor(5, 28);
        display->print("Temperatur");

        display->setCursor(20, 80);
        display->print("Licht");

        display->setCursor(76, 28);
        display->print("Feuchtigkeit");

        display->setCursor(82, 80);
        display->print("CO2-Gehalt");

        display->setCursor(160, 28);
        display->print("Sensoren");

        display->setCursor(160, 80);
        display->print("Batterie");

        display->setCursor(250, 28);
        display->print("WLAN");

        display->setCursor(232, 80);
        display->print("Fehlercode");
    } while (display->nextPage());
}

void drawSettingsLayout(Display *display)
{
    display->setFullWindow();
    display->clearScreen();
    display->firstPage();
    display->setTextColor(GxEPD_BLACK);
    do
    {
        display->drawLine(0, 24, 296, 24, GxEPD_BLACK);
        display->drawLine(0, 51, 296, 51, GxEPD_BLACK);
        display->drawLine(0, 77, 296, 77, GxEPD_BLACK);
        display->drawLine(0, 103, 296, 103, GxEPD_BLACK);

        display->setTextSize(2);
        display->setCursor(2, 2);
        display->print("Einstellungen");

        display->setTextSize(1);
        display->setCursor(2, 33);
        display->print("WLAN konfigurieren");

        display->setCursor(2, 60);
        display->print("Timer konfigurieren");

        display->setCursor(2, 86);
        display->print("Optimalwerte konfigurieren");

        display->setCursor(2, 112);
        display->print("Zurueck zum Startbildschirm");
    } while (display->nextPage());
}

void drawValuesLayout(Display *display, OptValues_t *optValues)
{
    display->setFullWindow();
    display->clearScreen();
    display->firstPage();
    display->setTextColor(GxEPD_BLACK);
    do
    {
        display->drawLine(0, 24, 296, 24, GxEPD_BLACK);
        display->drawLine(74, 26, 74, 128, GxEPD_BLACK);
        display->drawLine(148, 26, 148, 128, GxEPD_BLACK);
        display->drawLine(222, 26, 222, 128, GxEPD_BLACK);

        display->setTextSize(2);
        display->setCursor(2, 2);
        display->print("Optimalwerte aendern");

        display->setTextSize(1);
        display->setCursor(5, 28);
        display->print("Temperatur");
        display->setCursor(5, 38);
        display->print("in Celcius");

        display->setCursor(76, 28);
        display->print("Feuchtigkeit");
        display->setCursor(100, 38);
        display->print("in %");

        display->setCursor(170, 28);
        display->print("Licht");
        display->setCursor(167, 38);
        display->print("in Lux");

        display->setCursor(230, 28);
        display->print("CO2-Gehalt");
        display->setCursor(240, 38);
        display->print("in VOC");

        display->setTextSize(2);
        display->setTextColor(GxEPD_BLACK);

        display->setCursor(23, 60);
        display->print(optValues->maxTemp);
        display->setCursor(23, 95);
        display->print(optValues->minTemp);

        display->setCursor(97, 60);
        display->print(optValues->maxHum);
        display->setCursor(97, 95);
        display->print(optValues->minHum);

        display->setCursor(171, 60);
        display->print(optValues->maxLight);
        display->setCursor(171, 95);
        display->print(optValues->minLight);

        display->setCursor(245, 60);
        display->print(optValues->maxCO2);
        display->setCursor(245, 95);
        display->print(optValues->minCO2);

        drawArray(display, 8, 60, ARROW_UP, GxEPD_BLACK);
        drawArray(display, 8, 95, ARROW_DOWN, GxEPD_BLACK);

        drawArray(display, 82, 60, ARROW_UP, GxEPD_BLACK);
        drawArray(display, 82, 95, ARROW_DOWN, GxEPD_BLACK);

        drawArray(display, 156, 60, ARROW_UP, GxEPD_BLACK);
        drawArray(display, 156, 95, ARROW_DOWN, GxEPD_BLACK);

        drawArray(display, 230, 60, ARROW_UP, GxEPD_BLACK);
        drawArray(display, 230, 95, ARROW_DOWN, GxEPD_BLACK);
    } while (display->nextPage());
}

void drawWlanLayout(Display *display)
{
    display->setFullWindow();
    display->clearScreen();
    display->firstPage();
    display->setTextColor(GxEPD_BLACK);
    do
    {
        display->drawLine(0, 24, 296, 24, GxEPD_BLACK);

        display->setTextSize(2);
        display->setCursor(2, 2);
        display->print("WLAN konfigurieren");

        display->setCursor(90, 50);
        display->print("Laden...");
    } while (display->nextPage());
}

void updateWlanIP(Display *display, IPAddress *ip)
{
    display->firstPage();
    display->setPartialWindow(20, 40, 250, 100);
    do
    {
        display->setTextSize(1);
        display->setCursor(20, 40);
        display->print("1. Verbinden dich zum \"Homeoffice Guard\"-Netzwerk");
        display->setCursor(20, 60);
        display->print("2. Oeffne die folgende Adresse im Browser");
        display->setCursor(20, 80);
        display->print("3. Verbinde dich wieder mit ihrem normalen WLAN");
        display->setTextSize(2);
        display->setCursor(80, 100);
        display->print(ip->toString());
    } while (display->nextPage());
}

void drawTimerLayout(Display *display, TimerValue_t *timerValue)
{
    display->setFullWindow();
    display->clearScreen();
    display->firstPage();
    display->setTextColor(GxEPD_BLACK);
    do
    {
        display->drawLine(0, 24, 296, 24, GxEPD_BLACK);

        display->setTextSize(2);
        display->setCursor(2, 2);
        display->print("Messabstand aendern");

        display->setTextSize(1);
        display->setCursor(98, 55);
        display->print("Minuten:Sekunden");

        display->setTextSize(3);
        display->setCursor(100, 70);
        char buf[6];
        snprintf(buf, 6, "%02d:%02d", timerValue->minutes, timerValue->seconds);
        display->print(buf);

        display->fillRect(100, 100, 35, 5, GxEPD_BLACK);
    } while (display->nextPage());
}

void updateTimerValue(Display *display, TimerValue_t *timerValue, uint8_t min_selected)
{
    display->firstPage();
    display->setPartialWindow(100, 70, 150, 70);
    do
    {
        display->fillRect(100, 100, 150, 5, GxEPD_WHITE);
        if (min_selected)
        {
            display->fillRect(100, 100, 35, 5, GxEPD_BLACK);
        }
        else
        {
            display->fillRect(152, 100, 35, 5, GxEPD_BLACK);
        }

        char buf[6];
        display->setTextSize(3);
        display->setCursor(100, 70);
        snprintf(buf, 6, "%02d:%02d", timerValue->minutes, timerValue->seconds);
        display->print(buf);
    } while (display->nextPage());
}

void updateHomeValues(Display *display, Measurements_t *measurements, uint8_t dataType)
{
    display->setTextSize(2);
    display->setTextColor(GxEPD_BLACK);

    if (dataType & (1 << 0))
    {
        display->firstPage();
        display->setPartialWindow(0, 45, 73, 25);
        do
        {
            snprintf(buf, 10, "%.0f", measurements->temperature);
            w = 16 * strlen(buf);
            display->setCursor((72 - w) / 2, 45);
            display->print(buf);
        } while (display->nextPage());

        dataType |= (0 << 0);
    }

    if (dataType & (1 << 1))
    {
        display->firstPage();
        display->setPartialWindow(75, 45, 73, 25);
        do
        {
            snprintf(buf, 10, "%.0f%%", measurements->humidity);
            w = 16 * strlen(buf);
            display->setCursor(75 + ((72 - w) / 2), 45);
            display->print(buf);
        } while (display->nextPage());

        dataType |= (0 << 1);
    }

    if (dataType & (1 << 2))
    {
        display->firstPage();
        display->setPartialWindow(0, 97, 73, 25);
        do
        {
            snprintf(buf, 10, "%.0flx", measurements->light);
            w = 16 * strlen(buf);
            if ((72 - w) / 2 < 0)
            {
                x = 0;
            }
            else
            {
                x = (72 - w) / 2;
            }

            display->setCursor(x, 97);
            display->print(buf);
        } while (display->nextPage());

        dataType |= (0 << 2);
    }

    if (dataType & (1 << 3))
    {
        display->firstPage();
        display->setPartialWindow(75, 97, 73, 25);
        do
        {
            snprintf(buf, 10, "%.0f VOC", measurements->co2);
            w = 16 * strlen(buf);
            if ((72 - w) / 2 < 0)
            {
                x = 0;
            }
            else
            {
                x = (72 - w) / 2;
            }
            display->setCursor(75 + x, 97);
            display->print(buf);
        } while (display->nextPage());

        dataType |= (0 << 3);
    }

    if (dataType & (1 << 4))
    {

        display->firstPage();
        display->setPartialWindow(175, 45, 20, 20);
        do
        {
            if (measurements->sensor_status)
            {
                drawArray(display, 175, 45, TICK, GxEPD_BLACK);
            }
            else
            {
                drawArray(display, 175, 45, CROSS, GxEPD_BLACK);
            }
        } while (display->nextPage());
    }

    if (dataType & (1 << 5))
    {
        display->firstPage();
        display->setPartialWindow(255, 45, 20, 20);
        do
        {
            if (measurements->wlan_status)
            {
                drawArray(display, 255, 45, TICK, GxEPD_BLACK);
            }
            else
            {
                drawArray(display, 255, 45, CROSS, GxEPD_BLACK);
            }
        } while (display->nextPage());

        display->firstPage();
        display->setPartialWindow(240, 97, 50, 30);
        display->setCursor(240, 97);
        do
        {
            display->print(measurements->error_code);
        } while (display->nextPage());

        dataType |= (0 << 5);
    }

    if (dataType & (1 << 6))
    {
        display->firstPage();
        display->setPartialWindow(155, 97, 65, 25);
        do
        {
            display->setCursor(155, 97);
            snprintf(buf, 5, "%d%%", measurements->battery_level);
            display->print(buf);
            drawArray(display, 205, 97, BATTERY, GxEPD_BLACK);
        } while (display->nextPage());

        display->firstPage();
        display->setPartialWindow(240, 97, 50, 30);
        display->setCursor(240, 97);
        do
        {
            display->print(measurements->error_code);
        } while (display->nextPage());

        dataType |= (0 << 6);
    }
}

void drawMeasurement(Display *display, MeasurementType_t measurement_type)
{
    display->setPartialWindow(30, 60, 235, 37);
    display->firstPage();
    do
    {
        display->fillRect(30, 60, 235, 37, GxEPD_WHITE);
        display->drawRect(30, 60, 235, 37, GxEPD_BLACK);
        display->setCursor(35, 70);

        switch (measurement_type)
        {
        case TempHigh:
            display->print(TEMP_HIGH_TEXT);
            break;
        case TempLow:
            display->print(TEMP_LOW_TEXT);
            break;
        case HumidityHigh:
            display->print(HUM_HIGH_TEXT);
            break;
        case HumidityLow:
            display->print(HUM_LOW_TEXT);
            break;
        case LightHigh:
            display->print(LIGHT_HIGH_TEXT);
            break;
        case LightLow:
            display->print(LIGHT_LOW_TEXT);
            break;
        case Co2Bad:
            display->print(AIR_QUALITY_LOW);
            break;
        }
    } while (display->nextPage());
}

void drawWlanActive(Display *display, uint8_t wlan_disconnect_yes)
{
    display->firstPage();
    display->setPartialWindow(40, 50, 250, 60);
    do
    {
        display->setTextSize(1);
        display->setCursor(65, 50);
        display->print("WLAN verbunden. Beenden?");

        display->setTextSize(2);
        display->setCursor(100, 70);
        display->print("Ja");
        display->setCursor(145, 70);
        display->print("Nein");

        display->fillRect(70, 90, 100, 5, GxEPD_WHITE);
        if (wlan_disconnect_yes)
        {
            display->fillRect(100, 90, 20, 5, GxEPD_BLACK);
        }
        else
        {
            display->fillRect(145, 90, 50, 5, GxEPD_BLACK);
        }
    } while (display->nextPage());
}