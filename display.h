#ifndef DISPLAY_H
#define DISPLAY_H

#include <TFT_eSPI.h>


// ============================================================
// INITIALISATION
// ============================================================

void displayInit(TFT_eSPI &tft);


// ============================================================
// INTERFACE COMMUNE
// ============================================================

// Dessine le header
void displayDrawHeader(TFT_eSPI &tft);

// Dessine la ligne sous le header
void displayDrawHeaderSeparator(TFT_eSPI &tft);

// Dessine la barre de chargement
// progress = 0 a 100
void displayDrawLoadingBar(TFT_eSPI &tft, uint8_t progress);

// Dessine le titre de la page
void displayDrawPageTitle(TFT_eSPI &tft, const char *title);

// Dessine la ligne sous le titre
void displayDrawTitleSeparator(TFT_eSPI &tft);

// Dessine le footer
void displayDrawFooter(TFT_eSPI &tft);


// ============================================================
// CADRE COMPLET
// ============================================================
//
// Dessine toutes les zones communes.
//
// Header
// Separateur
// Barre chargement
// Titre
// Separateur titre
// Footer
//

void displayDrawFrame(
    TFT_eSPI &tft,
    const char *title,
    uint8_t loadingProgress
);


// ============================================================
// COMPATIBILITE
// ============================================================
//
// Ancien nom utilise dans le programme actuel.
//

void displayDrawSystemBar(TFT_eSPI &tft);


#endif