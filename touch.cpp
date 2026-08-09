#include "touch.h"

#include <Arduino.h>
#include <SPI.h>

// =====================================================
// OBJET XPT2046
// =====================================================

XPT2046_Touchscreen ts(
    TOUCH_CS,
    TOUCH_IRQ
);

// =====================================================
// INITIALISATION
// =====================================================

void touchInit()
{
    Serial.println();
    Serial.println("================================");
    Serial.println("[TOUCH] INITIALISATION XPT2046");
    Serial.println("================================");

    Serial.println("[TOUCH] Brochage :");

    Serial.print("[TOUCH] CS   = GPIO ");
    Serial.println(TOUCH_CS);

    Serial.print("[TOUCH] IRQ  = GPIO ");
    Serial.println(TOUCH_IRQ);

    Serial.println("[TOUCH] SCK  = GPIO14");
    Serial.println("[TOUCH] MISO = GPIO12");
    Serial.println("[TOUCH] MOSI = GPIO13");

    // -------------------------------------------------
    // CS
    // -------------------------------------------------

    pinMode(TOUCH_CS, OUTPUT);
    digitalWrite(TOUCH_CS, HIGH);

    // -------------------------------------------------
    // IRQ
    // -------------------------------------------------

    pinMode(TOUCH_IRQ, INPUT);

    // -------------------------------------------------
    // SPI
    // -------------------------------------------------

    Serial.println("[TOUCH] SPI.begin()");

    SPI.begin();

    delay(100);

    // -------------------------------------------------
    // XPT2046
    // -------------------------------------------------

    Serial.println("[TOUCH] ts.begin()");

    if (ts.begin())
    {
        Serial.println("[TOUCH] XPT2046 : OK");

        ts.setRotation(1);

        Serial.println("[TOUCH] Rotation = 1");
    }
    else
    {
        Serial.println("[TOUCH] XPT2046 : ERREUR");
    }

    // -------------------------------------------------
    // IRQ
    // -------------------------------------------------

    Serial.print("[TOUCH] IRQ initial = ");
    Serial.println(digitalRead(TOUCH_IRQ));

    Serial.println();
    Serial.println("[TOUCH] INITIALISATION TERMINEE");
    Serial.println("================================");
}

// =====================================================
// LECTURE
// =====================================================

bool touchRead(
    int16_t &screenX,
    int16_t &screenY,
    uint16_t &pressure
)
{
    // -------------------------------------------------
    // Pas de pression
    // -------------------------------------------------

    if (!ts.touched())
    {
        return false;
    }

    // -------------------------------------------------
    // Lecture XPT2046
    // -------------------------------------------------

    TS_Point p = ts.getPoint();

    pressure = p.z;

    // -------------------------------------------------
    // RAW
    // -------------------------------------------------

    Serial.println();
    Serial.println("[TOUCH] -------------------------------");

    Serial.print("[TOUCH] RAW X = ");
    Serial.println(p.x);

    Serial.print("[TOUCH] RAW Y = ");
    Serial.println(p.y);

    Serial.print("[TOUCH] RAW Z = ");
    Serial.println(p.z);

    // -------------------------------------------------
    // Conversion X
    // -------------------------------------------------

    screenX = map(
        p.x,
        TOUCH_RAW_X_MIN,
        TOUCH_RAW_X_MAX,
        0,
        TOUCH_SCREEN_WIDTH - 1
    );

    // -------------------------------------------------
    // Conversion Y
    // -------------------------------------------------

    screenY = map(
        p.y,
        TOUCH_RAW_Y_MIN,
        TOUCH_RAW_Y_MAX,
        0,
        TOUCH_SCREEN_HEIGHT - 1
    );

    // -------------------------------------------------
    // Limites
    // -------------------------------------------------

    screenX = constrain(
        screenX,
        0,
        TOUCH_SCREEN_WIDTH - 1
    );

    screenY = constrain(
        screenY,
        0,
        TOUCH_SCREEN_HEIGHT - 1
    );

    // -------------------------------------------------
    // Debug
    // -------------------------------------------------

    touchDebug(
        screenX,
        screenY,
        pressure
    );

    return true;
}

// =====================================================
// DEBUG
// =====================================================

void touchDebug(
    int16_t screenX,
    int16_t screenY,
    uint16_t pressure
)
{
    Serial.print("[TOUCH] SCREEN X = ");
    Serial.println(screenX);

    Serial.print("[TOUCH] SCREEN Y = ");
    Serial.println(screenY);

    Serial.print("[TOUCH] PRESSURE = ");
    Serial.println(pressure);

    Serial.print("[TOUCH] IRQ = ");
    Serial.println(
        digitalRead(TOUCH_IRQ)
    );

    Serial.println("[TOUCH] -------------------------------");
}
