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
//
// Zone : Y 0 -> 40
//
// HH:MM:SS - AAAA/MM/JJ              □ □ □ □
//

#define UI_HEADER_X            0
#define UI_HEADER_Y            0
#define UI_HEADER_WIDTH        TFT_SCREEN_WIDTH
#define UI_HEADER_HEIGHT       40


// ============================================================
// DATE / HEURE
// ============================================================

#define UI_DATETIME_X          4
#define UI_DATETIME_Y          20


// ============================================================
// INDICATEURS SYSTEME
// ============================================================
//
// 4 carres sur une seule ligne
//

#define UI_STATUS_COUNT        4

#define UI_STATUS_SIZE         10
#define UI_STATUS_GAP          4

#define UI_STATUS_AREA_WIDTH   \
    ((UI_STATUS_COUNT * UI_STATUS_SIZE) + \
     ((UI_STATUS_COUNT - 1) * UI_STATUS_GAP))

#define UI_STATUS_X            \
    (TFT_SCREEN_WIDTH - UI_STATUS_AREA_WIDTH - 4)

#define UI_STATUS_Y            15


// ============================================================
// SEPARATION HEADER
// ============================================================
//
// Ancien : Y = 45
// Nouveau : Y = 40
//
// Remontee : -5 px
//

#define UI_HEADER_SEPARATOR_X       0
#define UI_HEADER_SEPARATOR_Y       40
#define UI_HEADER_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_HEADER_SEPARATOR_HEIGHT  1


// ============================================================
// BARRE DE LOADING
// ============================================================
//
// Ancien : Y = 55
// Nouveau : Y = 50
//
// Remontee : -5 px
//

#define UI_LOADING_X           0
#define UI_LOADING_Y           50
#define UI_LOADING_WIDTH       TFT_SCREEN_WIDTH
#define UI_LOADING_HEIGHT      2


// ============================================================
// SEPARATION LOADING
// ============================================================
//
// Ancien : apres la barre
// Nouveau : Y = 53
//
// Barre : Y 50 -> 52
// Ligne : Y = 53
//

#define UI_LOADING_SEPARATOR_X       0
#define UI_LOADING_SEPARATOR_Y       53
#define UI_LOADING_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_LOADING_SEPARATOR_HEIGHT  1


// ============================================================
// TITRE PAGE
// ============================================================
//
// Ancien : Y = 65
// Nouveau : Y = 60
//
// Remontee : -5 px
//

#define UI_TITLE_X             0
#define UI_TITLE_Y             60
#define UI_TITLE_WIDTH         TFT_SCREEN_WIDTH
#define UI_TITLE_HEIGHT        15


// ============================================================
// SEPARATION TITRE
// ============================================================
//
// Ancien : Y = 80
// Nouveau : Y = 75
//
// Remontee : -5 px
//

#define UI_TITLE_SEPARATOR_X       0
#define UI_TITLE_SEPARATOR_Y       75
#define UI_TITLE_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_TITLE_SEPARATOR_HEIGHT  1


// ============================================================
// CONTENU
// ============================================================
//
// Ancien : Y = 81
// Nouveau : Y = 76
//
// Remontee : -5 px
//

#define UI_CONTENT_X           0
#define UI_CONTENT_Y           76
#define UI_CONTENT_WIDTH       TFT_SCREEN_WIDTH
#define UI_CONTENT_HEIGHT      \
    (TFT_SCREEN_HEIGHT - UI_CONTENT_Y)


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


#endif