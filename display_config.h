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

#define UI_HEADER_X            0
#define UI_HEADER_Y            0
#define UI_HEADER_WIDTH        TFT_SCREEN_WIDTH
#define UI_HEADER_HEIGHT       32


// ============================================================
// DATE / HEURE
// ============================================================

#define UI_DATETIME_X          4
#define UI_DATETIME_Y          16


// ============================================================
// INDICATEURS
// ============================================================

#define UI_STATUS_COUNT        4

#define UI_STATUS_SIZE         10
#define UI_STATUS_GAP          4

#define UI_STATUS_AREA_WIDTH   \
    ((UI_STATUS_COUNT * UI_STATUS_SIZE) + \
     ((UI_STATUS_COUNT - 1) * UI_STATUS_GAP))

#define UI_STATUS_X            \
    (TFT_SCREEN_WIDTH - UI_STATUS_AREA_WIDTH - 4)

#define UI_STATUS_Y            11


// ============================================================
// SEPARATION HEADER
// ============================================================

#define UI_HEADER_SEPARATOR_X       0
#define UI_HEADER_SEPARATOR_Y       32
#define UI_HEADER_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_HEADER_SEPARATOR_HEIGHT  1


// ============================================================
// BARRE DE LOADING
// ============================================================

#define UI_LOADING_X           0
#define UI_LOADING_Y           34
#define UI_LOADING_WIDTH       TFT_SCREEN_WIDTH
#define UI_LOADING_HEIGHT      4


// ============================================================
// SEPARATION LOADING
// ============================================================

#define UI_LOADING_SEPARATOR_X       0
#define UI_LOADING_SEPARATOR_Y       39
#define UI_LOADING_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_LOADING_SEPARATOR_HEIGHT  1


// ============================================================
// TITRE PAGE
// ============================================================

#define UI_TITLE_X             0
#define UI_TITLE_Y             40
#define UI_TITLE_WIDTH         TFT_SCREEN_WIDTH
#define UI_TITLE_HEIGHT        24


// ============================================================
// SEPARATION TITRE
// ============================================================

#define UI_TITLE_SEPARATOR_X       0
#define UI_TITLE_SEPARATOR_Y       64
#define UI_TITLE_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_TITLE_SEPARATOR_HEIGHT  1


// ============================================================
// CONTENU
// ============================================================

#define UI_CONTENT_X           0
#define UI_CONTENT_Y           65
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

#define UI_STATUS_OFF_COLOR   TFT_DARKGREY
#define UI_STATUS_ON_COLOR    TFT_GREEN


#endif