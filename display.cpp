#include "display.h"
#include "config.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

void displayInit()
{
    tft.begin();
    tft.setRotation(0);
    tft.fillScreen(ILI9341_BLACK);
}

static void drawButton(
    int16_t x,
    int16_t y,
    int16_t w,
    int16_t h,
    const char *text)
{
    tft.fillRoundRect(x, y, w, h, 6, ILI9341_DARKGREY);
    tft.drawRoundRect(x, y, w, h, 6, ILI9341_WHITE);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);

    int16_t tx = x + 10;
    int16_t ty = y + (h / 2) - 8;

    tft.setCursor(tx, ty);
    tft.print(text);
}

void displayMainPage()
{
    tft.fillScreen(ILI9341_BLACK);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(50, 15);
    tft.print("3x0c3t BO4RD");

    tft.setTextSize(1);
    tft.setCursor(75, 40);
    tft.print("DIAGNOSTIC v3");

    drawButton(20, 60, 200, 40, "1 | Tactile");
    drawButton(20, 110, 200, 40, "2 | Ecran");
    drawButton(20, 160, 200, 40, "3 | SD");
    drawButton(20, 210, 200, 40, "4 | WiFi");
    drawButton(20, 260, 200, 40, "5 | Reboot");
}

void displayTouchPage()
{
    tft.fillScreen(ILI9341_BLACK);

    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(2);
    tft.setCursor(50, 15);
    tft.print("TACTILE");

    tft.drawFastHLine(10, 45, 220, ILI9341_WHITE);

    tft.setTextSize(1);
    tft.setCursor(20, 65);
    tft.print("Test du XPT2046");

    tft.setCursor(20, 90);
    tft.print("Touchez l'ecran...");

    tft.drawRect(10, 115, 220, 150, ILI9341_BLUE);

    tft.fillRoundRect(20, 280, 200, 30, 5, ILI9341_DARKGREY);
    tft.drawRoundRect(20, 280, 200, 30, 5, ILI9341_WHITE);

    tft.setCursor(85, 290);
    tft.setTextColor(ILI9341_WHITE);
    tft.print("RETOUR");
}
