#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display_config.h"
#include "display.h"
#include "screen_main.h"

static MainButton mainButtons[MAIN_BUTTON_COUNT] =
{
    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y,
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "SYSTEME",
        1
    },

    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y +
            ((MAIN_BUTTON_HEIGHT + MAIN_BUTTON_GAP) * 1),
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "WI-FI",
        2
    },

    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y +
            ((MAIN_BUTTON_HEIGHT + MAIN_BUTTON_GAP) * 2),
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "CARTE SD",
        3
    },

    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y +
            ((MAIN_BUTTON_HEIGHT + MAIN_BUTTON_GAP) * 3),
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "TACTILE",
        4
    },

    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y +
            ((MAIN_BUTTON_HEIGHT + MAIN_BUTTON_GAP) * 4),
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "DIAGNOSTICS",
        5
    }
};

void mainScreenInit(TFT_eSPI &tft)
{
}

static void drawMainButton(
    TFT_eSPI &tft,
    const MainButton &button
)
{
    tft.fillRect(
        button.x,
        button.y,
        button.width,
        button.height,
        TFT_BLACK
    );

    tft.drawRect(
        button.x,
        button.y,
        button.width,
        button.height,
        TFT_CYAN
    );

    tft.setTextColor(
        TFT_WHITE,
        TFT_BLACK
    );

    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(2);

    tft.drawString(
        button.label,
        button.x + (button.width / 2),
        button.y + (button.height / 2)
    );
}

void mainScreenShow(TFT_eSPI &tft)
{
    displayDrawFrame(
        tft,
        "MAIN",
        100
    );

    for (uint8_t i = 0; i < MAIN_BUTTON_COUNT; i++)
    {
        drawMainButton(
            tft,
            mainButtons[i]
        );
    }
}

void mainScreenLoop(TFT_eSPI &tft)
{
}

bool mainScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
)
{
    for (uint8_t i = 0; i < MAIN_BUTTON_COUNT; i++)
    {
        const MainButton &button = mainButtons[i];

        if (
            x >= button.x &&
            x < (button.x + button.width) &&
            y >= button.y &&
            y < (button.y + button.height)
        )
        {
            screen = button.screen;

            Serial.print("[MAIN] Bouton touche -> ecran ");
            Serial.println(screen);

            return true;
        }
    }

    return false;
}