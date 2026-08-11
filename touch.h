#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>

// ============================================================
// 3x0c3t BO4RD
// TOUCH
// Gestion tactile via TFT_eSPI
// ============================================================

void touchInit();

bool touchAvailable();

bool touchRead(
    int16_t &x,
    int16_t &y,
    uint16_t &pressure
);

#endif