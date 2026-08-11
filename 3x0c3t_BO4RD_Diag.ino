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
#include "wifi_diag.h"
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
// AFFICHAGE EVENEMENT TOUCH
// ============================================================

void logTouchEvent(
    uint8_t screenBefore,
    uint8_t screenAfter,
    int16_t x,
    int16_t y,
    uint16_t z
)
{
    Serial.println();
    Serial.println("========================================");

    Serial.print("# ECRAN : [");
    Serial.print(screenName(screenBefore));

    Serial.print("] - [EVENT] [TOUCH] sur (");
    Serial.print(screenName(screenAfter));

    Serial.print(") X : ");
    Serial.print(x);

    Serial.print(" Y : ");
    Serial.print(y);

    Serial.print(" Z : ");
    Serial.println(z);

    Serial.println("========================================");
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
        uint8_t screenBefore = currentScreen;
        uint8_t newScreen = currentScreen;

        bool handled = false;

        // ----------------------------------------------------
        // MAIN
        // ----------------------------------------------------

        if (currentScreen == 0)
        {
            handled = mainScreenTouch(
                x,
                y,
                newScreen
            );
        }

        // ----------------------------------------------------
        // SYSTEME
        // ----------------------------------------------------

        else if (currentScreen == 1)
        {
            handled = systemeScreenTouch(
                x,
                y,
                newScreen
            );
        }

        // ----------------------------------------------------
        // WIFI
        // ----------------------------------------------------

        else if (currentScreen == 2)
        {
            handled = wifiScreenTouch(
                x,
                y,
                newScreen
            );
        }

        // ----------------------------------------------------
        // ECRAN NON GERE
        // ----------------------------------------------------

        else
        {
            handled = false;
        }

        // ----------------------------------------------------
        // LOG UNIQUE
        // ----------------------------------------------------

        logTouchEvent(
            screenBefore,
            newScreen,
            x,
            y,
            z
        );

        // ----------------------------------------------------
        // NAVIGATION
        // ----------------------------------------------------

        if (handled)
        {
            currentScreen = newScreen;

            // ------------------------------------------------
            // CHANGEMENT D'ECRAN
            // ------------------------------------------------

            if (currentScreen != screenBefore)
            {
                if (currentScreen == 0)
                {
                    tft.fillScreen(TFT_BLACK);

                    displayDrawSystemBar(tft);

                    mainScreenShow(tft);
                }
                else if (currentScreen == 1)
                {
                    tft.fillScreen(TFT_BLACK);

                    displayDrawSystemBar(tft);

                    systemeScreenShow(tft);
                }
                else if (currentScreen == 2)
                {
                    tft.fillScreen(TFT_BLACK);

                    displayDrawSystemBar(tft);

                    wifiScreenShow(tft);
                }
            }

            // ------------------------------------------------
            // MEME ECRAN
            // ------------------------------------------------

            else
            {
                if (currentScreen == 2)
                {
                    wifiScreenShow(tft);
                }
            }
        }
    }

    // --------------------------------------------------------
    // SCREEN LOOP
    // --------------------------------------------------------

    if (currentScreen == 2)
    {
        wifiScreenLoop(tft);
    }

    // --------------------------------------------------------
    // PETITE PAUSE
    // --------------------------------------------------------

    delay(10);
}