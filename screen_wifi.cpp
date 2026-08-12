#include <Arduino.h>
#include <TFT_eSPI.h>

#include "screen_wifi.h"
#include "display.h"
#include "wifi_diag.h"
#include "debug.h"

// ============================================================
// CONFIGURATION
// ============================================================

static const int16_t WIFI_TITLE_Y = 40;

// ============================================================
// INITIALISATION
// ============================================================

void wifiScreenInit(TFT_eSPI &tft)
{
    (void)tft;

    LOG_WIFI("[WIFI] Ecran Wi-Fi initialise");
}

// ============================================================
// AFFICHAGE
// ============================================================

void wifiScreenShow(TFT_eSPI &tft)
{
    tft.fillScreen(TFT_BLACK);

    displayDrawSystemBar(tft);

    // --------------------------------------------------------
    // TITRE
    // --------------------------------------------------------

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, WIFI_TITLE_Y);
    tft.print("WI-FI");

    // --------------------------------------------------------
    // INFORMATIONS
    // --------------------------------------------------------

    tft.setTextSize(1);

    tft.setCursor(10, 75);
    tft.print("Etat Wi-Fi : ");

    tft.setCursor(10, 95);
    tft.print("SSID : ");

    tft.setCursor(10, 115);
    tft.print("IP : ");

    // --------------------------------------------------------
    // BOUTON RETOUR
    // --------------------------------------------------------

    tft.drawRect(
        10,
        180,
        100,
        40,
        TFT_WHITE
    );

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(1);
    tft.setCursor(30, 195);
    tft.print("RETOUR");

    LOGLN_WIFI("[WIFI] Page affichee");
}

// ============================================================
// BOUCLE
// ============================================================

void wifiScreenLoop(TFT_eSPI &tft)
{
    (void)tft;
}

// ============================================================
// GESTION DU TOUCH
// ============================================================

bool wifiScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
)
{
    // --------------------------------------------------------
    // BOUTON RETOUR
    // --------------------------------------------------------

    if (
        x >= 10 &&
        x < 110 &&
        y >= 180 &&
        y < 220
    )
    {
        screen = 0;

        LOG_WIFI("[WIFI] Touch RETOUR -> MAIN");

        return true;
    }

    // --------------------------------------------------------
    // AUCUN BOUTON
    // --------------------------------------------------------

    return false;
}