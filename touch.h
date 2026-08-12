#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>
#include <TFT_eSPI.h>

// ============================================================
// XPT2046
// ============================================================

#define BO4RD_TOUCH_CS    0
#define BO4RD_TOUCH_SCK   14
#define BO4RD_TOUCH_MOSI  13
#define BO4RD_TOUCH_MISO  12
#define BO4RD_TOUCH_IRQ   5

// ============================================================
// API
// ============================================================

void touchInit(TFT_eSPI &tft);

bool touchIsInitialized();

bool touchRead(
    TFT_eSPI &tft,
    int16_t &x,
    int16_t &y,
    uint16_t &z
);

#endif