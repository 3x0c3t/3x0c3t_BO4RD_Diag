#include <Arduino.h>

#include "config.h"
#include "display.h"
#include "touch.h"
#include "sd_diag.h"

// ============================================================
// SETUP
// ============================================================

void setup()
{
    Serial.begin(115200);

    delay(500);

    Serial.println();
    Serial.println("================================");
    Serial.println("3x0c3t BO4RD DIAGNOSTIC");
    Serial.println("================================");

    Serial.println("[BOOT] setup() START");

    // --------------------------------------------------------
    // DISPLAY
    // --------------------------------------------------------

    Serial.println("[BOOT] displayInit()");

    displayInit();

    Serial.println("[BOOT] displayInit() END");

    // --------------------------------------------------------
    // TOUCH
    // --------------------------------------------------------

    Serial.println("[BOOT] touchInit()");

    touchInit();

    Serial.println("[BOOT] touchInit() END");

    // --------------------------------------------------------
    // SD
    // --------------------------------------------------------

    Serial.println("[BOOT] sdDiagInit()");

    sdDiagInit();

    Serial.println("[BOOT] sdDiagInit() END");

    // --------------------------------------------------------
    // DIAGNOSTIC SD
    // --------------------------------------------------------

    Serial.println("[BOOT] sdDiagRun()");

    bool result = sdDiagRun();

    Serial.print("[BOOT] SD RESULT = ");

    if (result)
    {
        Serial.println("OK");
    }
    else
    {
        Serial.println("ERREUR");
    }

    Serial.println("[BOOT] setup() END");
    Serial.println("================================");
}

// ============================================================
// LOOP
// ============================================================

void loop()
{
    static unsigned long lastLog = 0;
    static unsigned long lastTouch = 0;

    unsigned long now = millis();

    // --------------------------------------------------------
    // TOUCH
    // --------------------------------------------------------

    if (now - lastTouch >= 100)
    {
        lastTouch = now;

        int16_t screenX;
        int16_t screenY;
        uint16_t pressure;

        if (touchRead(
                screenX,
                screenY,
                pressure
            ))
        {
            Serial.println("[TOUCH] >>> PRESSION DETECTEE");
        }
    }

    // --------------------------------------------------------
    // LOG
    // --------------------------------------------------------

    if (now - lastLog >= 5000)
    {
        lastLog = now;

        Serial.println("[LOOP] diagnostic actif");
    }

    delay(10);
}