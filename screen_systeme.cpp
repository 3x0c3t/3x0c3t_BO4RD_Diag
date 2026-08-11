#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display.h"
#include "display_config.h"
#include "screen_systeme.h"

void systemeScreenInit(TFT_eSPI &tft)
{
}

void systemeScreenShow(TFT_eSPI &tft)
{
    displayDrawFrame(
        tft,
        "SYSTEME",
        101
    );

    tft.setTextDatum(TL_DATUM);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString(
        "Systeme",
        10,
        90
    );

    tft.setTextSize(1);

    tft.drawString(
        "ESP8266",
        10,
        120
    );

    tft.drawString(
        "3x0c3t BO4RD",
        10,
        140
    );

    tft.drawString(
        "Version DIAG 2.0",
        10,
        160
    );
}

void systemeScreenLoop(TFT_eSPI &tft)
{
}