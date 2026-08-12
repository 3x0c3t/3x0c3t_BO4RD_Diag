#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#include "touch.h"

// ============================================================
// XPT2046
// ============================================================

static XPT2046_Touchscreen touch(BO4RD_TOUCH_CS);

static bool touchInitialized = false;

// ============================================================
// INITIALISATION
// ============================================================

void touchInit(TFT_eSPI &tft)
{
    (void)tft;

    Serial.println("[TOUCH] Initialisation XPT2046");

    // --------------------------------------------------------
    // SPI ESP8266
    // --------------------------------------------------------

    SPI.begin();

    Serial.println("[TOUCH] SPI.begin() OK");

    // --------------------------------------------------------
    // CS tactile
    // --------------------------------------------------------

    pinMode(BO4RD_TOUCH_CS, OUTPUT);

    digitalWrite(BO4RD_TOUCH_CS, HIGH);

    // --------------------------------------------------------
    // IRQ
    // --------------------------------------------------------

    pinMode(BO4RD_TOUCH_IRQ, INPUT_PULLUP);

    // --------------------------------------------------------
    // Initialisation XPT2046
    // --------------------------------------------------------

    delay(20);

    if (touch.begin())
    {
        Serial.println("[TOUCH] XPT2046 initialise");
        touchInitialized = true;
    }
    else
    {
        Serial.println("[TOUCH] ERREUR XPT2046");
        touchInitialized = false;
        return;
    }

    // --------------------------------------------------------
    // Rotation
    // --------------------------------------------------------

    touch.setRotation(1);

    // --------------------------------------------------------
    // Informations
    // --------------------------------------------------------

    Serial.print("[TOUCH] CS   = ");
    Serial.println(BO4RD_TOUCH_CS);

    Serial.print("[TOUCH] SCK  = ");
    Serial.println(BO4RD_TOUCH_SCK);

    Serial.print("[TOUCH] MOSI = ");
    Serial.println(BO4RD_TOUCH_MOSI);

    Serial.print("[TOUCH] MISO = ");
    Serial.println(BO4RD_TOUCH_MISO);

    Serial.print("[TOUCH] IRQ  = ");
    Serial.println(BO4RD_TOUCH_IRQ);
}

// ============================================================
// ETAT
// ============================================================

bool touchIsInitialized()
{
    return touchInitialized;
}

// ============================================================
// LECTURE TOUCH
// ============================================================

bool touchRead(
    TFT_eSPI &tft,
    int16_t &x,
    int16_t &y,
    uint16_t &z
)
{
    (void)tft;

    if (!touchInitialized)
    {
        return false;
    }

    // --------------------------------------------------------
    // Pas de contact
    // --------------------------------------------------------

    if (!touch.touched())
    {
        return false;
    }

    // --------------------------------------------------------
    // Lecture XPT2046
    // --------------------------------------------------------

    TS_Point p = touch.getPoint();

    uint16_t rawX = p.x;
    uint16_t rawY = p.y;
    uint16_t rawZ = p.z;

    // --------------------------------------------------------
    // LOG RAW
    // --------------------------------------------------------

    Serial.print("[TOUCH] RAW X=");
    Serial.print(rawX);

    Serial.print(" Y=");
    Serial.print(rawY);

    Serial.print(" Z=");
    Serial.println(rawZ);

    // --------------------------------------------------------
    // Vérification lecture
    // --------------------------------------------------------

    if (
        rawX == 0 ||
        rawY == 0 ||
        rawX >= 4095 ||
        rawY >= 4095
    )
    {
        Serial.println("[TOUCH] Lecture RAW invalide");
        return false;
    }

    // --------------------------------------------------------
    // CALIBRATION PROVISOIRE
    //
    // Ces valeurs servent uniquement à obtenir
    // des coordonnées écran 240x320.
    //
    // Elles seront remplacées par les vraies valeurs
    // de calibration après le test RAW.
    // --------------------------------------------------------

    x = map(
        rawX,
        200,
        3900,
        0,
        239
    );

    y = map(
        rawY,
        200,
        3900,
        0,
        319
    );

    // --------------------------------------------------------
    // Limites écran
    // --------------------------------------------------------

    x = constrain(x, 0, 239);
    y = constrain(y, 0, 319);

    z = rawZ;

    // --------------------------------------------------------
    // LOG COORDONNEES ECRAN
    // --------------------------------------------------------

    Serial.print("[TOUCH] SCREEN X=");
    Serial.print(x);

    Serial.print(" Y=");
    Serial.print(y);

    Serial.print(" Z=");
    Serial.println(z);

    return true;
}