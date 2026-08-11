#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>

#include "touch.h"

// ============================================================
// XPT2046
// ============================================================

static XPT2046_Touchscreen touch(
    BO4RD_TOUCH_CS
);

// ============================================================
// ETAT
// ============================================================

static bool touchInitialized = false;

// ============================================================
// INITIALISATION
// ============================================================

void touchInit(
    TFT_eSPI &tft
)
{
    // --------------------------------------------------------
    // TFT deselectionne
    // --------------------------------------------------------

    tft.setTouch(nullptr);

    // --------------------------------------------------------
    // GPIO
    // --------------------------------------------------------

    pinMode(BO4RD_TOUCH_CS, OUTPUT);

    digitalWrite(
        BO4RD_TOUCH_CS,
        HIGH
    );

    // --------------------------------------------------------
    // SPI materiel ESP8266
    // GPIO14 = SCK
    // GPIO12 = MISO
    // GPIO13 = MOSI
    // --------------------------------------------------------

    SPI.begin();

    // --------------------------------------------------------
    // XPT2046
    // --------------------------------------------------------

    touch.begin(SPI);

    touchInitialized = true;
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

    return touch.touched();
}

// ============================================================
// LECTURE
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

    if (!touch.touched())
    {
        return false;
    }

    TS_Point p = touch.getPoint();

    x = p.x;
    y = p.y;
    pressure = p.z;

    return true;
}