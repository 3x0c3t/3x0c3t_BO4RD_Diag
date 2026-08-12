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
// AFFICHAGE PAGE SIMPLE
// ============================================================

void showSimpleScreen(
    const char* title,
    const char* description
)
{
    tft.fillScreen(TFT_BLACK);

    displayDrawSystemBar(tft);

    // --------------------------------------------------------
    // TITRE
    // --------------------------------------------------------

    tft.setTextColor(
        TFT_WHITE,
        TFT_BLACK
    );

    tft.setTextDatum(
        TL_DATUM
    );

    tft.setTextSize(2);

    tft.drawString(
        title,
        10,
        40
    );

    // --------------------------------------------------------
    // DESCRIPTION
    // --------------------------------------------------------

    tft.setTextSize(1);

    tft.drawString(
        description,
        10,
        75
    );

    // --------------------------------------------------------
    // BOUTON RETOUR
    // --------------------------------------------------------

    tft.drawRect(
        10,
        180,
        100,
        40,
        TFT_WHITE
    );

    tft.setTextDatum(
        MC_DATUM
    );

    tft.setTextSize(1);

    tft.drawString(
        "RETOUR",
        60,
        200
    );

    tft.setTextDatum(
        TL_DATUM
    );
}

// ============================================================
// AFFICHAGE ECRAN
// ============================================================

void showScreen(
    uint8_t screen
)
{
    tft.fillScreen(TFT_BLACK);

    displayDrawSystemBar(tft);

    switch (screen)
    {
        case 0:

            mainScreenShow(tft);

            break;

        case 1:

            systemeScreenShow(tft);

            break;

        case 2:

            wifiScreenShow(tft);

            break;

        case 3:

            showSimpleScreen(
                "CARTE SD",
                "Gestion de la carte SD"
            );

            break;

        case 4:

            showSimpleScreen(
                "TACTILE",
                "Diagnostic tactile"
            );

            break;

        case 5:

            showSimpleScreen(
                "DIAGNOSTICS",
                "Diagnostics 3x0c3t BO4RD"
            );

            break;

        default:

            currentScreen = 0;

            mainScreenShow(tft);

            break;
    }
}

// ============================================================
// TOUCH ECRANS SIMPLES
// ============================================================

bool simpleScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
)
{
    // --------------------------------------------------------
    // BOUTON RETOUR
    // --------------------------------------------------------

    if (
        x >= 10 &&
        x < 110 &&
        y >= 180 &&
        y < 220
    )
    {
        screen = 0;

        return true;
    }

    return false;
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

    Serial.println(
        "[BOOT] SPI initialise"
    );

    // --------------------------------------------------------
    // DISPLAY
    // --------------------------------------------------------

    Serial.println(
        "[BOOT] Initialisation display..."
    );

    displayInit(tft);

    Serial.println(
        "[BOOT] Display initialise"
    );

    // --------------------------------------------------------
    // TOUCH
    // --------------------------------------------------------

    Serial.println(
        "[BOOT] Initialisation tactile..."
    );

    touchInit(tft);

    Serial.println(
        "[BOOT] Tactile initialise"
    );

    // --------------------------------------------------------
    // WIFI
    // --------------------------------------------------------

    Serial.println(
        "[BOOT] Initialisation Wi-Fi..."
    );

    wifiSetMode(WIFI_MODE_OFF);

    wifiScreenInit(tft);

    Serial.println(
        "[BOOT] Wi-Fi initialise"
    );

    // --------------------------------------------------------
    // SPLASH
    // --------------------------------------------------------

    Serial.println(
        "[BOOT] Affichage splash..."
    );

    splashInit(tft);

    splashShow(tft);

    splashWait();

    Serial.println(
        "[BOOT] Splash termine"
    );

    // --------------------------------------------------------
    // MAIN
    // --------------------------------------------------------

    currentScreen = 0;

    showScreen(
        currentScreen
    );

    Serial.print(
        "[BOOT] Ecran : "
    );

    Serial.print(
        screenName(currentScreen)
    );

    Serial.print(
        " ("
    );

    Serial.print(
        currentScreen
    );

    Serial.println(
        ")"
    );

    Serial.println();
    Serial.println(
        "=== BOOT TERMINE ==="
    );
    Serial.println();
}

// ============================================================
// LOOP
// ============================================================

void loop()
{
    int16_t x = 0;
    int16_t y = 0;

    uint16_t z = 0;

    // --------------------------------------------------------
    // TOUCH
    // --------------------------------------------------------

    if (
        touchRead(
            tft,
            x,
            y,
            z
        )
    )
    {
        uint8_t screenBefore =
            currentScreen;

        uint8_t screenAfter =
            currentScreen;

        bool handled = false;

        // ----------------------------------------------------
        // TRAITEMENT ECRAN
        // ----------------------------------------------------

        switch (
            currentScreen
        )
        {
            case 0:

                handled =
                    mainScreenTouch(
                        x,
                        y,
                        screenAfter
                    );

                break;

            case 1:

                handled =
                    systemeScreenTouch(
                        x,
                        y,
                        screenAfter
                    );

                break;

            case 2:

                handled =
                    wifiScreenTouch(
                        x,
                        y,
                        screenAfter
                    );

                break;

            case 3:
            case 4:
            case 5:

                handled =
                    simpleScreenTouch(
                        x,
                        y,
                        screenAfter
                    );

                break;

            default:

                handled = false;

                break;
        }

        // ----------------------------------------------------
        // EVENEMENT
        // ----------------------------------------------------

        if (
            handled &&
            screenAfter != screenBefore
        )
        {
            Serial.println(
                "========================================"
            );

            Serial.print(
                "# ECRAN : ["
            );

            Serial.print(
                screenName(screenBefore)
            );

            Serial.print(
                "] - [EVENT] [TOUCH] sur ("
            );

            Serial.print(
                screenName(screenAfter)
            );

            Serial.print(
                ") X : "
            );

            Serial.print(x);

            Serial.print(
                " Y : "
            );

            Serial.print(y);

            Serial.print(
                " Z : "
            );

            Serial.println(z);

            Serial.print(
                "[EVENT] Navigation : "
            );

            Serial.print(
                screenName(screenBefore)
            );

            Serial.print(
                " -> "
            );

            Serial.println(
                screenName(screenAfter)
            );

            Serial.println(
                "========================================"
            );

            // ------------------------------------------------
            // CHANGEMENT ECRAN
            // ------------------------------------------------

            currentScreen =
                screenAfter;

            showScreen(
                currentScreen
            );
        }

        delay(120);
    }

    // --------------------------------------------------------
    // LOOP WI-FI
    // --------------------------------------------------------

    if (
        currentScreen == 2
    )
    {
        wifiScreenLoop(tft);
    }

    delay(10);
}