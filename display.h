#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>

// ============================================================
// INITIALISATION
// ============================================================

void displayInit(TFT_eSPI &tft);

// ============================================================
// CADRE COMMUN
// ============================================================

void displayDrawHeader(TFT_eSPI &tft);

void displayDrawHeaderSeparator(TFT_eSPI &tft);

void displayDrawLoadingBar(
    TFT_eSPI &tft,
    uint8_t progress
);

void displayDrawLoadingSeparator(TFT_eSPI &tft);

void displayDrawPageTitle(
    TFT_eSPI &tft,
    const char *title
);

void displayDrawTitleSeparator(TFT_eSPI &tft);

void displayDrawFrame(
    TFT_eSPI &tft,
    const char *title,
    uint8_t loadingProgress
);

// ============================================================
// COMPATIBILITE
// ============================================================

void displayDrawSystemBar(TFT_eSPI &tft);

#endif