#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>

void displayInit(TFT_eSPI &tft);
void displayDrawSystemBar(TFT_eSPI &tft);

#endif