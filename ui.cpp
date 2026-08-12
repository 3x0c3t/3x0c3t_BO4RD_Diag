#include "ui.h"
#include "display.h"
#include "touch.h"

enum Page
{
    PAGE_MAIN,
    PAGE_TOUCH
};

static Page currentPage = PAGE_MAIN;

void uiInit()
{
    displayMainPage();
}

void uiUpdate()
{
    int16_t x;
    int16_t y;

    if (!touchRead(x, y))
        return;

    if (currentPage == PAGE_MAIN)
    {
        // Bouton 1 | Tactile
        if (x >= 20 && x <= 220 &&
            y >= 60 && y <= 100)
        {
            currentPage = PAGE_TOUCH;
            displayTouchPage();
            delay(200);
        }
    }
    else if (currentPage == PAGE_TOUCH)
    {
        // Bouton RETOUR
        if (x >= 20 && x <= 220 &&
            y >= 280 && y <= 310)
        {
            currentPage = PAGE_MAIN;
            displayMainPage();
            delay(200);
        }
    }
}
