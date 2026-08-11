#include <Arduino.h>
#include <TFT_eSPI.h>
#include <ESP8266WiFi.h>

#include "config.h"
#include "display_config.h"
#include "display.h"
#include "touch.h"
#include "wifi_diag.h"
#include "screen_wifi.h"

// ============================================================
// PARAMETRES ECRAN WIFI
// ============================================================

#define WIFI_MAX_DISPLAY 8
#define WIFI_ROW_H 25

#define WIFI_TITLE_Y 48
#define WIFI_MODE_Y 76
#define WIFI_LIST_Y 112

// ============================================================
// ETAT ECRAN
// ============================================================

static uint8_t wifiDisplayMode = WIFI_MODE_OFF;
static int selectedNetwork = -1;
static bool wifiScanRequested = false;

// ============================================================
// RESEAU AFFICHABLE
// ============================================================

struct WifiScreenNetwork
{
String ssid;
int32_t rssi;
uint8_t encryption;
};

static WifiScreenNetwork screenNetworks[WIFI_MAX_DISPLAY];
static uint8_t screenNetworkCount = 0;

// ============================================================
// COULEURS
// ============================================================

static uint16_t wifiModeColor(uint8_t mode)
{
if (mode == WIFI_MODE_CLIENT)
return TFT_GREEN;

if (mode == WIFI_MODE_AP)
    return TFT_ORANGE;

return TFT_RED;

}

// ============================================================
// NOM SECURITE
// ============================================================

static const char *getSecurityName(uint8_t encryption)
{
switch (encryption)
{
case 0:
return "OUVERT";

    case 1:
        return "WEP";

    case 2:
        return "WPA";

    case 3:
        return "WPA2";

    case 4:
        return "WPA/WPA2";

    case 5:
        return "WPA2";

    case 6:
        return "WPA3";

    default:
        return "SEC";
}

}

// ============================================================
// SIGNAL
// ============================================================

static void drawSignal(
TFT_eSPI &tft,
int16_t x,
int16_t y,
int32_t rssi
)
{
uint8_t level = 0;

if (rssi >= -50)
    level = 4;
else if (rssi >= -60)
    level = 3;
else if (rssi >= -70)
    level = 2;
else if (rssi >= -80)
    level = 1;

for (uint8_t i = 0; i < 4; i++)
{
    int16_t h = 4 + i * 4;

    if (i < level)
    {
        tft.fillRect(
            x + i * 5,
            y + 12 - h,
            3,
            h,
            TFT_GREEN
        );
    }
    else
    {
        tft.drawRect(
            x + i * 5,
            y + 12 - h,
            3,
            h,
            TFT_DARKGREY
        );
    }
}

}

// ============================================================
// DESSIN RESEAU
// ============================================================

static void drawNetwork(
TFT_eSPI &tft,
uint8_t index
)
{
if (index >= screenNetworkCount)
return;

int16_t y =
    WIFI_LIST_Y +
    index * WIFI_ROW_H;

const WifiScreenNetwork &network =
    screenNetworks[index];

if (selectedNetwork == index)
{
    tft.fillRect(
        0,
        y,
        TFT_WIDTH,
        WIFI_ROW_H - 1,
        TFT_DARKCYAN
    );
}

tft.setTextColor(
    TFT_WHITE,
    selectedNetwork == index
        ? TFT_DARKCYAN
        : TFT_BLACK
);

tft.setTextSize(1);

String name = network.ssid;

if (name.length() > 20)
    name = name.substring(0, 20);

tft.setCursor(
    5,
    y + 3
);

tft.print(name);

tft.setCursor(
    5,
    y + 14
);

tft.print(
    getSecurityName(
        network.encryption
    )
);

tft.setCursor(
    65,
    y + 14
);

tft.print(
    network.rssi
);

tft.print(
    " dBm"
);

drawSignal(
    tft,
    205,
    y + 7,
    network.rssi
);

}

// ============================================================
// RECUPERATION DES RESEAUX
// ============================================================

