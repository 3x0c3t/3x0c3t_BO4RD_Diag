#include "display.h"
#include "display_config.h"

void displayInit(TFT_eSPI &tft)
{
    tft.init();
    tft.setRotation(TFT_ROTATION);
    tft.fillScreen(TFT_BLACK);
}

void displayDrawSystemBar(TFT_eSPI &tft)
{
    // BARRE SYSTEME | Zone standardisee utilisee par tous les ecrans
    tft.fillRect(
        SYSTEM_BAR_X,
        SYSTEM_BAR_Y,
        SYSTEM_BAR_WIDTH,
        SYSTEM_BAR_HEIGHT,
        SYSTEM_BAR_COLOR
    );
}