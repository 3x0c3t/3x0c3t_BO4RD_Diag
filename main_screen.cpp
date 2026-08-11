#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display_config.h"
#include "personalization.h"
#include "main_screen.h"

void mainScreenShow(TFT_eSPI &tft)
{
    tft.fillScreen(TFT_BLACK);

    // BARRE SYSTEME | Zone standardisee utilisee par tous les ecrans

    tft.fillRect(
        SYSTEM_BAR_X,
        SYSTEM_BAR_Y,
        SYSTEM_BAR_WIDTH,
        SYSTEM_BAR_HEIGHT,
        SYSTEM_BAR_COLOR
    );

    // --------------------------------------------------------
    // ECRAN PRINCIPAL
    // --------------------------------------------------------

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(2);

    tft.drawString(
        "3x0c3t BO4RD",
        TFT_WIDTH / 2,
        80
    );

    tft.setTextSize(1);

    tft.drawString(
        "DIAGNOSTIC",
        TFT_WIDTH / 2,
        110
    );
}