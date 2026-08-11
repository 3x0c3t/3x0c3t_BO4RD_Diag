// DEBUG 20260812-00:12


#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#include "touch.h"

static XPT2046_Touchscreen touch(BO4RD_TOUCH_CS);

static bool touchInitialized = false;

void touchInit()
{
    Serial.println();
    Serial.println("[TOUCH] INIT XPT2046");

    // TFT CS désactivé
    pinMode(BO4RD_TFT_CS, OUTPUT);
    digitalWrite(BO4RD_TFT_CS, HIGH);

    // Touch CS désactivé
    pinMode(BO4RD_TOUCH_CS, OUTPUT);
    digitalWrite(BO4RD_TOUCH_CS, HIGH);

    SPI.begin();

    Serial.println("[TOUCH] SPI OK");

    touch.begin(SPI);

    touchInitialized = true;

    Serial.println("[TOUCH] XPT2046 BEGIN OK");
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

    x = p.x;
    y = p.y;
    pressure = p.z;

    Serial.print("[TOUCH] RAW X=");
    Serial.print(p.x);

    Serial.print(" Y=");
    Serial.print(p.y);

    Serial.print(" Z=");
    Serial.println(p.z);

    return true;
}