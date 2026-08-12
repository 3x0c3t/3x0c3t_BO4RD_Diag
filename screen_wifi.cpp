#include <Arduino.h>
#include <TFT_eSPI.h>

#include "screen_wifi.h"
#include "display.h"
#include "wifi_diag.h"
#include "debug.h"

// ============================================================
// CONFIGURATION
// ============================================================

#define WIFI_BACK_X       10
#define WIFI_BACK_Y       180
#define WIFI_BACK_WIDTH   100
#define WIFI_BACK_HEIGHT  40

// ============================================================
// INITIALISATION
// ============================================================

void wifiScreenInit(
    TFT_eSPI &tft
)
{
    (void)tft;

    LOG_WIFI(
        "[WIFI] Ecran Wi-Fi initialise"
    );
}

// ============================================================
// AFFICHAGE
// ============================================================

void wifiScreenShow(
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
        "WI-FI",
        10,
        40
    );

    // --------------------------------------------------------
    // INFORMATIONS
    // --------------------------------------------------------

    tft.setTextSize(1);

    tft.drawString(
        "Etat Wi-Fi : OFF",
        10,
        75
    );

    tft.drawString(
        "SSID :",
        10,
        95
    );

    tft.drawString(
        "IP :",
        10,
        115
    );

    // --------------------------------------------------------
    // RETOUR
    // --------------------------------------------------------

    tft.drawRect(
        WIFI_BACK_X,
        WIFI_BACK_Y,
        WIFI_BACK_WIDTH,
        WIFI_BACK_HEIGHT,
        TFT_WHITE
    );

    tft.setTextDatum(
        MC_DATUM
    );

    tft.drawString(
        "RETOUR",
        WIFI_BACK_X +
            (WIFI_BACK_WIDTH / 2),
        WIFI_BACK_Y +
            (WIFI_BACK_HEIGHT / 2)
    );

    tft.setTextDatum(
        TL_DATUM
    );

    LOGLN_WIFI(
        "[WIFI] Page affichee"
    );
}

// ============================================================
// LOOP
// ============================================================

void wifiScreenLoop(
    TFT_eSPI &tft
)
{
    (void)tft;
}

// ============================================================
// TOUCH
// ============================================================

bool wifiScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
)
{
    if (
        x >= WIFI_BACK_X &&
        x < (
            WIFI_BACK_X +
            WIFI_BACK_WIDTH
        ) &&
        y >= WIFI_BACK_Y &&
        y < (
            WIFI_BACK_Y +
            WIFI_BACK_HEIGHT
        )
    )
    {
        screen = 0;

        LOG_WIFI(
            "[WIFI] RETOUR -> MAIN"
        );

        return true;
    }

    return false;
}