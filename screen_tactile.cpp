#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#include "screen_tactile.h"

static XPT2046_Touchscreen touch(TOUCH_CS);

static bool touchInitialized = false;

void touchInit()
{
    Serial.println();
    Serial.println("========================================");
    Serial.println("[TOUCH] TEST SPI XPT2046");
    Serial.println("========================================");

    Serial.println("[TOUCH] Brochage utilise :");
    Serial.println("[TOUCH] CS   = GPIO0  / D3");
    Serial.println("[TOUCH] SCK  = GPIO14 / D5");
    Serial.println("[TOUCH] MOSI = GPIO13 / D7");
    Serial.println("[TOUCH] MISO = GPIO12 / D6");

    // --------------------------------------------------------
    // DESACTIVATION TFT
    // --------------------------------------------------------

    // TFT CS = GPIO15 / D8
    pinMode(15, OUTPUT);
    digitalWrite(15, HIGH);

    Serial.println("[TOUCH] TFT CS force HIGH");

    // --------------------------------------------------------
    // TOUCH CS
    // --------------------------------------------------------

    pinMode(TOUCH_CS, OUTPUT);
    digitalWrite(TOUCH_CS, HIGH);

    Serial.println("[TOUCH] Touch CS configure");

    // --------------------------------------------------------
    // SPI
    // --------------------------------------------------------

    SPI.begin();

    Serial.println("[TOUCH] SPI.begin()");

    // --------------------------------------------------------
    // XPT2046
    // --------------------------------------------------------

    touch.begin();

    touchInitialized = true;

    Serial.println("[TOUCH] touch.begin() OK");
    Serial.println("========================================");
    Serial.println();
}

bool touchAvailable()
{
    if (!touchInitialized)
    {
        return false;
    }

    return touch.touched();
}

bool touchRead(
    int16_t &x,
    int16_t &y,
    uint16_t &pressure
)
{
    if (!touchInitialized)
    {
        return false;
    }

    if (!touch.touched())
    {
        return false;
    }

    TS_Point p = touch.getPoint();

    Serial.println();
    Serial.println("[TOUCH] ================================");
    Serial.println("[TOUCH] LECTURE XPT2046");

    Serial.print("[TOUCH] RAW X = ");
    Serial.println(p.x);

    Serial.print("[TOUCH] RAW Y = ");
    Serial.println(p.y);

    Serial.print("[TOUCH] RAW Z = ");
    Serial.println(p.z);

    x = p.x;
    y = p.y;
    pressure = p.z;

    Serial.println("[TOUCH] ================================");

    return true;
}