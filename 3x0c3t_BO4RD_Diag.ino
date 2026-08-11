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

#include "debug.h"


// ============================================================
// TFT
// ============================================================

TFT_eSPI tft = TFT_eSPI();


// ============================================================
// ECRAN ACTUEL
// ============================================================
//
// 0 = MAIN
// 1 = SYSTEME
// 2 = WI-FI
// 3 = CARTE SD
// 4 = TACTILE
// 5 = DIAGNOSTICS
//
// ============================================================

uint8_t currentScreen = 0;


// ============================================================
// SETUP
// ============================================================

void setup()
{
    Serial.begin(115200);

    delay(500);


    // ========================================================
    // BOOT
    // ========================================================

    LOGLN_BOOT("");
    LOGLN_BOOT("========================================");
    LOGLN_BOOT("       3x0c3t BO4RD DIAGNOSTIC");
    LOGLN_BOOT("              VERSION 2.0");
    LOGLN_BOOT("========================================");
    LOGLN_BOOT("");


    // ========================================================
    // SPI
    // ========================================================

    SPI.begin();

    LOGLN_BOOT("[BOOT] SPI initialise");


    // ========================================================
    // DISPLAY
    // ========================================================

    LOGLN_BOOT("[BOOT] Initialisation display...");

    displayInit(tft);

    LOGLN_BOOT("[BOOT] Display initialise");


    // ========================================================
    // TOUCH
    // ========================================================

    LOGLN_BOOT("[BOOT] Initialisation tactile...");

    touchInit();

    LOGLN_BOOT("[BOOT] Tactile initialise");


    // ========================================================
    // WIFI
    // ========================================================

    LOGLN_BOOT("[BOOT] Initialisation Wi-Fi...");

    wifiSetMode(WIFI_MODE_OFF);

    LOGLN_BOOT("[BOOT] Wi-Fi initialise");

    wifiScreenInit(tft);


    // ========================================================
    // SPLASH
    // ========================================================

    LOGLN_BOOT("[BOOT] Affichage splash...");

    splashInit(tft);

    splashShow(tft);

    splashWait();

    LOGLN_BOOT("[BOOT] Splash termine");


    // ========================================================
    // MAIN
    // ========================================================

    LOGLN_BOOT("[BOOT] Passage ecran principal...");

    currentScreen = 0;

    tft.fillScreen(TFT_BLACK);

    displayDrawSystemBar(tft);

    mainScreenShow(tft);

    LOGLN_BOOT("[BOOT] Ecran principal affiche");


    // ========================================================
    // FIN BOOT
    // ========================================================

    LOGLN_BOOT("");
    LOGLN_BOOT("[BOOT] MAIN  : OK");
    LOGLN_BOOT("[BOOT] TOUCH : OK");
    LOGLN_BOOT("[BOOT] WIFI  : OK");
    LOGLN_BOOT("");
    LOGLN_BOOT("=== BOOT TERMINE ===");
    LOGLN_BOOT("");
}


// ============================================================
// LOOP
// ============================================================

void loop()
{
    // ========================================================
    // LECTURE TACTILE
    // ========================================================

    int16_t x;
    int16_t y;
    uint16_t z;


    if (touchRead(x, y, z))
    {
        // ====================================================
        // EVENEMENT TOUCH
        // ====================================================

        LOGLN_MAIN("");
        LOGLN_MAIN("========================================");
        LOGLN_MAIN("[EVENT] NOUVEAU TOUCH");
        LOGLN_MAIN("========================================");

        LOG_MAIN("[EVENT] Ecran actuel : ");
        LOGLN_MAIN(currentScreen);

        LOG_MAIN("[EVENT] X : ");
        LOGLN_MAIN(x);

        LOG_MAIN("[EVENT] Y : ");
        LOGLN_MAIN(y);

        LOG_MAIN("[EVENT] Pression : ");
        LOGLN_MAIN(z);


        // ====================================================
        // MAIN
        // ====================================================

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


                LOG_MAIN("[EVENT] Navigation vers ecran : ");
                LOGLN_MAIN(currentScreen);


                // ============================================
                // WI-FI
                // ============================================

                if (currentScreen == 2)
                {
                    LOGLN_MAIN(
                        "[EVENT] Ouverture ecran WI-FI"
                    );

                    wifiScreenShow(tft);
                }
            }
            else
            {
                LOGLN_MAIN(
                    "[EVENT] Touch MAIN non traite"
                );
            }
        }


        // ====================================================
        // WI-FI
        // ====================================================

        else if (currentScreen == 2)
        {
            uint8_t newScreen = currentScreen;


            if (
                wifiScreenTouch(
                    x,
                    y,
                    newScreen
                )
            )
            {
                currentScreen = newScreen;


                LOG_WIFI(
                    "[WIFI] Ecran apres touch : "
                );

                LOGLN_WIFI(currentScreen);


                // ============================================
                // RETOUR MAIN
                // ============================================

                if (currentScreen == 0)
                {
                    LOGLN_WIFI(
                        "[WIFI] Retour ecran MAIN"
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
                LOGLN_WIFI(
                    "[WIFI] Touch non traite"
                );
            }
        }


        // ====================================================
        // FIN EVENEMENT
        // ====================================================

        LOGLN_MAIN(
            "========================================"
        );

        LOGLN_MAIN("");
    }


    // ========================================================
    // LOOP WI-FI
    // ========================================================

    if (currentScreen == 2)
    {
        wifiScreenLoop(tft);
    }


    // ========================================================
    // TEMPORISATION
    // ========================================================

    delay(10);
}