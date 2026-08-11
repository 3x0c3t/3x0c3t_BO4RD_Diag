#ifndef SCREEN_MAIN_H
#define SCREEN_MAIN_H

#include <Arduino.h>
#include <TFT_eSPI.h>

struct MainButton
{
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;
    const char *label;
    uint8_t screen;
};

#define MAIN_BUTTON_COUNT   5

#define MAIN_BUTTON_X       10
#define MAIN_BUTTON_START_Y 90
#define MAIN_BUTTON_WIDTH   220
#define MAIN_BUTTON_HEIGHT  38
#define MAIN_BUTTON_GAP     3

void mainScreenInit(TFT_eSPI &tft);
void mainScreenShow(TFT_eSPI &tft);
void mainScreenLoop(TFT_eSPI &tft);

bool mainScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
);

#endif