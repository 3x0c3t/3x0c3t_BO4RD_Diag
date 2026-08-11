#ifndef SCREEN_WIFI_H
#define SCREEN_WIFI_H

#include <Arduino.h>
#include <TFT_eSPI.h>

void wifiScreenInit(
    TFT_eSPI &tft
);

void wifiScreenShow(
    TFT_eSPI &tft
);

void wifiScreenLoop(
    TFT_eSPI &tft
);

bool wifiScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
);

#endif