#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "wifi_diag.h"

static uint8_t currentWifiMode = WIFI_MODE_OFF;

static WifiNetwork networks[WIFI_MAX_NETWORKS];

static uint8_t networkCount = 0;

void wifiSetMode(uint8_t mode)
{
    currentWifiMode = mode;

    Serial.print("[WIFI] Changement de mode : ");

    if (mode == WIFI_MODE_OFF)
    {
        Serial.println("OFF");

        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);

        return;
    }

    if (mode == WIFI_MODE_CLIENT)
    {
        Serial.println("CLIENT");

        WiFi.mode(WIFI_STA);

        return;
    }

    if (mode == WIFI_MODE_AP)
    {
        Serial.println("AP");

        WiFi.mode(WIFI_AP);

        return;
    }

    Serial.println("INCONNU");
}

uint8_t wifiGetMode()
{
    return currentWifiMode;
}

void wifiScan()
{
    Serial.println();
    Serial.println("[WIFI] ========================================");
    Serial.println("[WIFI] DEMARRAGE SCAN");
    Serial.println("[WIFI] ========================================");

    networkCount = 0;

    WiFi.mode(WIFI_STA);

    int count = WiFi.scanNetworks(false, true);

    if (count < 0)
    {
        Serial.println("[WIFI] ERREUR SCAN");

        WiFi.scanDelete();

        return;
    }

    Serial.print("[WIFI] Reseaux trouves : ");
    Serial.println(count);

    if (count > WIFI_MAX_NETWORKS)
    {
        count = WIFI_MAX_NETWORKS;
    }

    networkCount = count;

    for (int i = 0; i < count; i++)
    {
        networks[i].ssid = WiFi.SSID(i);
        networks[i].rssi = WiFi.RSSI(i);
        networks[i].encryption = WiFi.encryptionType(i);
        networks[i].hidden = networks[i].ssid.length() == 0;

        Serial.print("[WIFI] ");
        Serial.print(i);
        Serial.print(" | SSID=");
        Serial.print(networks[i].ssid);
        Serial.print(" | RSSI=");
        Serial.print(networks[i].rssi);
        Serial.print(" dBm | SEC=");

        if (networks[i].encryption == 0)
        {
            Serial.println("OPEN");
        }
        else
        {
            Serial.println("SEC");
        }
    }

    WiFi.scanDelete();

    Serial.println("[WIFI] Scan termine");
    Serial.println("[WIFI] ========================================");
}

uint8_t wifiGetNetworkCount()
{
    return networkCount;
}

const WifiNetwork &wifiGetNetwork(uint8_t index)
{
    static WifiNetwork emptyNetwork;

    if (index >= networkCount)
    {
        emptyNetwork.ssid = "";
        emptyNetwork.rssi = 0;
        emptyNetwork.encryption = 0;
        emptyNetwork.hidden = true;

        return emptyNetwork;
    }

    return networks[index];
}

bool wifiConnect(const char *ssid, const char *password)
{
    if (ssid == nullptr)
    {
        return false;
    }

    Serial.println();
    Serial.println("[WIFI] ========================================");
    Serial.println("[WIFI] CONNEXION");
    Serial.println("[WIFI] ========================================");

    Serial.print("[WIFI] SSID : ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);

    WiFi.disconnect();

    delay(100);

    if (password == nullptr)
    {
        password = "";
    }

    WiFi.begin(ssid, password);

    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - start > 15000)
        {
            Serial.println();
            Serial.println("[WIFI] Timeout connexion");

            wifiPrintStatus();

            return false;
        }

        delay(250);

        Serial.print(".");
    }

    Serial.println();
    Serial.println("[WIFI] Connexion OK");

    wifiPrintStatus();

    return true;
}

void wifiDisconnect()
{
    Serial.println("[WIFI] Deconnexion");

    WiFi.disconnect();

    currentWifiMode = WIFI_MODE_OFF;
}

bool wifiIsConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void wifiPrintStatus()
{
    Serial.println("[WIFI] STATUS");

    Serial.print("[WIFI] Mode : ");

    if (currentWifiMode == WIFI_MODE_OFF)
    {
        Serial.println("OFF");
    }
    else if (currentWifiMode == WIFI_MODE_CLIENT)
    {
        Serial.println("CLIENT");
    }
    else if (currentWifiMode == WIFI_MODE_AP)
    {
        Serial.println("AP");
    }
    else
    {
        Serial.println("UNKNOWN");
    }

    Serial.print("[WIFI] Etat : ");

    wl_status_t status = WiFi.status();

    switch (status)
    {
        case WL_CONNECTED:
            Serial.println("CONNECTED");
            break;

        case WL_NO_SSID_AVAIL:
            Serial.println("NO_SSID");
            break;

        case WL_CONNECT_FAILED:
            Serial.println("CONNECT_FAILED");
            break;

        case WL_CONNECTION_LOST:
            Serial.println("CONNECTION_LOST");
            break;

        case WL_DISCONNECTED:
            Serial.println("DISCONNECTED");
            break;

        default:
            Serial.println("UNKNOWN");
            break;
    }

    if (status == WL_CONNECTED)
    {
        Serial.print("[WIFI] SSID : ");
        Serial.println(WiFi.SSID());

        Serial.print("[WIFI] IP : ");
        Serial.println(WiFi.localIP());

        Serial.print("[WIFI] RSSI : ");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");
    }
}