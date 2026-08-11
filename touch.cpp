#include <Arduino.h>
#include <TFT_eSPI.h>

#include "touch.h"
#include "debug.h"

// ============================================================
// TFT GLOBAL
// ============================================================

extern TFT_eSPI tft;

// ============================================================
// ETAT
// ============================================================

static bool touchInitialized = false;

// ============================================================
// INITIALISATION
// ============================================================

void touchInit()
{
    LOGLN_TOUCH("[TOUCH] Initialisation TFT_eSPI tactile");

    touchInitialized = true;

    LOGLN_TOUCH("[TOUCH] Tactile initialise");
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

    uint16_t x;
    uint16_t y;

    return tft.getTouch(&x, &y);
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

    uint16_t tx;
    uint16_t ty;

    if (!tft.getTouch(&tx, &ty))
    {
        return false;
    }

    x = (int16_t)tx;
    y = (int16_t)ty;

    // TFT_eSPI ne fournit pas la pression avec getTouch().
    pressure = 1;

    // ========================================================
    // LOG IMPORTANT
    // ========================================================

    LOG_TOUCH("[TOUCH] X=");
    LOG_TOUCH(x);
    LOG_TOUCH(" Y=");
    LOG_TOUCH(y);
    LOG_TOUCH(" Z=");
    LOGLN_TOUCH(pressure);

    // ========================================================
    // LOG DETAIL
    // ========================================================

    LOG_TOUCH_DETAIL("[TOUCH] X = ");
    LOGLN_TOUCH_DETAIL(x);

    LOG_TOUCH_DETAIL("[TOUCH] Y = ");
    LOGLN_TOUCH_DETAIL(y);

    LOG_TOUCH_DETAIL("[TOUCH] Pression = ");
    LOGLN_TOUCH_DETAIL(pressure);

    return true;
}