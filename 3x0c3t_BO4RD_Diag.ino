#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "config.h"
#include "display_config.h"
#include "personalization.h"
#include "display.h"
#include "splash.h"
#include "screen_main.h"
#include "screen_systeme.h"

TFT_eSPI tft = TFT_eSPI();

uint8_t currentScreen = 0;

void setup()
{
    Serial.begin(115200);
    delay(500);

    Serial.println();
    Serial.println("========================================");
    Serial.println("       3x0c3t BO4RD DIAGNOSTIC");
    Serial.println("              VERSION 2.0");
    Serial.println("========================================");
    Serial.println();

    SPI.begin();

    Serial.println("[BOOT] SPI initialise");

    Serial.println("[BOOT] Initialisation display...");

    displayInit(tft);

    Serial.println("[BOOT] Display initialise");

    Serial.println("[BOOT] Affichage splash...");

    splashInit(tft);
    splashShow(tft);
    splashWait();

    Serial.println("[BOOT] Splash termine");

    currentScreen = 0;

    mainScreenInit(tft);
    mainScreenShow(tft);

    Serial.println("[BOOT] Ecran principal affiche");

    Serial.println();
    Serial.println("[BOOT] MAIN : OK");
    Serial.println("[BOOT] BOUTONS : 5");
    Serial.println("[BOOT] COLONNE UNIQUE");
    Serial.println("[BOOT] TOUCH : PRET POUR NAVIGATION");
    Serial.println();

    Serial.println("=== BOOT TERMINE ===");
    Serial.println();
}

void loop()
{
    if (currentScreen == 0)
    {
        mainScreenLoop(tft);
    }
    else if (currentScreen == 1)
    {
        systemeScreenLoop(tft);
    }

    delay(10);
}