#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "config.h"
#include "display_config.h"
#include "personalization.h"
#include "display.h"
#include "splash.h"
#include "screen_main.h"

// ============================================================
// TFT
// ============================================================

TFT_eSPI tft = TFT_eSPI();


// ============================================================
// ECRAN ACTUEL
// ============================================================

uint8_t currentScreen = 0;


// ============================================================
// SETUP
// ============================================================

void setup()
{
    // --------------------------------------------------------
    // SERIAL
    // --------------------------------------------------------

    Serial.begin(115200);
    delay(500);

    Serial.println();
    Serial.println("========================================");
    Serial.println("       3x0c3t BO4RD DIAGNOSTIC");
    Serial.println("              VERSION 2.0");
    Serial.println("========================================");
    Serial.println();


    // --------------------------------------------------------
    // SPI
    // --------------------------------------------------------

    SPI.begin();

    Serial.println("[BOOT] SPI initialise");


    // --------------------------------------------------------
    // DISPLAY
    // --------------------------------------------------------

    Serial.println("[BOOT] Initialisation display...");

    displayInit(tft);

    Serial.println("[BOOT] Display initialise");


    // --------------------------------------------------------
    // SPLASH
    // --------------------------------------------------------

    Serial.println("[BOOT] Affichage splash...");

    splashInit(tft);
    splashShow(tft);
    splashWait();

    Serial.println("[BOOT] Splash termine");


    // --------------------------------------------------------
    // MAIN
    // --------------------------------------------------------

    Serial.println("[BOOT] Passage ecran principal...");

    currentScreen = 0;

    mainScreenInit(tft);
    mainScreenShow(tft);

    Serial.println("[BOOT] Ecran principal affiche");


    // --------------------------------------------------------
    // FIN BOOT
    // --------------------------------------------------------

    Serial.println();
    Serial.println("[BOOT] MAIN : OK");
    Serial.println("[BOOT] BOUTONS : 5");
    Serial.println("[BOOT] COLONNE UNIQUE");
    Serial.println("[BOOT] TOUCH : PRET POUR NAVIGATION");
    Serial.println();

    Serial.println("=== BOOT TERMINE ===");
    Serial.println();
}


// ============================================================
// LOOP
// ============================================================

void loop()
{
    // --------------------------------------------------------
    // MAIN
    // --------------------------------------------------------

    if (currentScreen == 0)
    {
        mainScreenLoop(tft);
    }

    delay(10);
}