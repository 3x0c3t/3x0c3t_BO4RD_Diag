#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

// ============================================================
// AFFICHAGE TFT
// ============================================================

#define TFT_ROTATION 2

// ============================================================
// DIMENSIONS
// ============================================================

#define TFT_SCREEN_WIDTH   240
#define TFT_SCREEN_HEIGHT  320

// ============================================================
// HEADER
// ============================================================

#define UI_HEADER_X          0
#define UI_HEADER_Y          0
#define UI_HEADER_WIDTH      TFT_SCREEN_WIDTH
#define UI_HEADER_HEIGHT     45

// ============================================================
// HEURE / DATE
// ============================================================

#define UI_DATETIME_X        5
#define UI_DATETIME_Y        8

// ============================================================
// CARRÉS / FONCTIONS
// ============================================================

#define UI_BUTTON_SIZE       30
#define UI_BUTTON_Y          7
#define UI_BUTTON_GAP        5
#define UI_BUTTON_COUNT      4

// ============================================================
// LIGNE SOUS HEADER
// ============================================================

#define UI_HEADER_LINE_X     0
#define UI_HEADER_LINE_Y     45
#define UI_HEADER_LINE_WIDTH TFT_SCREEN_WIDTH
#define UI_HEADER_LINE_HEIGHT 1

// ============================================================
// BARRE SYSTEME COMMUNE
// ============================================================

#define UI_BAR_X             0
#define UI_BAR_Y             55
#define UI_BAR_WIDTH         TFT_SCREEN_WIDTH
#define UI_BAR_HEIGHT        2
#define UI_BAR_COLOR         TFT_CYAN

// ============================================================
// DEUXIÈME LIGNE
// ============================================================

#define UI_TITLE_LINE_X      0
#define UI_TITLE_LINE_Y      80
#define UI_TITLE_LINE_WIDTH  TFT_SCREEN_WIDTH
#define UI_TITLE_LINE_HEIGHT 1

// ============================================================
// TITRE PAGE
// ============================================================

#define UI_TITLE_X            10
#define UI_TITLE_Y            65

// ============================================================
// ZONE CONTENU
// ============================================================

#define UI_CONTENT_X          0
#define UI_CONTENT_Y          81
#define UI_CONTENT_WIDTH      TFT_SCREEN_WIDTH
#define UI_CONTENT_HEIGHT     (TFT_SCREEN_HEIGHT - UI_CONTENT_Y)

#endif