#include "display.h"

#include <Arduino.h>
#include <TFT_eSPI.h>

// ============================================================
// TFT
// ============================================================

TFT_eSPI tft = TFT_eSPI();

// ============================================================
// INITIALISATION
// ============================================================

void displayInit()
{
    Serial.println();
    Serial.println("================================");
    Serial.println("[DISPLAY] displayInit() START");
    Serial.println("================================");

    Serial.println("[DISPLAY] Initialisation TFT...");

    tft.init();

    Serial.println("[DISPLAY] TFT init OK");

    Serial.println("[DISPLAY] Rotation = 1");

    tft.setRotation(1);

    Serial.println("[DISPLAY] Effacement ecran");

    tft.fillScreen(TFT_BLACK);

    Serial.println("[DISPLAY] TFT READY");

    Serial.println("[DISPLAY] displayInit() END");
    Serial.println("================================");
}