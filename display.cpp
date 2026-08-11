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
    tft.fillRect(
        UI_HEADER_X,
        UI_HEADER_Y,
        UI_HEADER_WIDTH,
        UI_HEADER_HEIGHT,
        UI_HEADER_COLOR
    );


    // --------------------------------------------------------
    // HEURE
    // --------------------------------------------------------
    //
    // Placeholder temporaire.
    // La vraie horloge sera ajoutee plus tard.
    //

    tft.setTextColor(
        TFT_WHITE,
        UI_HEADER_COLOR
    );

    tft.setTextDatum(TL_DATUM);
    tft.setTextSize(1);

    tft.drawString(
        "--:--",
        UI_TIME_X,
        UI_TIME_Y
    );


    // --------------------------------------------------------
    // DATE
    // --------------------------------------------------------
    //
    // Placeholder temporaire.
    //

    tft.drawString(
        "--/--/----",
        UI_DATE_X,
        UI_DATE_Y
    );


    // --------------------------------------------------------
    // INDICATEURS SYSTEME
    // --------------------------------------------------------
    //
    // Reserve pour les futurs indicateurs :
    //
    // WiFi
    // SD
    // Touch
    // Batterie
    //
    // Pour l'instant : petits carres de reservation.
    //

    int x = UI_STATUS_X;

    const int size = 8;
    const int gap  = 4;

    for (int i = 0; i < 4; i++)
    {
        tft.drawRect(
            x + (i * (size + gap)),
            UI_STATUS_Y,
            size,
            size,
            TFT_DARKGREY
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
// BARRE DE CHARGEMENT
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
    // Largeur progression
    // --------------------------------------------------------

    uint16_t progressWidth =
        (UI_LOADING_WIDTH * progress) / 100;


    // --------------------------------------------------------
    // Progression
    // --------------------------------------------------------

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
// TITRE PAGE
// ============================================================

void displayDrawPageTitle(
    TFT_eSPI &tft,
    const char *title
)
{
    tft.fillRect(
        UI_TITLE_X,
        UI_TITLE_Y,
        UI_TITLE_WIDTH,
        UI_TITLE_HEIGHT,
        UI_BACKGROUND_COLOR
    );


    tft.setTextColor(
        UI_TITLE_COLOR,
        UI_BACKGROUND_COLOR
    );

    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(2);


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
// FOOTER
// ============================================================

void displayDrawFooter(TFT_eSPI &tft)
{
    tft.fillRect(
        UI_FOOTER_X,
        UI_FOOTER_Y,
        UI_FOOTER_WIDTH,
        UI_FOOTER_HEIGHT,
        UI_FOOTER_COLOR
    );


    tft.setTextColor(
        TFT_DARKGREY,
        UI_FOOTER_COLOR
    );

    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(1);

    tft.drawString(
        "3x0c3t BO4RD",
        UI_FOOTER_X + (UI_FOOTER_WIDTH / 2),
        UI_FOOTER_Y + (UI_FOOTER_HEIGHT / 2)
    );
}


// ============================================================
// CADRE COMPLET
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
    // Header
    // --------------------------------------------------------

    displayDrawHeader(tft);


    // --------------------------------------------------------
    // Ligne Header
    // --------------------------------------------------------

    displayDrawHeaderSeparator(tft);


    // --------------------------------------------------------
    // Barre de chargement
    // --------------------------------------------------------

    displayDrawLoadingBar(
        tft,
        loadingProgress
    );


    // --------------------------------------------------------
    // Titre
    // --------------------------------------------------------

    displayDrawPageTitle(
        tft,
        title
    );


    // --------------------------------------------------------
    // Ligne titre
    // --------------------------------------------------------

    displayDrawTitleSeparator(tft);


    // --------------------------------------------------------
    // Footer
    // --------------------------------------------------------

    displayDrawFooter(tft);
}


// ============================================================
// COMPATIBILITE ANCIENNE API
// ============================================================

void displayDrawSystemBar(TFT_eSPI &tft)
{
    displayDrawLoadingBar(tft, 100);
}