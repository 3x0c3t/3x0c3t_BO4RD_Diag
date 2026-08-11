#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display_config.h"
#include "display.h"
#include "main_screen.h"


// ============================================================
// INITIALISATION
// ============================================================

void mainScreenInit(TFT_eSPI &tft)
{
    // Rien pour le moment.
}


// ============================================================
// ECRAN PRINCIPAL
// ============================================================

void mainScreenShow(TFT_eSPI &tft)
{
    // ========================================================
    // CADRE COMMUN
    // ========================================================

    displayDrawFrame(
        tft,
        "MAIN",
        100
    );


    // ========================================================
    // CONTENU PAGE
    // ========================================================

    const int centerX =
        UI_CONTENT_X +
        (UI_CONTENT_WIDTH / 2);

    const int centerY =
        UI_CONTENT_Y +
        (UI_CONTENT_HEIGHT / 2);


    // --------------------------------------------------------
    // Nom du projet
    // --------------------------------------------------------

    tft.setTextColor(
        TFT_WHITE,
        UI_BACKGROUND_COLOR
    );

    tft.setTextDatum(MC_DATUM);

    tft.setTextSize(2);

    tft.drawString(
        "3x0c3t BO4RD",
        centerX,
        centerY - 20
    );


    // --------------------------------------------------------
    // Mode
    // --------------------------------------------------------

    tft.setTextSize(1);

    tft.drawString(
        "DIAGNOSTIC",
        centerX,
        centerY + 10
    );
}


// ============================================================
// LOOP
// ============================================================

void mainScreenLoop(TFT_eSPI &tft)
{
    // Rien pour le moment.
}