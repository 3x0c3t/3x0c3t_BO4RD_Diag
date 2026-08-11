#ifndef SCREEN_SYSTEME_H
#define SCREEN_SYSTEME_H

#include <Arduino.h>
#include <TFT_eSPI.h>

void systemeScreenInit(TFT_eSPI &tft);
void systemeScreenShow(TFT_eSPI &tft);
void systemeScreenLoop(TFT_eSPI &tft);

#endif