static void wifiScreenScan()
{
Serial.println();
Serial.println(
"[WIFI_SCREEN] ========================================"
);
Serial.println(
"[WIFI_SCREEN] DEMARRAGE SCAN"
);
Serial.println(
"[WIFI_SCREEN] ========================================"
);

selectedNetwork = -1;
screenNetworkCount = 0;

WiFi.mode(WIFI_STA);

int count =
    WiFi.scanNetworks(
        false,
        true
    );

if (count < 0)
{
    Serial.println(
        "[WIFI_SCREEN] ERREUR SCAN"
    );

    WiFi.scanDelete();

    return;
}

Serial.print(
    "[WIFI_SCREEN] Reseaux trouves : "
);

Serial.println(count);

uint8_t maxNetworks =
    count > WIFI_MAX_DISPLAY
        ? WIFI_MAX_DISPLAY
        : count;

for (uint8_t i = 0; i < maxNetworks; i++)
{
    screenNetworks[i].ssid =
        WiFi.SSID(i);

    screenNetworks[i].rssi =
        WiFi.RSSI(i);

    screenNetworks[i].encryption =
        WiFi.encryptionType(i);

    Serial.print(
        "[WIFI_SCREEN] "
    );

    Serial.print(i);

    Serial.print(
        " | SSID="
    );

    Serial.print(
        screenNetworks[i].ssid
    );

    Serial.print(
        " | RSSI="
    );

    Serial.print(
        screenNetworks[i].rssi
    );

    Serial.print(
        " dBm | SEC="
    );

    Serial.println(
        getSecurityName(
            screenNetworks[i].encryption
        )
    );

    screenNetworkCount++;
}

WiFi.scanDelete();

Serial.println(
    "[WIFI_SCREEN] Scan termine"
);

Serial.println(
    "[WIFI_SCREEN] ========================================"
);

}

// ============================================================
// MODE WIFI
// ============================================================

static void drawWifiMode(
TFT_eSPI &tft
)
{
tft.setTextSize(1);

tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
);

tft.setCursor(
    5,
    WIFI_MODE_Y
);

tft.print(
    "MODE : "
);

uint16_t color =
    wifiModeColor(
        wifiDisplayMode
    );

tft.setTextColor(
    color,
    TFT_BLACK
);

if (wifiDisplayMode == WIFI_MODE_CLIENT)
{
    tft.print(
        "CLIENT"
    );
}
else if (wifiDisplayMode == WIFI_MODE_AP)
{
    tft.print(
        "POINT D'ACCES"
    );
}
else
{
    tft.print(
        "OFF"
    );
}

}

// ============================================================
// BOUTONS MODE
// ============================================================

static void drawModeButtons(
TFT_eSPI &tft
)
{
int16_t y = 88;

int16_t w =
    TFT_WIDTH / 3;

tft.drawRect(
    0,
    y,
    w,
    20,
    wifiDisplayMode == WIFI_MODE_CLIENT
        ? TFT_GREEN
        : TFT_DARKGREY
);

tft.drawRect(
    w,
    y,
    w,
    20,
    wifiDisplayMode == WIFI_MODE_AP
        ? TFT_ORANGE
        : TFT_DARKGREY
);

tft.drawRect(
    w * 2,
    y,
    TFT_WIDTH - w * 2,
    20,
    wifiDisplayMode == WIFI_MODE_OFF
        ? TFT_RED
        : TFT_DARKGREY
);

tft.setTextSize(1);

tft.setTextColor(
    TFT_WHITE,
    TFT_BLACK
);

tft.setCursor(
    10,
    y + 6
);

tft.print(
    "CLIENT"
);

tft.setCursor(
    w + 8,
    y + 6
);

tft.print(
    "AP"
);

tft.setCursor(
    w * 2 + 12,
    y + 6
);

tft.print(
    "OFF"
);

}

// ============================================================
// ECRAN
// ============================================================

