#include <Arduino.h>
#include <TFT_eSPI.h>

#include "display.h"
#include "display_config.h"
#include "screen_systeme.h"

void systemeScreenInit(TFT_eSPI &tft)
{
    Serial.println("[SYSTEME] Initialisation page SYSTEME");
}

void systemeScreenShow(TFT_eSPI &tft)
{
    Serial.println("[SYSTEME] Affichage page SYSTEME");

    displayDrawFrame(
        tft,
        "SYSTEME",
        101
    );

    tft.setTextDatum(TL_DATUM);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.setTextSize(2);

    tft.drawString(
        "Systeme",
        10,
        55
    );

    tft.setTextSize(1);

    tft.drawString(
        "ESP8266",
        10,
        90
    );

    tft.drawString(
        "3x0c3t BO4RD",
        10,
        110
    );

    tft.drawString(
        "Version DIAG 2.0",
        10,
        130
    );

    // --------------------------------------------------------
    // BOUTON RETOUR
    // --------------------------------------------------------

    tft.drawRect(
        10,
        280,
        100,
        30,
        TFT_CYAN
    );

    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.drawString(
        "RETOUR",
        60,
        295
    );

    Serial.println("[SYSTEME] Page SYSTEME affichee");
}

void systemeScreenLoop(TFT_eSPI &tft)
{
}

bool systemeScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
)
{
    Serial.print("[SYSTEME] Clic X=");
    Serial.print(x);
    Serial.print(" Y=");
    Serial.println(y);

    if (
        x >= 10 &&
        x < 110 &&
        y >= 280 &&
        y < 310
    )
    {
        Serial.println("----------------------------------------");
        Serial.println("[SYSTEME] >>> BOUTON RETOUR CLIQUE");
        Serial.println("[SYSTEME] Retour vers MAIN");
        Serial.println("----------------------------------------");

        screen = 0;

        return true;
    }

    Serial.println("[SYSTEME] Aucun bouton correspondant");

    return false;
}