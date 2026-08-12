#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display_config.h"
#include "display.h"
#include "screen_main.h"
#include "debug.h"

// ============================================================
// BOUTONS MAIN
// ============================================================

static const MainButton mainButtons[
    MAIN_BUTTON_COUNT
] =
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
    // FOND
    // --------------------------------------------------------

    tft.fillRect(
        button.x,
        button.y,
        button.width,
        button.height,
        TFT_BLACK
    );

    // --------------------------------------------------------
    // CONTOUR
    // --------------------------------------------------------

    tft.drawRect(
        button.x,
        button.y,
        button.width,
        button.height,
        TFT_CYAN
    );

    // --------------------------------------------------------
    // TEXTE
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
        button.x +
            (button.width / 2),
        button.y +
            (button.height / 2)
    );

    tft.setTextDatum(
        TL_DATUM
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
    // CADRE
    // --------------------------------------------------------

    displayDrawFrame(
        tft,
        "MAIN",
        70
    );

    // --------------------------------------------------------
    // BOUTONS
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
    for (
        uint8_t i = 0;
        i < MAIN_BUTTON_COUNT;
        i++
    )
    {
        const MainButton &button =
            mainButtons[i];

        if (
            x >= button.x &&
            x < (
                button.x +
                button.width
            ) &&
            y >= button.y &&
            y < (
                button.y +
                button.height
            )
        )
        {
            screen =
                button.screen;

            LOG_MAIN(
                "[MAIN] -> "
            );

            LOGLN_MAIN(
                button.label
            );

            return true;
        }
    }

    return false;
}