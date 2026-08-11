#ifndef DISPLAY_CONFIG_H
#define DISPLAY_CONFIG_H

// ============================================================
// 3x0c3t BO4RD
// CONFIGURATION STANDARD DE L'INTERFACE TFT
//
// Resolution : 240 x 320
// Toutes les pages utilisent les memes zones.
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
// Zone commune a toutes les pages.
//
// Y = 0
// Hauteur = 40
//
// +----------------------------------------+
// | HEADER                                 |
// +----------------------------------------+
//

#define UI_HEADER_X            0
#define UI_HEADER_Y            0
#define UI_HEADER_WIDTH        TFT_SCREEN_WIDTH
#define UI_HEADER_HEIGHT       40


// ============================================================
// HEURE
// ============================================================

#define UI_TIME_X              5
#define UI_TIME_Y              5


// ============================================================
// DATE
// ============================================================

#define UI_DATE_X              5
#define UI_DATE_Y              22


// ============================================================
// INDICATEURS SYSTEME
// ============================================================
//
// Zone reservee a droite du header.
//
// Exemple futur :
// WiFi / SD / Touch / Batterie / etc.
//

#define UI_STATUS_X            175
#define UI_STATUS_Y            5
#define UI_STATUS_WIDTH        60
#define UI_STATUS_HEIGHT       30


// ============================================================
// SEPARATEUR HEADER
// ============================================================

#define UI_HEADER_SEPARATOR_X       0
#define UI_HEADER_SEPARATOR_Y       40
#define UI_HEADER_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_HEADER_SEPARATOR_HEIGHT  1


// ============================================================
// BARRE DE CHARGEMENT
// ============================================================
//
// Barre commune a toutes les pages.
//
// Y = 41
// Hauteur = 4
//
// Progression : 0 -> 100
//

#define UI_LOADING_X           0
#define UI_LOADING_Y           41
#define UI_LOADING_WIDTH       TFT_SCREEN_WIDTH
#define UI_LOADING_HEIGHT      4


// ============================================================
// ESPACE ENTRE BARRE ET TITRE
// ============================================================

#define UI_TITLE_TOP           49


// ============================================================
// TITRE DE PAGE
// ============================================================
//
// Zone commune a toutes les pages.
//

#define UI_TITLE_X             0
#define UI_TITLE_Y             49
#define UI_TITLE_WIDTH         TFT_SCREEN_WIDTH
#define UI_TITLE_HEIGHT        30


// ============================================================
// SEPARATEUR TITRE
// ============================================================

#define UI_TITLE_SEPARATOR_X       0
#define UI_TITLE_SEPARATOR_Y       79
#define UI_TITLE_SEPARATOR_WIDTH   TFT_SCREEN_WIDTH
#define UI_TITLE_SEPARATOR_HEIGHT  1


// ============================================================
// ZONE DE CONTENU
// ============================================================
//
// C'est ici que les pages dessinent leur contenu.
//
// Une page ne doit pas modifier ces coordonnees.
//

#define UI_CONTENT_X           0
#define UI_CONTENT_Y           80
#define UI_CONTENT_WIDTH       TFT_SCREEN_WIDTH
#define UI_CONTENT_HEIGHT      220


// ============================================================
// FOOTER
// ============================================================
//
// Zone commune reservee au bas de l'ecran.
//

#define UI_FOOTER_X            0
#define UI_FOOTER_Y            300
#define UI_FOOTER_WIDTH        TFT_SCREEN_WIDTH
#define UI_FOOTER_HEIGHT       20


// ============================================================
// COULEURS INTERFACE
// ============================================================

#define UI_BACKGROUND_COLOR    TFT_BLACK

#define UI_HEADER_COLOR        TFT_BLACK

#define UI_SEPARATOR_COLOR     TFT_CYAN

#define UI_LOADING_BACKGROUND  TFT_DARKGREY
#define UI_LOADING_COLOR       TFT_CYAN

#define UI_TITLE_COLOR         TFT_WHITE

#define UI_CONTENT_COLOR       TFT_WHITE

#define UI_FOOTER_COLOR        TFT_BLACK


#endif