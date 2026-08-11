#include "screen_wifi.h"

// ============================================================
// ÉCRAN WI-FI
// ============================================================

void wifiScreenInit(TFT_eSPI &tft)
{
    // Initialisation de l'écran Wi-Fi.
    // Pour l'instant, aucune initialisation spécifique.
    // La fonction existe afin que le système de pages
    // puisse l'appeler proprement.

    (void)tft;
}

// ============================================================
// AFFICHAGE
// ============================================================

void wifiScreenShow(TFT_eSPI &tft)
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    tft.setCursor(10, 10);
    tft.println("WI-FI");

    tft.drawLine(
        0,
        35,
        tft.width(),
        35,
        TFT_WHITE
    );

    tft.setTextSize(1);

    tft.setCursor(10, 55);
    tft.println("Etat Wi-Fi");

    tft.setCursor(10, 75);
    tft.println("----------------");

    tft.setCursor(10, 100);
    tft.println("SSID :");

    tft.setCursor(10, 120);
    tft.println("IP   :");

    tft.setCursor(10, 140);
    tft.println("Signal :");

    tft.setCursor(10, 180);
    tft.println("Ecran Wi-Fi");
}

// ============================================================
// LOOP
// ============================================================

void wifiScreenLoop(TFT_eSPI &tft)
{
    // Rien à faire pour l'instant.
    // Cette fonction servira plus tard pour :
    // - état de connexion
    // - SSID
    // - adresse IP
    // - RSSI
    // - reconnexion
    // - etc.

    (void)tft;
}

// ============================================================
// TACTILE
// ============================================================

bool wifiScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &newScreen
)
{
    (void)x;
    (void)y;

    // Aucune zone tactile spécifique pour l'instant.
    newScreen = 0;

    return false;
}