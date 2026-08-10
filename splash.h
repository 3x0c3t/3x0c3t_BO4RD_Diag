#ifndef SPLASH_H
#define SPLASH_H

#include <TFT_eSPI.h>

void splashInit(TFT_eSPI &tft);
void splashShow(TFT_eSPI &tft);
void splashWait();

#endif