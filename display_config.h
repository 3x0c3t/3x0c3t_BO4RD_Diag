#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

#define TFT_WIDTH  240
#define TFT_HEIGHT 320

#define TFT_ROTATION 2

// BARRE SYSTEME | Zone standardisee utilisee par tous les ecrans
#define SYSTEM_BAR_X       0
#define SYSTEM_BAR_Y       10
#define SYSTEM_BAR_WIDTH   TFT_WIDTH
#define SYSTEM_BAR_HEIGHT  2
#define SYSTEM_BAR_COLOR   TFT_CYAN

// SPLASH | Couleurs
#define SPLASH_BACKGROUND  TFT_BLACK
#define SPLASH_TEXT_COLOR  TFT_WHITE
#define SPLASH_ACCENT      TFT_CYAN

// SPLASH | Positions
#define SPLASH_BRAND_Y     100
#define SPLASH_MOTTO_Y     130
#define SPLASH_SEPARATOR_Y 165
#define SPLASH_PROJECT_Y   195
#define SPLASH_VERSION_Y   225
#define SPLASH_DATE_Y      250

// SPLASH | Duree
#define SPLASH_DURATION_MS 3000

#endif