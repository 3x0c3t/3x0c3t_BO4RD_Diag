#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>
#include <XPT2046_Touchscreen.h>

// =====================================================
// BROCHAGE 3x0c3t BO4RD
// =====================================================

#define TOUCH_CS  0    // GPIO0 / D3
#define TOUCH_IRQ 5    // GPIO5 / D1

// =====================================================
// ECRAN
// =====================================================

#define TOUCH_SCREEN_WIDTH  240
#define TOUCH_SCREEN_HEIGHT 320

// =====================================================
// CALIBRATION XPT2046
// =====================================================

#define TOUCH_RAW_X_MIN 388
#define TOUCH_RAW_X_MAX 3701

#define TOUCH_RAW_Y_MIN 477
#define TOUCH_RAW_Y_MAX 3794

// =====================================================
// OBJET XPT2046
// =====================================================

extern XPT2046_Touchscreen ts;

// =====================================================
// INITIALISATION
// =====================================================

void touchInit();

// =====================================================
// LECTURE
// =====================================================

bool touchRead(
    int16_t &screenX,
    int16_t &screenY,
    uint16_t &pressure
);

// =====================================================
// DEBUG
// =====================================================

void touchDebug(
    int16_t screenX,
    int16_t screenY,
    uint16_t pressure
);

#endif
