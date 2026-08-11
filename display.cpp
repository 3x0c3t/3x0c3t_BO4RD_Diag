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

void displayDrawHeader(TFT_eSPI &tft)
{
    // --------------------------------------------------------
    // Fond
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
    // Indicateurs
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
// SEPARATION HEADER
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

void displayDrawLoadingBar(
    TFT_eSPI &tft,
    uint8_t progress
)
{
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
// SEPARATION LOADING
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

void displayDrawPageTitle(
    TFT_eSPI &tft,
    const char *title
)
{
    // --------------------------------------------------------
    // Fond
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
    tft.setTextSize(1);

    tft.drawString(
        title,
        UI_TITLE_X + (UI_TITLE_WIDTH / 2),
        UI_TITLE_Y + (UI_TITLE_HEIGHT / 2)
    );
}


// ============================================================
// SEPARATION TITRE
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
// HEADER
//     ↓
// SEPARATION 1 px
//     ↓
// LOADING
//     ↓
// SEPARATION 1 px
//     ↓
// TITRE
//     ↓
// SEPARATION 1 px
//     ↓
// CONTENU
//
// ============================================================

void displayDrawFrame(
    TFT_eSPI &tft,
    const char *title,
    uint8_t loadingProgress
)
{
    // --------------------------------------------------------
    // Fond
    // --------------------------------------------------------

    tft.fillScreen(UI_BACKGROUND_COLOR);


    // --------------------------------------------------------
    // HEADER
    // --------------------------------------------------------

    displayDrawHeader(tft);


    // --------------------------------------------------------
    // SEPARATION HEADER
    // --------------------------------------------------------

    displayDrawHeaderSeparator(tft);


    // --------------------------------------------------------
    // LOADING
    // --------------------------------------------------------

    displayDrawLoadingBar(
        tft,
        loadingProgress
    );


    // --------------------------------------------------------
    // SEPARATION LOADING
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
    // SEPARATION TITRE
    // --------------------------------------------------------

    displayDrawTitleSeparator(tft);
}


// ============================================================
// COMPATIBILITE ANCIENNE API
// ============================================================

void displayDrawSystemBar(TFT_eSPI &tft)
{
    displayDrawLoadingBar(
        tft,
        100
    );
}