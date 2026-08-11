#ifndef WIFI_DIAG_H
#define WIFI_DIAG_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

#define WIFI_MODE_OFF     0
#define WIFI_MODE_CLIENT  1
#define WIFI_MODE_AP      2

#define WIFI_MAX_NETWORKS 20

struct WifiNetwork
{
    String ssid;
    int32_t rssi;
    uint8_t encryption;
    bool hidden;
};

void wifiSetMode(uint8_t mode);

uint8_t wifiGetMode();

void wifiScan();

uint8_t wifiGetNetworkCount();

const WifiNetwork &wifiGetNetwork(uint8_t index);

bool wifiConnect(const char *ssid, const char *password);

void wifiDisconnect();

bool wifiIsConnected();

void wifiPrintStatus();

#endif