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
#include "touch.h"
#include "screen_wifi.h"

#include "touch.h"
#include "wifi_diag.h"
#include "screen_wifi.h"
#include "debug.h"

// ============================================================
// TFT
// ============================================================

TFT_eSPI tft = TFT_eSPI();

// ============================================================
// ECRAN ACTUEL
// ============================================================

uint8_t currentScreen = 0;

// ============================================================
// NOMS DES ECRANS
// ============================================================

const char* screenName(uint8_t screen)
{
    switch (screen)
    {
        case 0:
            return "MAIN";

        case 1:
            return "SYSTEME";

        case 2:
            return "WI-FI";

        case 3:
            return "CARTE SD";

        case 4:
            return "TACTILE";

        case 5:
            return "DIAGNOSTICS";

        default:
            return "INCONNU";
    }
}

// ============================================================
// SETUP
// ============================================================

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

    touchInit(tft);

    Serial.println("[BOOT] Tactile initialise");

    // --------------------------------------------------------
    // WIFI
    // --------------------------------------------------------

    Serial.println("[BOOT] Initialisation Wi-Fi...");

    wifiSetMode(WIFI_MODE_OFF);

    Serial.println("[BOOT] Wi-Fi initialise");

    wifiScreenInit(tft);

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

    displayDrawSystemBar(tft);

    mainScreenShow(tft);

    Serial.print("[BOOT] Ecran affiche : ");
    Serial.print(screenName(currentScreen));
    Serial.print(" (");
    Serial.print(currentScreen);
    Serial.println(")");

    // --------------------------------------------------------
    // FIN BOOT
    // --------------------------------------------------------

    Serial.println();
    Serial.println("[BOOT] MAIN  : OK");
    Serial.println("[BOOT] TOUCH : OK");
    Serial.println("[BOOT] WIFI  : OK");
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
    // TOUCH
    // --------------------------------------------------------

    int16_t x;
    int16_t y;
    uint16_t z;

    if (touchRead(tft, x, y, z))
    {
        Serial.println();
        Serial.println("========================================");
        Serial.println("[EVENT] NOUVEAU TOUCH");
        Serial.println("========================================");

        Serial.print("[EVENT] Ecran actuel : ");
        Serial.print(screenName(currentScreen));
        Serial.print(" (");
        Serial.print(currentScreen);
        Serial.println(")");

        Serial.print("[EVENT] X : ");
        Serial.println(x);

        Serial.print("[EVENT] Y : ");
        Serial.println(y);

        Serial.print("[EVENT] Pression : ");
        Serial.println(z);

        // ----------------------------------------------------
        // MAIN
        // ----------------------------------------------------

        if (currentScreen == 0)
        {
            uint8_t newScreen = currentScreen;

            if (
                mainScreenTouch(
                    x,
                    y,
                    newScreen
                )
            )
            {
                currentScreen = newScreen;

                Serial.print("[EVENT] Navigation vers : ");
                Serial.print(screenName(currentScreen));
                Serial.print(" (");
                Serial.print(currentScreen);
                Serial.println(")");

                // ------------------------------------------------
                // WI-FI
                // ------------------------------------------------

                if (currentScreen == 2)
                {
                    Serial.println(
                        "[EVENT] Ouverture ecran WI-FI"
                    );

                    wifiScreenShow(tft);
                }
            }
            else
            {
                Serial.println(
                    "[EVENT] Touch MAIN non traite"
                );
            }
        }

        // ----------------------------------------------------
        // SYSTEME
        // ----------------------------------------------------

        else if (currentScreen == 1)
        {
            Serial.print("[EVENT] Touch sur : ");
            Serial.print(screenName(currentScreen));
            Serial.print(" (");
            Serial.print(currentScreen);
            Serial.println(")");

            Serial.print("[SYSTEME] X=");
            Serial.print(x);
            Serial.print(" Y=");
            Serial.println(y);

            // Navigation SYSTEME à ajouter ici
        }

        // ----------------------------------------------------
        // WIFI
        // ----------------------------------------------------

        else if (currentScreen == 2)
        {
            uint8_t newScreen = currentScreen;

            Serial.print("[WIFI] Touch X=");
            Serial.print(x);
            Serial.print(" Y=");
            Serial.println(y);

            if (
                wifiScreenTouch(
                    x,
                    y,
                    newScreen
                )
            )
            {
                currentScreen = newScreen;

                Serial.print("[EVENT] Ecran apres touch Wi-Fi : ");
                Serial.print(screenName(currentScreen));
                Serial.print(" (");
                Serial.print(currentScreen);
                Serial.println(")");

                // ------------------------------------------------
                // RETOUR MAIN
                // ------------------------------------------------

                if (currentScreen == 0)
                {
                    Serial.println(
                        "[EVENT] Retour ecran MAIN"
                    );

                    tft.fillScreen(TFT_BLACK);

                    displayDrawSystemBar(tft);

                    mainScreenShow(tft);
                }
                else
                {
                    wifiScreenShow(tft);
                }
            }
            else
            {
                Serial.println(
                    "[EVENT] Touch Wi-Fi non traite"
                );
            }
        }

        // ----------------------------------------------------
        // AUTRES ECRANS
        // ----------------------------------------------------

        else
        {
            Serial.print("[EVENT] Ecran non gere : ");
            Serial.print(screenName(currentScreen));
            Serial.print(" (");
            Serial.print(currentScreen);
            Serial.println(")");
        }

        Serial.println(
            "========================================"
        );
        Serial.println();
    }

    // --------------------------------------------------------
    // SCREEN LOOP
    // --------------------------------------------------------

    if (currentScreen == 2)
    {
        wifiScreenLoop(tft);
    }

    delay(10);
}