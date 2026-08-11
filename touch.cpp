#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#include "touch.h"
#include "debug.h"

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

void touchInit()
{
    // --------------------------------------------------------
    // LOG IMPORTANT
    // --------------------------------------------------------

    LOGLN_TOUCH(
        "[TOUCH] Initialisation XPT2046"
    );

    // --------------------------------------------------------
    // TFT CS
    // --------------------------------------------------------

    pinMode(
        BO4RD_TFT_CS,
        OUTPUT
    );

    digitalWrite(
        BO4RD_TFT_CS,
        HIGH
    );

    // --------------------------------------------------------
    // TOUCH CS
    // --------------------------------------------------------

    pinMode(
        BO4RD_TOUCH_CS,
        OUTPUT
    );

    digitalWrite(
        BO4RD_TOUCH_CS,
        HIGH
    );

    // --------------------------------------------------------
    // SPI
    // --------------------------------------------------------

    SPI.begin();

    LOGLN_TOUCH_DETAIL(
        "[TOUCH] SPI.begin() OK"
    );

    // --------------------------------------------------------
    // XPT2046
    // --------------------------------------------------------

    digitalWrite(
        BO4RD_TFT_CS,
        HIGH
    );

    digitalWrite(
        BO4RD_TOUCH_CS,
        HIGH
    );

    touch.begin(SPI);

    touchInitialized = true;

    // --------------------------------------------------------
    // LOG
    // --------------------------------------------------------

    LOGLN_TOUCH(
        "[TOUCH] XPT2046 initialise"
    );

    LOGLN_TOUCH_DETAIL(
        "[TOUCH] touch.begin(SPI) OK"
    );
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
    int16_t &x,
    int16_t &y,
    uint16_t &pressure
)
{
    if (!touchInitialized)
    {
        return false;
    }

    // --------------------------------------------------------
    // TEST APPUI
    // --------------------------------------------------------

    if (!touch.touched())
    {
        return false;
    }

    // --------------------------------------------------------
    // LECTURE
    // --------------------------------------------------------

    TS_Point p = touch.getPoint();

    // --------------------------------------------------------
    // RESULTAT
    // --------------------------------------------------------

    x = p.x;
    y = p.y;
    pressure = p.z;

    // --------------------------------------------------------
    // LOG NIVEAU 1
    // --------------------------------------------------------

    LOG_TOUCH("[TOUCH] X=");
    LOG_TOUCH(x);

    LOG_TOUCH(" Y=");
    LOG_TOUCH(y);

    LOG_TOUCH(" Z=");
    LOGLN_TOUCH(pressure);

    // --------------------------------------------------------
    // LOG NIVEAU 2
    // --------------------------------------------------------

    LOG_TOUCH_DETAIL("[TOUCH] RAW X = ");
    LOGLN_TOUCH_DETAIL(p.x);

    LOG_TOUCH_DETAIL("[TOUCH] RAW Y = ");
    LOGLN_TOUCH_DETAIL(p.y);

    LOG_TOUCH_DETAIL("[TOUCH] RAW Z = ");
    LOGLN_TOUCH_DETAIL(p.z);

    return true;
}