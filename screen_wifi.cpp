#include <Arduino.h>
#include <TFT_eSPI.h>

#include "screen_wifi.h"
#include "wifi_diag.h"
#include "debug.h"

// ============================================================
// ECRAN WI-FI
// ============================================================

// ------------------------------------------------------------
// PARAMETRES AFFICHAGE
// ------------------------------------------------------------

static const int WIFI_TITLE_Y = 45;
static const int WIFI_LINE_Y = 75;
static const int WIFI_BUTTON_Y = 95;
static const int WIFI_BUTTON_H = 42;

// ============================================================
// INITIALISATION
// ============================================================

void wifiScreenInit(
    TFT_eSPI &tft
)
{
    LOG_WIFI("[WIFI] Ecran Wi-Fi initialise");
}

// ============================================================
// AFFICHAGE
// ============================================================

void wifiScreenShow(
    TFT_eSPI &tft
)
{
    // --------------------------------------------------------
    // FOND
    // --------------------------------------------------------

    tft.fillScreen(TFT_BLACK);

    // --------------------------------------------------------
    // TITRE
    // --------------------------------------------------------

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    tft.setCursor(
        10,
        WIFI_TITLE_Y
    );

    tft.print("WI-FI");

    // --------------------------------------------------------
    // LIGNE
    // --------------------------------------------------------

    tft.drawLine(
        0,
        WIFI_LINE_Y,
        tft.width(),
        WIFI_LINE_Y,
        TFT_WHITE
    );

    // --------------------------------------------------------
    // MODE
    // --------------------------------------------------------

    tft.setTextSize(1);

    tft.setCursor(
        10,
        82
    );

    tft.print("Mode : ");

    uint8_t mode = wifiGetMode();

    if (mode == WIFI_MODE_OFF)
    {
        tft.print("OFF");
    }
    else if (mode == WIFI_MODE_CLIENT)
    {
        tft.print("CLIENT");
    }
    else if (mode == WIFI_MODE_AP)
    {
        tft.print("AP");
    }
    else
    {
        tft.print("UNKNOWN");
    }

    // --------------------------------------------------------
    // BOUTON SCAN
    // --------------------------------------------------------

    tft.fillRect(
        10,
        WIFI_BUTTON_Y,
        tft.width() - 20,
        WIFI_BUTTON_H,
        TFT_BLUE
    );

    tft.setTextColor(TFT_WHITE, TFT_BLUE);
    tft.setTextSize(2);

    tft.setCursor(
        65,
        WIFI_BUTTON_Y + 12
    );

    tft.print("SCAN WI-FI");

    // --------------------------------------------------------
    // BOUTON OFF
    // --------------------------------------------------------

    tft.fillRect(
        10,
        150,
        tft.width() - 20,
        WIFI_BUTTON_H,
        TFT_RED
    );

    tft.setTextColor(TFT_WHITE, TFT_RED);

    tft.setCursor(
        85,
        162
    );

    tft.print("WI-FI OFF");

    // --------------------------------------------------------
    // RETOUR
    // --------------------------------------------------------

    tft.fillRect(
        10,
        210,
        tft.width() - 20,
        42,
        TFT_DARKGREY
    );

    tft.setTextColor(
        TFT_WHITE,
        TFT_DARKGREY
    );

    tft.setCursor(
        95,
        222
    );

    tft.print("RETOUR");

    // --------------------------------------------------------
    // LOG
    // --------------------------------------------------------

    LOGLN_WIFI(
        "[WIFI] Ecran affiche"
    );
}

// ============================================================
// LOOP
// ============================================================

void wifiScreenLoop(
    TFT_eSPI &tft
)
{
    // --------------------------------------------------------
    // Rien à faire en permanence pour le moment.
    // --------------------------------------------------------
}

// ============================================================
// TOUCH
// ============================================================

bool wifiScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &newScreen
)
{
    // --------------------------------------------------------
    // RETOUR
    // --------------------------------------------------------

    if (
        x >= 10 &&
        x <= 230 &&
        y >= 210 &&
        y <= 252
    )
    {
        LOG_WIFI(
            "[WIFI] Bouton RETOUR"
        );

        newScreen = 0;

        return true;
    }

    // --------------------------------------------------------
    // SCAN
    // --------------------------------------------------------

    if (
        x >= 10 &&
        x <= 230 &&
        y >= 95 &&
        y <= 137
    )
    {
        LOGLN_WIFI(
            "[WIFI] Bouton SCAN"
        );

        wifiScan();

        return true;
    }

    // --------------------------------------------------------
    // WI-FI OFF
    // --------------------------------------------------------

    if (
        x >= 10 &&
        x <= 230 &&
        y >= 150 &&
        y <= 192
    )
    {
        LOGLN_WIFI(
            "[WIFI] Bouton WI-FI OFF"
        );

        wifiSetMode(WIFI_MODE_OFF);

        return true;
    }

    return false;
}