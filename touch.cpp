#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "config.h"
#include "touch.h"

#ifndef BO4RD_TFT_CS
#define BO4RD_TFT_CS 15
#endif

#ifndef BO4RD_TOUCH_CS
#define BO4RD_TOUCH_CS 0
#endif

#ifndef BO4RD_TOUCH_IRQ
#define BO4RD_TOUCH_IRQ 5
#endif

#define XPT2046_CMD_X  0xD0
#define XPT2046_CMD_Y  0x90
#define XPT2046_CMD_Z1 0xB0
#define XPT2046_CMD_Z2 0xC0

static bool touchInitialized = false;

static uint16_t xptRead(uint8_t command)
{
    uint8_t b1;
    uint8_t b2;

    digitalWrite(BO4RD_TFT_CS, HIGH);
    digitalWrite(BO4RD_TOUCH_CS, LOW);

    delayMicroseconds(5);

    SPI.transfer(command);

    delayMicroseconds(5);

    b1 = SPI.transfer(0x00);
    b2 = SPI.transfer(0x00);

    delayMicroseconds(5);

    digitalWrite(BO4RD_TOUCH_CS, HIGH);

    uint16_t value =
        ((uint16_t)b1 << 8) |
        b2;

    value >>= 3;

    return value & 0x0FFF;
}

void touchInit(TFT_eSPI &tft)
{
    (void)tft;

    Serial.println("[TOUCH] Initialisation XPT2046");

    pinMode(BO4RD_TFT_CS, OUTPUT);
    digitalWrite(BO4RD_TFT_CS, HIGH);

    pinMode(BO4RD_TOUCH_CS, OUTPUT);
    digitalWrite(BO4RD_TOUCH_CS, HIGH);

    pinMode(BO4RD_TOUCH_IRQ, INPUT);

    SPI.begin();

    delay(10);

    touchInitialized = true;

    Serial.println("[TOUCH] SPI.begin() OK");

    Serial.print("[TOUCH] TFT CS = ");
    Serial.println(BO4RD_TFT_CS);

    Serial.print("[TOUCH] TOUCH CS = ");
    Serial.println(BO4RD_TOUCH_CS);

    Serial.print("[TOUCH] TOUCH IRQ = ");
    Serial.println(BO4RD_TOUCH_IRQ);

    Serial.print("[TOUCH] IRQ actuel = ");
    Serial.println(digitalRead(BO4RD_TOUCH_IRQ));

    Serial.println("[TOUCH] Test SPI XPT2046...");
}

bool touchAvailable()
{
    if (!touchInitialized)
    {
        return false;
    }

    return digitalRead(BO4RD_TOUCH_IRQ) == LOW;
}

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

    if (digitalRead(BO4RD_TOUCH_IRQ) == HIGH)
    {
        return false;
    }

    uint16_t rawX =
        xptRead(XPT2046_CMD_X);

    uint16_t rawY =
        xptRead(XPT2046_CMD_Y);

    uint16_t rawZ1 =
        xptRead(XPT2046_CMD_Z1);

    uint16_t rawZ2 =
        xptRead(XPT2046_CMD_Z2);

    Serial.print("[TOUCH] RAW X=");
    Serial.print(rawX);

    Serial.print(" Y=");
    Serial.print(rawY);

    Serial.print(" Z1=");
    Serial.print(rawZ1);

    Serial.print(" Z2=");
    Serial.println(rawZ2);

    if (
        rawX == 0 &&
        rawY == 0 &&
        rawZ1 == 0 &&
        rawZ2 == 0
    )
    {
        Serial.println("[TOUCH] Aucune donnee SPI");

        return false;
    }

    if (
        rawX >= 4095 ||
        rawY >= 4095
    )
    {
        Serial.println("[TOUCH] Donnee RAW invalide");

        return false;
    }

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

    x = constrain(x, 0, 239);
    y = constrain(y, 0, 319);

    z = rawZ1;

    Serial.print("[TOUCH] SCREEN X=");
    Serial.print(x);

    Serial.print(" Y=");
    Serial.print(y);

    Serial.print(" Z=");
    Serial.println(z);

    return true;
}