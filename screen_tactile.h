#ifndef SCREEN_TACTILE_H
#define SCREEN_TACTILE_H

#include <Arduino.h>

#define TOUCH_CS 0

void touchInit();

bool touchAvailable();

bool touchRead(
    int16_t &x,
    int16_t &y,
    uint16_t &pressure
);

#endif