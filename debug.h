#ifndef DEBUG_H
#define DEBUG_H

// ============================================================
// 3x0c3t BO4RD DIAGNOSTIC
// GESTION CENTRALISEE DES LOGS
// ============================================================
//
// NIVEAUX
//
// 0 = aucun log
// 1 = logs importants
// 2 = logs complets
//
// ============================================================


// ============================================================
// CONFIGURATION
// ============================================================

#define DEBUG_BOOT      0
#define DEBUG_MAIN      1
#define DEBUG_TOUCH     2
#define DEBUG_WIFI      0
#define DEBUG_DISPLAY   0
#define DEBUG_SPLASH    0
#define DEBUG_SYSTEME   0


// ============================================================
// BOOT
// ============================================================

#if DEBUG_BOOT >= 1
    #define LOG_BOOT(x)       Serial.print(x)
    #define LOGLN_BOOT(x)     Serial.println(x)
#else
    #define LOG_BOOT(x)
    #define LOGLN_BOOT(x)
#endif

#if DEBUG_BOOT >= 2
    #define LOG_BOOT_DETAIL(x)       Serial.print(x)
    #define LOGLN_BOOT_DETAIL(x)     Serial.println(x)
#else
    #define LOG_BOOT_DETAIL(x)
    #define LOGLN_BOOT_DETAIL(x)
#endif


// ============================================================
// MAIN
// ============================================================

#if DEBUG_MAIN >= 1
    #define LOG_MAIN(x)       Serial.print(x)
    #define LOGLN_MAIN(x)     Serial.println(x)
#else
    #define LOG_MAIN(x)
    #define LOGLN_MAIN(x)
#endif

#if DEBUG_MAIN >= 2
    #define LOG_MAIN_DETAIL(x)       Serial.print(x)
    #define LOGLN_MAIN_DETAIL(x)     Serial.println(x)
#else
    #define LOG_MAIN_DETAIL(x)
    #define LOGLN_MAIN_DETAIL(x)
#endif


// ============================================================
// TOUCH
// ============================================================

#if DEBUG_TOUCH >= 1
    #define LOG_TOUCH(x)       Serial.print(x)
    #define LOGLN_TOUCH(x)     Serial.println(x)
#else
    #define LOG_TOUCH(x)
    #define LOGLN_TOUCH(x)
#endif

#if DEBUG_TOUCH >= 2
    #define LOG_TOUCH_DETAIL(x)       Serial.print(x)
    #define LOGLN_TOUCH_DETAIL(x)     Serial.println(x)
#else
    #define LOG_TOUCH_DETAIL(x)
    #define LOGLN_TOUCH_DETAIL(x)
#endif


// ============================================================
// WIFI
// ============================================================

#if DEBUG_WIFI >= 1
    #define LOG_WIFI(x)       Serial.print(x)
    #define LOGLN_WIFI(x)     Serial.println(x)
#else
    #define LOG_WIFI(x)
    #define LOGLN_WIFI(x)
#endif

#if DEBUG_WIFI >= 2
    #define LOG_WIFI_DETAIL(x)       Serial.print(x)
    #define LOGLN_WIFI_DETAIL(x)     Serial.println(x)
#else
    #define LOG_WIFI_DETAIL(x)
    #define LOGLN_WIFI_DETAIL(x)
#endif


// ============================================================
// DISPLAY
// ============================================================

#if DEBUG_DISPLAY >= 1
    #define LOG_DISPLAY(x)       Serial.print(x)
    #define LOGLN_DISPLAY(x)     Serial.println(x)
#else
    #define LOG_DISPLAY(x)
    #define LOGLN_DISPLAY(x)
#endif

#if DEBUG_DISPLAY >= 2
    #define LOG_DISPLAY_DETAIL(x)       Serial.print(x)
    #define LOGLN_DISPLAY_DETAIL(x)     Serial.println(x)
#else
    #define LOG_DISPLAY_DETAIL(x)
    #define LOGLN_DISPLAY_DETAIL(x)
#endif


// ============================================================
// SPLASH
// ============================================================

#if DEBUG_SPLASH >= 1
    #define LOG_SPLASH(x)       Serial.print(x)
    #define LOGLN_SPLASH(x)     Serial.println(x)
#else
    #define LOG_SPLASH(x)
    #define LOGLN_SPLASH(x)
#endif

#if DEBUG_SPLASH >= 2
    #define LOG_SPLASH_DETAIL(x)       Serial.print(x)
    #define LOGLN_SPLASH_DETAIL(x)     Serial.println(x)
#else
    #define LOG_SPLASH_DETAIL(x)
    #define LOGLN_SPLASH_DETAIL(x)
#endif


// ============================================================
// SYSTEME
// ============================================================

#if DEBUG_SYSTEME >= 1
    #define LOG_SYSTEME(x)       Serial.print(x)
    #define LOGLN_SYSTEME(x)     Serial.println(x)
#else
    #define LOG_SYSTEME(x)
    #define LOGLN_SYSTEME(x)
#endif

#if DEBUG_SYSTEME >= 2
    #define LOG_SYSTEME_DETAIL(x)       Serial.print(x)
    #define LOGLN_SYSTEME_DETAIL(x)     Serial.println(x)
#else
    #define LOG_SYSTEME_DETAIL(x)
    #define LOGLN_SYSTEME_DETAIL(x)
#endif

#endif