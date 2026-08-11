#ifndef MAIN_SCREEN_H
#define MAIN_SCREEN_H

#include <TFT_eSPI.h>

// ============================================================
// 3x0c3t BO4RD
// MAIN SCREEN
// ============================================================


// ============================================================
// NOMBRE DE BOUTONS
// ============================================================

#define MAIN_BUTTON_COUNT       5


// ============================================================
// GEOMETRIE DES BOUTONS
// ============================================================

#define MAIN_BUTTON_X           10
#define MAIN_BUTTON_WIDTH       220
#define MAIN_BUTTON_HEIGHT      45
#define MAIN_BUTTON_GAP         8
#define MAIN_BUTTON_START_Y     50


// ============================================================
// STRUCTURE BOUTON
// ============================================================

struct MainButton
{
    int16_t x;
    int16_t y;
    int16_t width;
    int16_t height;

    const char *label;

    // Identifiant de la page
    uint8_t screen;
};


// ============================================================
// INITIALISATION
// ============================================================

void mainScreenInit(TFT_eSPI &tft);


// ============================================================
// AFFICHAGE
// ============================================================

void mainScreenShow(TFT_eSPI &tft);


// ============================================================
// BOUCLE
// ============================================================

void mainScreenLoop(TFT_eSPI &tft);


// ============================================================
// TACTILE
// ============================================================
//
// Retourne true si un bouton a été touché.
// La variable "screen" reçoit le numéro de la page.
//
// ============================================================

bool mainScreenTouch(
    int16_t x,
    int16_t y,
    uint8_t &screen
);


#endif