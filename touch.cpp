#include "touch.h"
#include "config.h"

#include <SPI.h>
#include <XPT2046_Touchscreen.h>

XPT2046_Touchscreen touch(TOUCH_CS, TOUCH_IRQ);

void touchInit()
{
    touch.begin();
    touch.setRotation(0);
}

bool touchRead(int16_t &x, int16_t &y)
{
    if (!touch.touched())
        return false;

    TS_Point p = touch.getPoint();

    // Calibration provisoire.
    // À ajuster avec les valeurs RAW réelles.
    x = map(p.x, 200, 3900, 0, 239);
    y = map(p.y, 200, 3900, 0, 319);

    x = constrain(x, 0, 239);
    y = constrain(y, 0, 319);

    return true;
}
