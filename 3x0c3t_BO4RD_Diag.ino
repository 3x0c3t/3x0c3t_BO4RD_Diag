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
#include "screen_tactile.h"

TFT_eSPI tft = TFT_eSPI();

uint8_t currentScreen = 0;

static bool lastTouchState = false;

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
    // TOUCH
    // --------------------------------------------------------

    Serial.println("[BOOT] Initialisation tactile...");

    touchInit();

    Serial.println("[BOOT] Tactile initialise");

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

    tft.fillScreen(TFT_BLACK);

    mainScreenInit(tft);
    mainScreenShow(tft);

    Serial.println("[BOOT] Ecran principal affiche");

    // --------------------------------------------------------
    // FIN BOOT
    // --------------------------------------------------------

    Serial.println();
    Serial.println("[BOOT] MAIN    : OK");
    Serial.println("[BOOT] TOUCH   : OK");
    Serial.println("[BOOT] SYSTEME : PRET");
    Serial.println();
    Serial.println("=== BOOT TERMINE ===");
    Serial.println();
}

void loop()
{
    // ========================================================
    // TOUCH
    // ========================================================

    bool touchState = touchAvailable();

    if (touchState && !lastTouchState)
    {
        int16_t x = 0;
        int16_t y = 0;
        uint16_t pressure = 0;

        Serial.println();
        Serial.println("========================================");
        Serial.println("[EVENT] NOUVEAU TOUCH");
        Serial.println("========================================");

        if (touchRead(x, y, pressure))
        {
            uint8_t newScreen = currentScreen;

            Serial.print("[EVENT] Ecran actuel : ");
            Serial.println(currentScreen);

            Serial.print("[EVENT] X : ");
            Serial.println(x);

            Serial.print("[EVENT] Y : ");
            Serial.println(y);

            Serial.print("[EVENT] Pression : ");
            Serial.println(pressure);

            bool handled = false;

            // ------------------------------------------------
            // MAIN
            // ------------------------------------------------

            if (currentScreen == 0)
            {
                handled = mainScreenTouch(
                    x,
                    y,
                    newScreen
                );
            }

            // ------------------------------------------------
            // SYSTEME
            // ------------------------------------------------

            else if (currentScreen == 1)
            {
                handled = systemeScreenTouch(
                    x,
                    y,
                    newScreen
                );
            }

            // ------------------------------------------------
            // RESULTAT
            // ------------------------------------------------

            if (handled)
            {
                if (newScreen != currentScreen)
                {
                    Serial.println();
                    Serial.println("[NAV] CHANGEMENT D'ECRAN");

                    Serial.print("[NAV] ");
                    Serial.print(currentScreen);

                    Serial.print(" -> ");

                    Serial.println(newScreen);

                    currentScreen = newScreen;

                    // ----------------------------------------
                    // AFFICHAGE NOUVEL ECRAN
                    // ----------------------------------------

                    tft.fillScreen(TFT_BLACK);

                    if (currentScreen == 0)
                    {
                        Serial.println("[NAV] Affichage MAIN");

                        mainScreenInit(tft);
                        mainScreenShow(tft);
                    }
                    else if (currentScreen == 1)
                    {
                        Serial.println("[NAV] Affichage SYSTEME");

                        systemeScreenInit(tft);
                        systemeScreenShow(tft);
                    }

                    Serial.println("[NAV] Ecran affiche");
                }
            }
            else
            {
                Serial.println("[EVENT] Touch non traite");
            }
        }

        Serial.println("========================================");
        Serial.println();
    }

    lastTouchState = touchState;

    // ========================================================
    // SCREEN LOOP
    // ========================================================

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