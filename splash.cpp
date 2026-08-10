#include "splash.h"
#include "personalization.h"
#include "display_config.h"

void splashInit(TFT_eSPI &tft)
{
    tft.fillScreen(SPLASH_BACKGROUND);
}

void splashShow(TFT_eSPI &tft)
{
    tft.fillScreen(SPLASH_BACKGROUND);

    tft.setTextColor(SPLASH_TEXT_COLOR, SPLASH_BACKGROUND);
    tft.setTextDatum(MC_DATUM);

    tft.setTextSize(3);
    tft.drawString(
        SPLASH_TITLE,
        TFT_WIDTH / 2,
        110
    );

    tft.setTextSize(2);
    tft.drawString(
        SPLASH_SUBTITLE,
        TFT_WIDTH / 2,
        150
    );

    tft.setTextSize(1);
    tft.drawString(
        SPLASH_VERSION,
        TFT_WIDTH / 2,
        190
    );

    // BARRE SYSTEME | Position standardisee
    tft.fillRect(
        SYSTEM_BAR_X,
        SYSTEM_BAR_Y,
        SYSTEM_BAR_WIDTH,
        SYSTEM_BAR_HEIGHT,
        SYSTEM_BAR_COLOR
    );
}

void splashWait()
{
    delay(SPLASH_DURATION_MS);
}