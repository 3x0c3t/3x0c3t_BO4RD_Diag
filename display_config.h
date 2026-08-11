#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

// ============================================================
// 3x0c3t BO4RD
// STANDARD UI
// TFT 240 x 320
// ============================================================


// ============================================================
// ECRAN
// ============================================================

#define TFT_SCREEN_WIDTH       240
#define TFT_SCREEN_HEIGHT      320
#define TFT_ROTATION           2


// ============================================================
// HEADER
// ============================================================
// Hauteur : 20 px
// Y : 0 -> 19
// ============================================================

#define UI_HEADER_X            0
#define UI_HEADER_Y            0
#define UI_HEADER_WIDTH        TFT_SCREEN_WIDTH
#define UI_HEADER_HEIGHT       20


// ============================================================
// DATE / HEURE
// ============================================================

#define UI_DATETIME_X          4
#define UI_DATETIME_Y          10


// ============================================================
// INDICATEURS
// ============================================================
// 4 carrés sur une seule ligne
// ============================================================

#define UI_STATUS_COUNT        4
#define UI_STATUS_SIZE         10
#define UI_STATUS_GAP          4

#define UI_STATUS_AREA_WIDTH   ((UI_STATUS_COUNT * UI_STATUS_SIZE) + ((UI_STATUS_COUNT - 1) * UI_STATUS_GAP))

#define UI_STATUS_X            (TFT_SCREEN_WIDTH - UI_STATUS_AREA_WIDTH - 4)
#define UI_STATUS_Y            5


// ============================================================
// SEPARATION HEADER
// ============================================================
// Y = 20
// Hauteur = 1 px
// ============================================================

#define UI_HEADER_SEPARATOR_X       0
#define UI_HEADER_SEPARATOR_Y       20
#define UI_HEADER_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_HEADER_SEPARATOR_HEIGHT  1


// ============================================================
// BARRE DE LOADING
// ============================================================
// Y = 21 -> 22
// Hauteur = 2 px
// ============================================================

#define UI_LOADING_X           0
#define UI_LOADING_Y           21
#define UI_LOADING_WIDTH       TFT_SCREEN_WIDTH
#define UI_LOADING_HEIGHT      2


// ============================================================
// SEPARATION LOADING
// ============================================================
// Y = 23
// Hauteur = 1 px
// ============================================================

#define UI_LOADING_SEPARATOR_X       0
#define UI_LOADING_SEPARATOR_Y       23
#define UI_LOADING_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_LOADING_SEPARATOR_HEIGHT  1


// ============================================================
// TITRE PAGE
// ============================================================
// Y = 24 -> 39
// Hauteur = 16 px
// ============================================================

#define UI_TITLE_X             0
#define UI_TITLE_Y             24
#define UI_TITLE_WIDTH         TFT_SCREEN_WIDTH
#define UI_TITLE_HEIGHT        16


// ============================================================
// SEPARATION TITRE
// ============================================================
// Y = 40
// Hauteur = 1 px
// ============================================================

#define UI_TITLE_SEPARATOR_X       0
#define UI_TITLE_SEPARATOR_Y       40
#define UI_TITLE_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_TITLE_SEPARATOR_HEIGHT  1


// ============================================================
// CONTENU
// ============================================================
// Y = 41 -> 319
// Hauteur = 279 px
// ============================================================

#define UI_CONTENT_X           0
#define UI_CONTENT_Y           41
#define UI_CONTENT_WIDTH       TFT_SCREEN_WIDTH
#define UI_CONTENT_HEIGHT      (TFT_SCREEN_HEIGHT - UI_CONTENT_Y)


// ============================================================
// COULEURS
// ============================================================

#define UI_BACKGROUND_COLOR    TFT_BLACK

#define UI_SEPARATOR_COLOR     TFT_CYAN

#define UI_LOADING_BACKGROUND  TFT_DARKGREY
#define UI_LOADING_COLOR       TFT_CYAN

#define UI_HEADER_TEXT_COLOR   TFT_WHITE
#define UI_TITLE_COLOR         TFT_WHITE

#define UI_STATUS_OFF_COLOR    TFT_DARKGREY
#define UI_STATUS_ON_COLOR     TFT_GREEN


// ============================================================
// FIN
// ============================================================

#endif