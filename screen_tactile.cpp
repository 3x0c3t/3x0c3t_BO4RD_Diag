#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#include "screen_tactile.h"

static XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);

static bool touchInitialized = false;

void touchInit()
{
    Serial.println();
    Serial.println("[TOUCH] Initialisation XPT2046...");
    Serial.print("[TOUCH] CS  = GPIO");
    Serial.println(TOUCH_CS);
    Serial.print("[TOUCH] IRQ = GPIO");
    Serial.println(TOUCH_IRQ);

    touch.begin();

    touchInitialized = true;

    Serial.println("[TOUCH] XPT2046 initialise");
    Serial.println("[TOUCH] Touch pret");
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

    int16_t rawX = p.x;
    int16_t rawY = p.y;

    pressure = p.z;

    // --------------------------------------------------------
    // CALIBRATION XPT2046
    // A ajuster si necessaire apres test physique
    // --------------------------------------------------------

    const int16_t RAW_X_MIN = 200;
    const int16_t RAW_X_MAX = 3900;

    const int16_t RAW_Y_MIN = 200;
    const int16_t RAW_Y_MAX = 3900;

    x = map(
        rawX,
        RAW_X_MIN,
        RAW_X_MAX,
        0,
        239
    );

    y = map(
        rawY,
        RAW_Y_MIN,
        RAW_Y_MAX,
        0,
        319
    );

    x = constrain(x, 0, 239);
    y = constrain(y, 0, 319);

    Serial.print("[TOUCH] RAW X=");
    Serial.print(rawX);

    Serial.print(" Y=");
    Serial.print(rawY);

    Serial.print(" Z=");
    Serial.print(pressure);

    Serial.print(" -> SCREEN X=");
    Serial.print(x);

    Serial.print(" Y=");
    Serial.println(y);

    return true;
}