#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "config.h"
#include "touch.h"

// ============================================================
// BROCHES 3x0c3t BO4RD
// ============================================================

#ifndef BO4RD_TFT_CS
#define BO4RD_TFT_CS 15
#endif

#ifndef BO4RD_TOUCH_CS
#define BO4RD_TOUCH_CS 0
#endif

#ifndef BO4RD_TOUCH_IRQ
#define BO4RD_TOUCH_IRQ 5
#endif

// ============================================================
// COMMANDES XPT2046
// ============================================================

#define XPT2046_CMD_X   0xD0
#define XPT2046_CMD_Y   0x90
#define XPT2046_CMD_Z1  0xB0
#define XPT2046_CMD_Z2  0xC0

// ============================================================
// ETAT
// ============================================================

static bool touchInitialized = false;

// ============================================================
// LECTURE SPI BRUTE XPT2046
// ============================================================

static uint16_t xpt2046Read(uint8_t command)
{
    uint16_t value;

    // --------------------------------------------------------
    // Désélectionner complètement le TFT
    // --------------------------------------------------------

    digitalWrite(BO4RD_TFT_CS, HIGH);

    // --------------------------------------------------------
    // Sélectionner XPT2046
    // --------------------------------------------------------

    digitalWrite(BO4RD_TOUCH_CS, LOW);

    delayMicroseconds(2);

    // --------------------------------------------------------
    // Transaction SPI
    // XPT2046 : MSB first, mode 0
    // --------------------------------------------------------

    SPI.beginTransaction(
        SPISettings(
            2500000,
            MSBFIRST,
            SPI_MODE0
        )
    );

    SPI.transfer(command);

    uint8_t highByte = SPI.transfer(0x00);
    uint8_t lowByte  = SPI.transfer(0x00);

    SPI.endTransaction();

    // --------------------------------------------------------
    // Désélection XPT2046
    // --------------------------------------------------------

    digitalWrite(BO4RD_TOUCH_CS, HIGH);

    // --------------------------------------------------------
    // Conversion 12 bits
    // --------------------------------------------------------

    value =
        ((uint16_t)highByte << 8) |
        lowByte;

    value >>= 3;

    value &= 0x0FFF;

    return value;
}

// ============================================================
// INITIALISATION
// ============================================================

void touchInit(TFT_eSPI &tft)
{
    (void)tft;

    Serial.println("[TOUCH] Initialisation XPT2046");

    // --------------------------------------------------------
    // CS TFT
    // --------------------------------------------------------

    pinMode(
        BO4RD_TFT_CS,
        OUTPUT
    );

    digitalWrite(
        BO4RD_TFT_CS,
        HIGH
    );

    // --------------------------------------------------------
    // CS TOUCH
    // --------------------------------------------------------

    pinMode(
        BO4RD_TOUCH_CS,
        OUTPUT
    );

    digitalWrite(
        BO4RD_TOUCH_CS,
        HIGH
    );

    // --------------------------------------------------------
    // IRQ TOUCH
    // --------------------------------------------------------

    pinMode(
        BO4RD_TOUCH_IRQ,
        INPUT_PULLUP
    );

    // --------------------------------------------------------
    // SPI
    // --------------------------------------------------------

    SPI.begin();

    delay(20);

    touchInitialized = true;

    // --------------------------------------------------------
    // Diagnostic
    // --------------------------------------------------------

    Serial.println("[TOUCH] SPI initialise");

    Serial.print("[TOUCH] TFT CS = ");
    Serial.println(BO4RD_TFT_CS);

    Serial.print("[TOUCH] TOUCH CS = ");
    Serial.println(BO4RD_TOUCH_CS);

    Serial.print("[TOUCH] TOUCH IRQ = ");
    Serial.println(BO4RD_TOUCH_IRQ);

    Serial.print("[TOUCH] IRQ actuel = ");
    Serial.println(
        digitalRead(BO4RD_TOUCH_IRQ)
    );

    Serial.println("[TOUCH] XPT2046 pret");
}

// ============================================================
// DISPONIBILITE
// ============================================================

bool touchAvailable()
{
    if (!touchInitialized)
    {
        return false;
    }

    return (
        digitalRead(BO4RD_TOUCH_IRQ) == LOW
    );
}

// ============================================================
// LECTURE TOUCH
// ============================================================

bool touchRead(
    TFT_eSPI &tft,
    int16_t &x,
    int16_t &y,
    uint16_t &z
)
{
    (void)tft;

    if (!touchInitialized)
    {
        return false;
    }

    // --------------------------------------------------------
    // PAS DE CONTACT
    // --------------------------------------------------------

    if (
        digitalRead(BO4RD_TOUCH_IRQ) != LOW
    )
    {
        return false;
    }

    // --------------------------------------------------------
    // LECTURE RAW
    // --------------------------------------------------------

    uint16_t rawX =
        xpt2046Read(
            XPT2046_CMD_X
        );

    uint16_t rawY =
        xpt2046Read(
            XPT2046_CMD_Y
        );

    uint16_t rawZ1 =
        xpt2046Read(
            XPT2046_CMD_Z1
        );

    uint16_t rawZ2 =
        xpt2046Read(
            XPT2046_CMD_Z2
        );

    // --------------------------------------------------------
    // VALIDATION PRESSION
    // --------------------------------------------------------

    if (
        rawZ1 == 0 ||
        rawZ1 >= 4095
    )
    {
        return false;
    }

    if (
        rawZ2 == 0 ||
        rawZ2 >= 4095
    )
    {
        return false;
    }

    // --------------------------------------------------------
    // VALIDATION COORDONNEES
    // --------------------------------------------------------

    if (
        rawX == 0 ||
        rawY == 0
    )
    {
        return false;
    }

    if (
        rawX >= 4095 ||
        rawY >= 4095
    )
    {
        return false;
    }

    // --------------------------------------------------------
    // MAPPING
    // --------------------------------------------------------

    x = map(
        rawX,
        200,
        3900,
        0,
        239
    );

    y = map(
        rawY,
        200,
        3900,
        0,
        319
    );

    x = constrain(
        x,
        0,
        239
    );

    y = constrain(
        y,
        0,
        319
    );

    z = rawZ1;

    // --------------------------------------------------------
    // EVENEMENT VALIDE
    // --------------------------------------------------------

    Serial.print("[TOUCH] X=");
    Serial.print(x);

    Serial.print(" Y=");
    Serial.print(y);

    Serial.print(" Z=");
    Serial.println(z);

    return true;
}