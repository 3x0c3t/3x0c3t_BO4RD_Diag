#ifndef TOUCH_H
#define TOUCH_H

#include <Arduino.h>
#include <TFT_eSPI.h>

// ============================================================
// XPT2046
// ============================================================

#define BO4RD_TOUCH_CS    0
#define BO4RD_TOUCH_IRQ   5

// ============================================================
// SPI
// ============================================================

#define BO4RD_TOUCH_SCK   14
#define BO4RD_TOUCH_MOSI  13
#define BO4RD_TOUCH_MISO  12

// ============================================================
// TFT
// ============================================================

#define BO4RD_TFT_CS      15

// ============================================================
// API
// ============================================================

void touchInit(TFT_eSPI &tft);

bool touchAvailable();

bool touchRead(
    TFT_eSPI &tft,
    int16_t &x,
    int16_t &y,
    uint16_t &pressure
);

#endif