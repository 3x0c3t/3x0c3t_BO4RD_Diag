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

    // Cadre de progression
    int barX = 40;
    int barY = 230;
    int barW = TFT_WIDTH - 80;
    int barH = 10;

    tft.drawRect(
        barX,
        barY,
        barW,
        barH,
        SPLASH_TEXT_COLOR
    );

    // Progression
    tft.fillRect(
        barX + 2,
        barY + 2,
        barW - 4,
        barH - 4,
        SPLASH_TEXT_COLOR
    );
}

void splashWait()
{
    delay(SPLASH_DURATION_MS);
}