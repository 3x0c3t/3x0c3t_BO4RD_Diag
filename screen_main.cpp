#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display_config.h"
#include "display.h"
#include "screen_main.h"
#include "debug.h"


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

void mainScreenInit(
    TFT_eSPI &tft
)
{
    (void)tft;

    LOGLN_MAIN(
        "[MAIN] Initialisation"
    );
}


// ============================================================
// DESSIN BOUTON
// ============================================================

static void drawMainButton(
    TFT_eSPI &tft,
    const MainButton &button
)
{
    // --------------------------------------------------------
    // Fond
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

    tft.setTextDatum(
        MC_DATUM
    );

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

void mainScreenShow(
    TFT_eSPI &tft
)
{
    LOGLN_MAIN(
        "[MAIN] Affichage page MAIN"
    );


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

    for (
        uint8_t i = 0;
        i < MAIN_BUTTON_COUNT;
        i++
    )
    {
        drawMainButton(
            tft,
            mainButtons[i]
        );


        // ----------------------------------------------------
        // DETAIL UNIQUEMENT NIVEAU 2
        // ----------------------------------------------------

        LOG_MAIN_DETAIL("[MAIN] Bouton ");
        LOG_MAIN_DETAIL(i);

        LOG_MAIN_DETAIL(" : ");
        LOG_MAIN_DETAIL(mainButtons[i].label);

        LOG_MAIN_DETAIL(" -> ecran ");
        LOGLN_MAIN_DETAIL(mainButtons[i].screen);
    }


    LOGLN_MAIN(
        "[MAIN] Page MAIN affichee"
    );
}


// ============================================================
// LOOP MAIN
// ============================================================

void mainScreenLoop(
    TFT_eSPI &tft
)
{
    (void)tft;
}


// ============================================================
// TOUCH MAIN
// ============================================================

bool mainScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
)
{
    // --------------------------------------------------------
    // LOG IMPORTANT
    // --------------------------------------------------------

    LOG_MAIN("[MAIN] Touch X=");
    LOG_MAIN(x);

    LOG_MAIN(" Y=");
    LOGLN_MAIN(y);


    // --------------------------------------------------------
    // TEST BOUTONS
    // --------------------------------------------------------

    for (
        uint8_t i = 0;
        i < MAIN_BUTTON_COUNT;
        i++
    )
    {
        const MainButton &button =
            mainButtons[i];


        // ----------------------------------------------------
        // LOG COMPLET
        // ----------------------------------------------------

        LOG_MAIN_DETAIL("[MAIN] Test bouton ");
        LOG_MAIN_DETAIL(i);

        LOG_MAIN_DETAIL(" : ");
        LOGLN_MAIN_DETAIL(button.label);


        // ----------------------------------------------------
        // TEST COORDONNEES
        // ----------------------------------------------------

        if (
            x >= button.x &&
            x < (button.x + button.width) &&
            y >= button.y &&
            y < (button.y + button.height)
        )
        {
            screen = button.screen;


            LOG_MAIN("[MAIN] Bouton : ");
            LOG_MAIN(button.label);

            LOG_MAIN(" -> ecran ");
            LOGLN_MAIN(screen);


            return true;
        }
    }


    // --------------------------------------------------------
    // AUCUN BOUTON
    // --------------------------------------------------------

    LOGLN_MAIN(
        "[MAIN] Aucun bouton correspondant"
    );


    return false;
}