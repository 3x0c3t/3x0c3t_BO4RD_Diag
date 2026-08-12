#include <Arduino.h>
#include <TFT_eSPI.h>

#include "screen_systeme.h"
#include "display.h"
#include "debug.h"

// ============================================================
// CONFIGURATION
// ============================================================

#define SYSTEME_BACK_X       10
#define SYSTEME_BACK_Y       180
#define SYSTEME_BACK_WIDTH   100
#define SYSTEME_BACK_HEIGHT  40

// ============================================================
// INITIALISATION
// ============================================================

void systemeScreenInit(
    TFT_eSPI &tft
)
{
    (void)tft;
}

// ============================================================
// AFFICHAGE
// ============================================================

void systemeScreenShow(
    TFT_eSPI &tft
)
{
    tft.fillScreen(
        TFT_BLACK
    );

    displayDrawSystemBar(
        tft
    );

    // --------------------------------------------------------
    // TITRE
    // --------------------------------------------------------

    tft.setTextColor(
        TFT_WHITE,
        TFT_BLACK
    );

    tft.setTextDatum(
        TL_DATUM
    );

    tft.setTextSize(2);

    tft.drawString(
        "SYSTEME",
        10,
        40
    );

    // --------------------------------------------------------
    // INFORMATIONS
    // --------------------------------------------------------

    tft.setTextSize(1);

    tft.drawString(
        "Informations systeme",
        10,
        75
    );

    tft.drawString(
        "ESP8266 NodeMCU",
        10,
        95
    );

    // --------------------------------------------------------
    // RETOUR
    // --------------------------------------------------------

    tft.drawRect(
        SYSTEME_BACK_X,
        SYSTEME_BACK_Y,
        SYSTEME_BACK_WIDTH,
        SYSTEME_BACK_HEIGHT,
        TFT_WHITE
    );

    tft.setTextDatum(
        MC_DATUM
    );

    tft.drawString(
        "RETOUR",
        SYSTEME_BACK_X +
            (SYSTEME_BACK_WIDTH / 2),
        SYSTEME_BACK_Y +
            (SYSTEME_BACK_HEIGHT / 2)
    );

    tft.setTextDatum(
        TL_DATUM
    );

    LOGLN_SYSTEME(
        "[SYSTEME] Page affichee"
    );
}

// ============================================================
// LOOP
// ============================================================

void systemeScreenLoop(
    TFT_eSPI &tft
)
{
    (void)tft;
}

// ============================================================
// TOUCH
// ============================================================

bool systemeScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
)
{
    if (
        x >= SYSTEME_BACK_X &&
        x < (
            SYSTEME_BACK_X +
            SYSTEME_BACK_WIDTH
        ) &&
        y >= SYSTEME_BACK_Y &&
        y < (
            SYSTEME_BACK_Y +
            SYSTEME_BACK_HEIGHT
        )
    )
    {
        screen = 0;

        LOG_SYSTEME(
            "[SYSTEME] RETOUR -> MAIN"
        );

        return true;
    }

    return false;
}