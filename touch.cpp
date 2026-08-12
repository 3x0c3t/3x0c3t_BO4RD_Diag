#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#include "touch.h"

// ============================================================
// XPT2046
// ============================================================

static XPT2046_Touchscreen touch(
    BO4RD_TOUCH_CS,
    BO4RD_TOUCH_IRQ
);

// ============================================================
// ETAT
// ============================================================

static bool touchInitialized = false;

// ============================================================
// INITIALISATION
// ============================================================

void touchInit(TFT_eSPI &tft)
{
    (void)tft;

    Serial.println("[TOUCH] Initialisation XPT2046");

    // --------------------------------------------------------
    // TFT CS
    // --------------------------------------------------------

    pinMode(BO4RD_TFT_CS, OUTPUT);
    digitalWrite(BO4RD_TFT_CS, HIGH);

    // --------------------------------------------------------
    // TOUCH CS
    // --------------------------------------------------------

    pinMode(BO4RD_TOUCH_CS, OUTPUT);
    digitalWrite(BO4RD_TOUCH_CS, HIGH);

    // --------------------------------------------------------
    // TOUCH IRQ
    // --------------------------------------------------------

    pinMode(BO4RD_TOUCH_IRQ, INPUT_PULLUP);

    // --------------------------------------------------------
    // SPI ESP8266
    // --------------------------------------------------------

    SPI.begin();

    Serial.println("[TOUCH] SPI.begin() OK");

    // --------------------------------------------------------
    // XPT2046
    // --------------------------------------------------------

    touch.begin();

    touch.setRotation(2);

    touchInitialized = true;

    Serial.println("[TOUCH] XPT2046 initialise");

    Serial.print("[TOUCH] CS  = GPIO");
    Serial.println(BO4RD_TOUCH_CS);

    Serial.print("[TOUCH] IRQ = GPIO");
    Serial.println(BO4RD_TOUCH_IRQ);

    Serial.print("[TOUCH] IRQ actuel = ");
    Serial.println(digitalRead(BO4RD_TOUCH_IRQ));
}

// ============================================================
// DISPONIBILITE
// ============================================================

bool touchAvailable()
{
    if (!touchInitialized)
    {
        return false;
    }

    digitalWrite(BO4RD_TFT_CS, HIGH);

    return touch.touched();
}

// ============================================================
// LECTURE TOUCH
// ============================================================

bool touchRead(
    TFT_eSPI &tft,
    int16_t &x,
    int16_t &y,
    uint16_t &pressure
)
{
    (void)tft;

    if (!touchInitialized)
    {
        return false;
    }

    // --------------------------------------------------------
    // TFT OFF
    // --------------------------------------------------------

    digitalWrite(BO4RD_TFT_CS, HIGH);

    // --------------------------------------------------------
    // TEST TOUCH
    // --------------------------------------------------------

    if (!touch.touched())
    {
        return false;
    }

    // --------------------------------------------------------
    // LECTURE XPT2046
    // --------------------------------------------------------

    TS_Point point = touch.getPoint();

    // --------------------------------------------------------
    // VALEURS BRUTES
    // --------------------------------------------------------

    x = point.x;
    y = point.y;
    pressure = point.z;

    // --------------------------------------------------------
    // LOG BRUT
    // --------------------------------------------------------

    Serial.print("[TOUCH] RAW X=");
    Serial.print(x);

    Serial.print(" Y=");
    Serial.print(y);

    Serial.print(" Z=");
    Serial.println(pressure);

    // --------------------------------------------------------
    // REJET DES VALEURS MANIFESTEMENT INVALIDES
    // --------------------------------------------------------

    if (
        x == 0 &&
        y == 0 &&
        pressure >= 4095
    )
    {
        Serial.println("[TOUCH] Valeur invalide ignoree");
        return false;
    }

    // --------------------------------------------------------
    // CONTACT VALIDE
    // --------------------------------------------------------

    return true;
}