void wifiScreenShow(
TFT_eSPI &tft
)
{
Serial.println(
"[WIFI_SCREEN] Affichage ecran Wi-Fi"
);

tft.fillScreen(
    TFT_BLACK
);

displayDrawSystemBar(
    tft
);

tft.setTextSize(2);

tft.setTextColor(
    TFT_CYAN,
    TFT_BLACK
);

tft.setCursor(
    5,
    WIFI_TITLE_Y
);

tft.print(
    "WI-FI"
);

tft.drawFastHLine(
    0,
    70,
    TFT_WIDTH,
    TFT_DARKGREY
);

drawWifiMode(
    tft
);

drawModeButtons(
    tft
);

tft.drawFastHLine(
    0,
    110,
    TFT_WIDTH,
    TFT_DARKGREY
);

if (wifiDisplayMode == WIFI_MODE_OFF)
{
    tft.setTextSize(1);

    tft.setTextColor(
        TFT_LIGHTGREY,
        TFT_BLACK
    );

    tft.setCursor(
        5,
        125
    );

    tft.print(
        "Wi-Fi desactive"
    );

    return;
}

if (wifiDisplayMode == WIFI_MODE_CLIENT)
{
    tft.setTextColor(
        TFT_CYAN,
        TFT_BLACK
    );

    tft.setCursor(
        5,
        115
    );

    tft.print(
        "RESEAUX DISPONIBLES"
    );

    for (
        uint8_t i = 0;
        i < screenNetworkCount;
        i++
    )
    {
        drawNetwork(
            tft,
            i
        );
    }

    return;
}

if (wifiDisplayMode == WIFI_MODE_AP)
{
    tft.setTextColor(
        TFT_ORANGE,
        TFT_BLACK
    );

    tft.setTextSize(1);

    tft.setCursor(
        5,
        120
    );

    tft.print(
        "POINT D'ACCES"
    );

    tft.setTextColor(
        TFT_WHITE,
        TFT_BLACK
    );

    tft.setCursor(
        5,
        145
    );

    tft.print(
        "SSID :"
    );

    tft.setCursor(
        5,
        170
    );

    tft.print(
        "MOT DE PASSE :"
    );

    tft.drawRect(
        5,
        130,
        230,
        20,
        TFT_DARKGREY
    );

    tft.drawRect(
        5,
        155,
        230,
        20,
        TFT_DARKGREY
    );

    tft.setCursor(
        10,
        136
    );

    tft.print(
        "3x0c3t_BO4RD"
    );

    tft.setCursor(
        10,
        161
    );

    tft.print(
        "********"
    );
}

}

// ============================================================
// TOUCH ECRAN WIFI
// ============================================================

bool wifiScreenTouch(
int16_t x,
int16_t y,
uint8_t &newScreen
)
{
Serial.print(
"[WIFI_SCREEN] Touch X="
);

Serial.print(x);

Serial.print(
    " Y="
);

Serial.println(y);

newScreen = 2;

if (y >= 88 && y <= 108)
{
    if (x < TFT_WIDTH / 3)
    {
        Serial.println(
            "[WIFI_SCREEN] Mode CLIENT"
        );

        wifiDisplayMode =
            WIFI_MODE_CLIENT;

        wifiSetMode(
            WIFI_MODE_CLIENT
        );

        wifiScreenScan();

        return true;
    }

    if (x < (TFT_WIDTH / 3) * 2)
    {
        Serial.println(
            "[WIFI_SCREEN] Mode POINT D'ACCES"
        );

        wifiDisplayMode =
            WIFI_MODE_AP;

        wifiSetMode(
            WIFI_MODE_AP
        );

        return true;
    }

    Serial.println(
        "[WIFI_SCREEN] Mode OFF"
    );

    wifiDisplayMode =
        WIFI_MODE_OFF;

    wifiSetMode(
        WIFI_MODE_OFF
    );

    return true;
}

if (
    wifiDisplayMode == WIFI_MODE_CLIENT &&
    y >= WIFI_LIST_Y &&
    y < WIFI_LIST_Y +
        screenNetworkCount * WIFI_ROW_H
)
{
    uint8_t index =
        (y - WIFI_LIST_Y) /
        WIFI_ROW_H;

    if (
        index < screenNetworkCount
    )
    {
        selectedNetwork =
            index;

        Serial.print(
            "[WIFI_SCREEN] Reseau selectionne : "
        );

        Serial.println(
            screenNetworks[index].ssid
        );

        return true;
    }
}

if (
    x < 45 &&
    y < 45
)
{
    Serial.println(
        "[WIFI_SCREEN] Retour MAIN"
    );

    newScreen = 0;

    return true;
}

return false;

}

// ============================================================
// LOOP ECRAN WIFI
// ============================================================

void wifiScreenLoop(
TFT_eSPI &tft
)
{
if (wifiScanRequested)
{
wifiScanRequested =
false;

    wifiScreenScan();

    wifiScreenShow(
        tft
    );
}

}
