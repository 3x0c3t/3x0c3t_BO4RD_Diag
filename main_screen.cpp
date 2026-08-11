#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display_config.h"
#include "personalization.h"
#include "display.h"
#include "main_screen.h"

// ============================================================
// BOUTONS MAIN
// ============================================================

static MainButton mainButtons[MAIN_BUTTON_COUNT] =
{
    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y,
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "ECRAN 1",
        1
    },

    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y +
            (MAIN_BUTTON_HEIGHT + MAIN_BUTTON_GAP) * 1,
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "ECRAN 2",
        2
    },

    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y +
            (MAIN_BUTTON_HEIGHT + MAIN_BUTTON_GAP) * 2,
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "ECRAN 3",
        3
    },

    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y +
            (MAIN_BUTTON_HEIGHT + MAIN_BUTTON_GAP) * 3,
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "ECRAN 4",
        4
    },

    {
        MAIN_BUTTON_X,
        MAIN_BUTTON_START_Y +
            (MAIN_BUTTON_HEIGHT + MAIN_BUTTON_GAP) * 4,
        MAIN_BUTTON_WIDTH,
        MAIN_BUTTON_HEIGHT,
        "ECRAN 5",
        5
    }
};


// ============================================================
// INITIALISATION
// ============================================================

void mainScreenInit(TFT_eSPI &tft)
{
    // Rien de spécifique pour le moment.
}


// ============================================================
// DESSIN D'UN BOUTON
// ============================================================

static void drawMainButton(
    TFT_eSPI &tft,
    const MainButton &button
)
{
    // Fond
    tft.fillRect(
        button.x,
        button.y,
        button.width,
        button.height,
        TFT_BLACK
    );

    // Contour
    tft.drawRect(
        button.x,
        button.y,
        button.width,
        button.height,
        TFT_CYAN
    );

    // Texte
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


// ============================================================
// AFFICHAGE MAIN
// ============================================================

void mainScreenShow(TFT_eSPI &tft)
{
    // Fond
    tft.fillScreen(UI_BACKGROUND_COLOR);

    // Cadre commun
    displayDrawFrame(
        tft,
        "MAIN",
        100
    );

    // Boutons
    for (uint8_t i = 0; i < MAIN_BUTTON_COUNT; i++)
    {
        drawMainButton(
            tft,
            mainButtons[i]
        );
    }
}


// ============================================================
// LOOP MAIN
// ============================================================

void mainScreenLoop(TFT_eSPI &tft)
{
    // Rien pour le moment.
}


// ============================================================
// DETECTION TACTILE
// ============================================================

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
            x <  button.x + button.width &&
            y >= button.y &&
            y <  button.y + button.height
        )
        {
            screen = button.screen;
            return true;
        }
    }

    return false;
}