#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

// ============================================================
// DEBUG MAIN
// ============================================================

#define DEBUG_MAIN 1
#define DEBUG_MAIN_DETAIL 0

#if DEBUG_MAIN

#define LOG_MAIN(x)       Serial.print(x)
#define LOGLN_MAIN(x)     Serial.println(x)

#else

#define LOG_MAIN(x)
#define LOGLN_MAIN(x)

#endif

// ============================================================
// DEBUG MAIN DETAIL
// ============================================================

#if DEBUG_MAIN_DETAIL

#define LOG_MAIN_DETAIL(x)   Serial.print(x)
#define LOGLN_MAIN_DETAIL(x) Serial.println(x)

#else

#define LOG_MAIN_DETAIL(x)
#define LOGLN_MAIN_DETAIL(x)

#endif

// ============================================================
// DEBUG SYSTEME
// ============================================================

#define DEBUG_SYSTEME 1

#if DEBUG_SYSTEME

#define LOG_SYSTEME(x)       Serial.print(x)
#define LOGLN_SYSTEME(x)     Serial.println(x)

#else

#define LOG_SYSTEME(x)
#define LOGLN_SYSTEME(x)

#endif

// ============================================================
// DEBUG ECRAN WIFI
// ============================================================
// Ne PAS utiliser DEBUG_WIFI.
// Ce nom existe déjà dans ESP8266WiFi.h.
// ============================================================

#define DEBUG_WIFI_SCREEN 1

#if DEBUG_WIFI_SCREEN

#define LOG_WIFI(x)       Serial.print(x)
#define LOGLN_WIFI(x)     Serial.println(x)

#else

#define LOG_WIFI(x)
#define LOGLN_WIFI(x)

#endif

// ============================================================
// DEBUG TOUCH
// ============================================================

#define DEBUG_TOUCH 1

#if DEBUG_TOUCH

#define LOG_TOUCH(x)       Serial.print(x)
#define LOGLN_TOUCH(x)     Serial.println(x)

#else

#define LOG_TOUCH(x)
#define LOGLN_TOUCH(x)

#endif

#endif