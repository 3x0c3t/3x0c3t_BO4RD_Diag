#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include <TFT_eSPI.h>

void mainScreenInit(TFT_eSPI &tft);
void mainScreenShow(TFT_eSPI &tft);
void mainScreenLoop(TFT_eSPI &tft);

#endif