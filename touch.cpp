#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "touch.h"
#include "debug.h"

// ============================================================
// ETAT
// ============================================================

static bool touchInitialized = false;
static bool touchWasPressed = false;

// ============================================================
// INITIALISATION
// ============================================================

void touchInit(TFT_eSPI &tft)
{
    LOGLN_TOUCH("[TOUCH] Initialisation XPT2046");

    // --------------------------------------------------------
    // Désactivation du TFT
    // TFT CS = GPIO15 / D8
    // --------------------------------------------------------

    pinMode(15, OUTPUT);
    digitalWrite(15, HIGH);

    // --------------------------------------------------------
    // Initialisation SPI matériel ESP8266
    //
    // SCK  = GPIO14 / D5
    // MISO = GPIO12 / D6
    // MOSI = GPIO13 / D7
    // --------------------------------------------------------

    SPI.begin();

    LOGLN_TOUCH_DETAIL(
        "[TOUCH] SPI.begin() OK"
    );

    // --------------------------------------------------------
    // Etat initial
    // --------------------------------------------------------

    touchWasPressed = false;
    touchInitialized = true;

    LOGLN_TOUCH(
        "[TOUCH] XPT2046 initialise"
    );
}

// ============================================================
// DISPONIBILITE
// ============================================================

bool touchAvailable()
{
    return touchInitialized;
}

// ============================================================
// LECTURE TACTILE
//
// Un seul événement est généré par appui.
//
// TOUCH
//   ↓
// événement
//   ↓
// maintien du doigt = aucun nouvel événement
//   ↓
// RELEASE
//   ↓
// nouvel appui autorisé
// ============================================================

bool touchRead(
    TFT_eSPI &tft,
    int16_t &x,
    int16_t &y,
    uint16_t &pressure
)
{
    // --------------------------------------------------------
    // Vérification initialisation
    // --------------------------------------------------------

    if (!touchInitialized)
    {
        return false;
    }

    // --------------------------------------------------------
    // Lecture TFT_eSPI
    // --------------------------------------------------------

    uint16_t tx = 0;
    uint16_t ty = 0;

    bool pressed = tft.getTouch(
        &tx,
        &ty
    );

    // --------------------------------------------------------
    // RELEASE
    //
    // Le doigt n'est plus sur l'écran.
    // On réarme la détection.
    // --------------------------------------------------------

    if (!pressed)
    {
        touchWasPressed = false;

        return false;
    }

    // --------------------------------------------------------
    // APPUI MAINTENU
    //
    // Le doigt est toujours posé.
    // On ne génère PAS un nouvel événement.
    // --------------------------------------------------------

    if (touchWasPressed)
    {
        return false;
    }

    // --------------------------------------------------------
    // NOUVEL APPUI
    // --------------------------------------------------------

    touchWasPressed = true;

    // --------------------------------------------------------
    // Coordonnées
    // --------------------------------------------------------

    x = (int16_t)tx;
    y = (int16_t)ty;

    // TFT_eSPI::getTouch() ne fournit pas la pression.
    //
    // Pour l'instant :
    // 1 = contact détecté
    // 0 = aucun contact
    //
    pressure = 1;

    // --------------------------------------------------------
    // LOG IMPORTANT
    // Niveau 1+
    // --------------------------------------------------------

    LOG_TOUCH("[TOUCH] X=");
    LOG_TOUCH(x);

    LOG_TOUCH(" Y=");
    LOG_TOUCH(y);

    LOG_TOUCH(" Z=");
    LOGLN_TOUCH(pressure);

    // --------------------------------------------------------
    // LOG COMPLET
    // Niveau 2
    // --------------------------------------------------------

    LOG_TOUCH_DETAIL(
        "[TOUCH] Nouveau contact"
    );

    LOG_TOUCH_DETAIL(
        "[TOUCH] X = "
    );

    LOGLN_TOUCH_DETAIL(
        x
    );

    LOG_TOUCH_DETAIL(
        "[TOUCH] Y = "
    );

    LOGLN_TOUCH_DETAIL(
        y
    );

    LOG_TOUCH_DETAIL(
        "[TOUCH] Pression = "
    );

    LOGLN_TOUCH_DETAIL(
        pressure
    );

    // --------------------------------------------------------
    // Nouvel événement tactile
    // --------------------------------------------------------

    return true;
}