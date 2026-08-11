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

    // --------------------------------------------------------
    // BRAND
    // --------------------------------------------------------

    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(SPLASH_BRAND_SIZE);
    tft.setTextColor(
        SPLASH_BRAND_COLOR,
        SPLASH_BACKGROUND
    );

    tft.drawString(
        SPLASH_BRAND,
        TFT_WIDTH / 2,
        SPLASH_BRAND_Y
    );

    // --------------------------------------------------------
    // MOTTO
    // --------------------------------------------------------

    tft.setTextSize(SPLASH_MOTTO_SIZE);
    tft.setTextColor(
        SPLASH_MOTTO_COLOR,
        SPLASH_BACKGROUND
    );

    tft.drawString(
        SPLASH_MOTTO,
        TFT_WIDTH / 2,
        SPLASH_MOTTO_Y
    );

    // --------------------------------------------------------
    // LIGNE DECORATIVE
    // --------------------------------------------------------

    tft.fillRect(
        (TFT_WIDTH - SPLASH_LINE_WIDTH) / 2,
        SPLASH_LINE_Y,
        SPLASH_LINE_WIDTH,
        SPLASH_LINE_HEIGHT,
        SPLASH_LINE_COLOR
    );

    // --------------------------------------------------------
    // PROJECT
    // --------------------------------------------------------

    tft.setTextSize(SPLASH_PROJECT_SIZE);
    tft.setTextColor(
        SPLASH_PROJECT_COLOR,
        SPLASH_BACKGROUND
    );

    tft.drawString(
        SPLASH_PROJECT,
        TFT_WIDTH / 2,
        SPLASH_PROJECT_Y
    );

    // --------------------------------------------------------
    // VERSION
    // --------------------------------------------------------

    tft.setTextSize(SPLASH_VERSION_SIZE);
    tft.setTextColor(
        SPLASH_VERSION_COLOR,
        SPLASH_BACKGROUND
    );

    tft.drawString(
        DEVICE_VERSION,
        TFT_WIDTH / 2,
        SPLASH_VERSION_Y
    );

    // --------------------------------------------------------
    // DATE DE COMPILATION
    // --------------------------------------------------------

    tft.setTextColor(
        SPLASH_DATE_COLOR,
        SPLASH_BACKGROUND
    );

    tft.drawString(
        __DATE__,
        TFT_WIDTH / 2,
        SPLASH_DATE_Y
    );
}

void splashWait()
{
    delay(SPLASH_DURATION_MS);
}