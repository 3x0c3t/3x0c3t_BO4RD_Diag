#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>

// ============================================================
// TOUCH
// ============================================================

void touchInit();

bool touchRead(
    int16_t &x,
    int16_t &y,
    uint16_t &z
);

#endif