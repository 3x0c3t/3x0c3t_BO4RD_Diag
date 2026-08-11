#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "config.h"
#include "display_config.h"
#include "personalization.h"

#include "display.h"
#include "splash.h"
#include "main_screen.h"

// MODULES DESACTIVEES
// #include "touch.h"
// #include "sd_diag.h"
// #include "wifi_diag.h"
// #include "system_diag.h"
// #include "diagnostics.h"

// ============================================================
// TFT
// ============================================================

TFT_eSPI tft = TFT_eSPI();

// ============================================================
// SETUP
// ============================================================

void setup()
{
    // SERIAL
    Serial.begin(115200);
    delay(500);

    Serial.println();
    Serial.println("========================================");
    Serial.println("       3x0c3t BO4RD DIAGNOSTIC");
    Serial.println("              VERSION 2.0");
    Serial.println("========================================");
    Serial.println();

    // SPI
    SPI.begin();
    Serial.println("[BOOT] SPI initialise");

    // DISPLAY
    Serial.println("[BOOT] Initialisation display...");
    displayInit(tft);
    Serial.println("[BOOT] Display initialise");

    // SPLASH
    Serial.println("[BOOT] Affichage splash...");
    splashInit(tft);
    splashShow(tft);
    splashWait();
    Serial.println("[BOOT] Splash termine");

    // ========================================================
    // TRANSITION SPLASH -> MAIN
    // ========================================================

    Serial.println("[BOOT] Passage ecran principal...");

    tft.fillScreen(TFT_BLACK);

    displayDrawSystemBar(tft);
    mainScreenShow(tft);

    Serial.println("[BOOT] Ecran principal affiche");

    // ========================================================
    // MODULES DESACTIVEES
    // ========================================================

    Serial.println();
    Serial.println("[BOOT] Modules supplementaires desactives");
    Serial.println("[BOOT] TOUCH : OFF");
    Serial.println("[BOOT] SD    : OFF");
    Serial.println("[BOOT] WIFI  : OFF");
    Serial.println("[BOOT] SYSTEM: OFF");
    Serial.println("[BOOT] DIAG  : OFF");

    // ========================================================
    // FIN BOOT
    // ========================================================

    Serial.println();
    Serial.println("=== BOOT TERMINE ===");
    Serial.println();
}

// ============================================================
// LOOP
// ============================================================

void loop()
{
    // Aucun module actif pour le moment.

    delay(10);
}