#ifndef SCREEN_TACTILE_H
#define SCREEN_TACTILE_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

#define TOUCH_CS 0
#define TOUCH_IRQ 5

void touchInit();
bool touchAvailable();

bool touchRead(
    int16_t &x,
    int16_t &y,
    uint16_t &pressure
);

#endif