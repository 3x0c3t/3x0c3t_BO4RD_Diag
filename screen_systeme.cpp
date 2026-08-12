#include <Arduino.h>
#include <TFT_eSPI.h>

#include "screen_systeme.h"
#include "display.h"
#include "debug.h"

// ============================================================
// CONFIGURATION ECRAN SYSTEME
// ============================================================

static const int16_t SYSTEME_TITLE_Y = 40;

// ============================================================
// INITIALISATION
// ============================================================

void systemeScreenInit(TFT_eSPI &tft)
{
    (void)tft;

    LOG_SYSTEME("[SYSTEME] Ecran initialise");
}

// ============================================================
// AFFICHAGE
// ============================================================

void systemeScreenShow(TFT_eSPI &tft)
{
    tft.fillScreen(TFT_BLACK);

    displayDrawSystemBar(tft);

    // --------------------------------------------------------
    // TITRE
    // --------------------------------------------------------

    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(10, SYSTEME_TITLE_Y);
    tft.print("SYSTEME");

    // --------------------------------------------------------
    // CONTENU
    // --------------------------------------------------------

    tft.setTextSize(1);
    tft.setCursor(10, 75);
    tft.print("Informations systeme");

    tft.setCursor(10, 95);
    tft.print("ESP8266 NodeMCU");

    LOGLN_SYSTEME("[SYSTEME] Page affichee");
}

// ============================================================
// BOUCLE
// ============================================================

void systemeScreenLoop(TFT_eSPI &tft)
{
    (void)tft;
}

// ============================================================
// GESTION DU TOUCH
// ============================================================

bool systemeScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
)
{
    // --------------------------------------------------------
    // Pour le moment, aucun bouton SYSTEME
    // --------------------------------------------------------

    (void)x;
    (void)y;
    (void)screen;

    return false;
}