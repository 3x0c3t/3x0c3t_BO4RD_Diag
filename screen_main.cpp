#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display_config.h"
#include "display.h"
#include "screen_main.h"


// ============================================================
// BOUTONS MAIN
// ============================================================
//
// Une seule colonne.
//
// 1 : SYSTEME
// 2 : WI-FI
// 3 : CARTE SD
// 4 : TACTILE
// 5 : DIAGNOSTICS
//
// ============================================================

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
    // --------------------------------------------------------
    // Fond du bouton
    // --------------------------------------------------------

    tft.fillRect(
        button.x,
        button.y,
        button.width,
        button.height,
        TFT_BLACK
    );


    // --------------------------------------------------------
    // Contour
    // --------------------------------------------------------

    tft.drawRect(
        button.x,
        button.y,
        button.width,
        button.height,
        TFT_CYAN
    );


    // --------------------------------------------------------
    // Texte
    // --------------------------------------------------------

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
// AFFICHAGE ECRAN PRINCIPAL
// ============================================================

void mainScreenShow(TFT_eSPI &tft)
{
    // --------------------------------------------------------
    // Cadre commun
    // --------------------------------------------------------

    displayDrawFrame(
        tft,
        "MAIN",
        100
    );


    // --------------------------------------------------------
    // Boutons
    // --------------------------------------------------------

    for (uint8_t i = 0; i < MAIN_BUTTON_COUNT; i++)
    {
        drawMainButton(
            tft,
            mainButtons[i]
        );
    }
}


// ============================================================
// BOUCLE MAIN
// ============================================================

void mainScreenLoop(TFT_eSPI &tft)
{
    // Rien pour le moment.
}


// ============================================================
// DETECTION TACTILE
// ============================================================
//
// Les coordonnées utilisées ici sont exactement les mêmes
// que celles utilisées pour dessiner les boutons.
//
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


        // ----------------------------------------------------
        // Test zone bouton
        // ----------------------------------------------------

        if (
            x >= button.x &&
            x <  (button.x + button.width) &&
            y >= button.y &&
            y <  (button.y + button.height)
        )
        {
            screen = button.screen;

            return true;
        }
    }


    return false;
}