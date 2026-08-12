#include <Arduino.h>
#include <SPI.h>

#include "config.h"
#include "display.h"
#include "touch.h"
#include "ui.h"

void setup()
{
    Serial.begin(115200);
    delay(500);

    Serial.println();
    Serial.println("==============================");
    Serial.println("  3x0c3t BO4RD DIAG v3");
    Serial.println("==============================");

    SPI.begin();

    Serial.println("[TFT] Initialisation...");
    displayInit();
    Serial.println("[TFT] OK");

    Serial.println("[TOUCH] Initialisation...");
    touchInit();
    Serial.println("[TOUCH] OK");

    uiInit();

    Serial.println("[SYSTEM] Pret...");
}

void loop()
{
    uiUpdate();
    delay(10);
}
