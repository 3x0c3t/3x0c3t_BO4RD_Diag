#include "display.h"
#include "display_config.h"


// ============================================================
// INITIALISATION
// ============================================================

void displayInit(TFT_eSPI &tft)
{
    tft.init();

    tft.setRotation(TFT_ROTATION);

    tft.fillScreen(UI_BACKGROUND_COLOR);
}


// ============================================================
// HEADER
// ============================================================
//
// HH:MM:SS - AAAA/MM/JJ                □ □ □ □
//
// Les donnees reelles heure/date seront ajoutees plus tard.
// Pour le moment, affichage de placeholders.
// ============================================================

void displayDrawHeader(TFT_eSPI &tft)
{
    // --------------------------------------------------------
    // Fond du header
    // --------------------------------------------------------

    tft.fillRect(
        UI_HEADER_X,
        UI_HEADER_Y,
        UI_HEADER_WIDTH,
        UI_HEADER_HEIGHT,
        UI_BACKGROUND_COLOR
    );


    // --------------------------------------------------------
    // Date / heure
    // --------------------------------------------------------

    tft.setTextColor(
        UI_HEADER_TEXT_COLOR,
        UI_BACKGROUND_COLOR
    );

    tft.setTextDatum(ML_DATUM);
    tft.setTextSize(1);

    tft.drawString(
        "--:--:-- - ----/--/--",
        UI_DATETIME_X,
        UI_DATETIME_Y
    );


    // --------------------------------------------------------
    // Indicateurs systeme
    // --------------------------------------------------------

    for (int i = 0; i < UI_STATUS_COUNT; i++)
    {
        int x =
            UI_STATUS_X +
            (i * (UI_STATUS_SIZE + UI_STATUS_GAP));

        tft.drawRect(
            x,
            UI_STATUS_Y,
            UI_STATUS_SIZE,
            UI_STATUS_SIZE,
            UI_STATUS_OFF_COLOR
        );
    }
}


// ============================================================
// SEPARATEUR HEADER
// ============================================================

void displayDrawHeaderSeparator(TFT_eSPI &tft)
{
    tft.fillRect(
        UI_HEADER_SEPARATOR_X,
        UI_HEADER_SEPARATOR_Y,
        UI_HEADER_SEPARATOR_WIDTH,
        UI_HEADER_SEPARATOR_HEIGHT,
        UI_SEPARATOR_COLOR
    );
}


// ============================================================
// BARRE DE LOADING
// ============================================================
//
// progress : 0 -> 100
// ============================================================

void displayDrawLoadingBar(
    TFT_eSPI &tft,
    uint8_t progress
)
{
    // --------------------------------------------------------
    // Protection
    // --------------------------------------------------------

    if (progress > 100)
    {
        progress = 100;
    }


    // --------------------------------------------------------
    // Fond
    // --------------------------------------------------------

    tft.fillRect(
        UI_LOADING_X,
        UI_LOADING_Y,
        UI_LOADING_WIDTH,
        UI_LOADING_HEIGHT,
        UI_LOADING_BACKGROUND
    );


    // --------------------------------------------------------
    // Progression
    // --------------------------------------------------------

    uint16_t progressWidth =
        (UI_LOADING_WIDTH * progress) / 100;


    if (progressWidth > 0)
    {
        tft.fillRect(
            UI_LOADING_X,
            UI_LOADING_Y,
            progressWidth,
            UI_LOADING_HEIGHT,
            UI_LOADING_COLOR
        );
    }
}


// ============================================================
// SEPARATEUR LOADING
// ============================================================

void displayDrawLoadingSeparator(TFT_eSPI &tft)
{
    tft.fillRect(
        UI_LOADING_SEPARATOR_X,
        UI_LOADING_SEPARATOR_Y,
        UI_LOADING_SEPARATOR_WIDTH,
        UI_LOADING_SEPARATOR_HEIGHT,
        UI_SEPARATOR_COLOR
    );
}


// ============================================================
// TITRE PAGE
// ============================================================
//
// Petit titre centre dans sa zone.
// ============================================================

void displayDrawPageTitle(
    TFT_eSPI &tft,
    const char *title
)
{
    // --------------------------------------------------------
    // Zone titre
    // --------------------------------------------------------

    tft.fillRect(
        UI_TITLE_X,
        UI_TITLE_Y,
        UI_TITLE_WIDTH,
        UI_TITLE_HEIGHT,
        UI_BACKGROUND_COLOR
    );


    // --------------------------------------------------------
    // Texte
    // --------------------------------------------------------

    tft.setTextColor(
        UI_TITLE_COLOR,
        UI_BACKGROUND_COLOR
    );

    tft.setTextDatum(MC_DATUM);

    // Petit titre
    tft.setTextSize(1);

    tft.drawString(
        title,
        UI_TITLE_X + (UI_TITLE_WIDTH / 2),
        UI_TITLE_Y + (UI_TITLE_HEIGHT / 2)
    );
}


// ============================================================
// SEPARATEUR TITRE
// ============================================================

void displayDrawTitleSeparator(TFT_eSPI &tft)
{
    tft.fillRect(
        UI_TITLE_SEPARATOR_X,
        UI_TITLE_SEPARATOR_Y,
        UI_TITLE_SEPARATOR_WIDTH,
        UI_TITLE_SEPARATOR_HEIGHT,
        UI_SEPARATOR_COLOR
    );
}


// ============================================================
// CADRE COMMUN
// ============================================================
//
// Structure commune a toutes les pages :
//
// HEADER
// SEPARATEUR
// LOADING
// SEPARATEUR
// TITRE
// SEPARATEUR
// CONTENU
//
// Aucun footer.
// ============================================================

void displayDrawFrame(
    TFT_eSPI &tft,
    const char *title,
    uint8_t loadingProgress
)
{
    // --------------------------------------------------------
    // Fond complet
    // --------------------------------------------------------

    tft.fillScreen(UI_BACKGROUND_COLOR);


    // --------------------------------------------------------
    // HEADER
    // --------------------------------------------------------

    displayDrawHeader(tft);


    // --------------------------------------------------------
    // SEPARATEUR HEADER
    // --------------------------------------------------------

    displayDrawHeaderSeparator(tft);


    // --------------------------------------------------------
    // BARRE LOADING
    // --------------------------------------------------------

    displayDrawLoadingBar(
        tft,
        loadingProgress
    );


    // --------------------------------------------------------
    // SEPARATEUR LOADING
    // --------------------------------------------------------

    displayDrawLoadingSeparator(tft);


    // --------------------------------------------------------
    // TITRE
    // --------------------------------------------------------

    displayDrawPageTitle(
        tft,
        title
    );


    // --------------------------------------------------------
    // SEPARATEUR TITRE
    // --------------------------------------------------------

    displayDrawTitleSeparator(tft);
}


// ============================================================
// COMPATIBILITE ANCIENNE API
// ============================================================
//
// Conserve cette fonction pour eviter de casser d'eventuels
// appels encore presents dans le projet.
// ============================================================

void displayDrawSystemBar(TFT_eSPI &tft)
{
    displayDrawLoadingBar(
        tft,
        100
    );
}