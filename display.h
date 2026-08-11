#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <TFT_eSPI.h>


// ============================================================
// INITIALISATION
// ============================================================

void displayInit(
    TFT_eSPI &tft
);


// ============================================================
// HEADER
// ============================================================

void displayDrawHeader(
    TFT_eSPI &tft
);

void displayDrawHeaderSeparator(
    TFT_eSPI &tft
);


// ============================================================
// LOADING
// ============================================================

void displayDrawLoadingBar(
    TFT_eSPI &tft,
    uint8_t progress
);

void displayDrawLoadingSeparator(
    TFT_eSPI &tft
);


// ============================================================
// TITRE
// ============================================================

void displayDrawPageTitle(
    TFT_eSPI &tft,
    const char *title
);

void displayDrawTitleSeparator(
    TFT_eSPI &tft
);


// ============================================================
// CADRE COMMUN
// ============================================================

void displayDrawFrame(
    TFT_eSPI &tft,
    const char *title,
    uint8_t loadingProgress
);


// ============================================================
// COMPATIBILITE
// ============================================================

void displayDrawSystemBar(
    TFT_eSPI &tft
);

#endif