#include "sd_diag.h"

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// ============================================================
// SD
// ============================================================

#define SD_CS 4

// ============================================================
// ETAT
// ============================================================

static bool sdReady = false;

// ============================================================
// INITIALISATION
// ============================================================

void sdDiagInit()
{
    Serial.println();
    Serial.println("================================");
    Serial.println("[SD] sdDiagInit() START");
    Serial.println("================================");

    Serial.print("[SD] CS = GPIO ");
    Serial.println(SD_CS);

    Serial.println("[SD] SPI.begin()");

    SPI.begin();

    Serial.println("[SD] SPI OK");

    Serial.println("[SD] SD.begin()");

    if (SD.begin(SD_CS))
    {
        sdReady = true;

        Serial.println("[SD] CARTE SD DETECTEE");
        Serial.println("[SD] SD READY");
    }
    else
    {
        sdReady = false;

        Serial.println("[SD] ERREUR CARTE SD");
        Serial.println("[SD] SD NOT READY");
    }

    Serial.println("[SD] sdDiagInit() END");
    Serial.println("================================");
}

// ============================================================
// DIAGNOSTIC
// ============================================================

bool sdDiagRun()
{
    Serial.println();
    Serial.println("================================");
    Serial.println("[SD] DIAGNOSTIC");
    Serial.println("================================");

    if (!sdReady)
    {
        Serial.println("[SD] ABANDON");
        Serial.println("[SD] Carte non initialisee");

        return false;
    }

    // --------------------------------------------------------
    // RACINE
    // --------------------------------------------------------

    Serial.println("[SD] TEST 1 -> ouverture racine");

    File root = SD.open("/");

    if (!root)
    {
        Serial.println("[SD] ERREUR ouverture racine");

        return false;
    }

    Serial.println("[SD] Racine ouverte");

    int count = 0;

    File file = root.openNextFile();

    while (file)
    {
        Serial.print("[SD] ");

        if (file.isDirectory())
        {
            Serial.print("[DIR] ");
        }
        else
        {
            Serial.print("[FILE] ");
        }

        Serial.print(file.name());

        if (!file.isDirectory())
        {
            Serial.print(" | ");
            Serial.print(file.size());
            Serial.print(" octets");
        }

        Serial.println();

        file.close();

        count++;

        file = root.openNextFile();
    }

    root.close();

    Serial.print("[SD] Nombre elements = ");
    Serial.println(count);

    Serial.println("[SD] TEST 1 OK");

    // --------------------------------------------------------
    // FICHIER TEST
    // --------------------------------------------------------

    const char *testFile = "/SD_DIAG.TXT";

    Serial.println("[SD] TEST 2 -> creation fichier");

    if (SD.exists(testFile))
    {
        Serial.println("[SD] Ancien fichier trouve");
        Serial.println("[SD] Suppression");

        if (!SD.remove(testFile))
        {
            Serial.println("[SD] ERREUR suppression");

            return false;
        }
    }

    File writeFile = SD.open(testFile, FILE_WRITE);

    if (!writeFile)
    {
        Serial.println("[SD] ERREUR ouverture ecriture");

        return false;
    }

    Serial.println("[SD] Fichier ouvert");

    writeFile.println("3x0c3t BO4RD DIAGNOSTIC");
    writeFile.println("SD WRITE TEST OK");

    writeFile.close();

    Serial.println("[SD] Ecriture OK");

    Serial.println("[SD] TEST 2 OK");

    // --------------------------------------------------------
    // VERIFICATION
    // --------------------------------------------------------

    Serial.println("[SD] TEST 3 -> verification");

    if (!SD.exists(testFile))
    {
        Serial.println("[SD] ERREUR fichier absent");

        return false;
    }

    Serial.println("[SD] Fichier present");

    Serial.println("[SD] TEST 3 OK");

    // --------------------------------------------------------
    // LECTURE
    // --------------------------------------------------------

    Serial.println("[SD] TEST 4 -> lecture");

    File readFile = SD.open(testFile, FILE_READ);

    if (!readFile)
    {
        Serial.println("[SD] ERREUR ouverture lecture");

        return false;
    }

    Serial.println("[SD] Contenu :");

    while (readFile.available())
    {
        Serial.write(readFile.read());
    }

    Serial.println();

    readFile.close();

    Serial.println("[SD] Lecture OK");

    Serial.println("[SD] TEST 4 OK");

    // --------------------------------------------------------
    // SUPPRESSION
    // --------------------------------------------------------

    Serial.println("[SD] TEST 5 -> suppression");

    if (!SD.remove(testFile))
    {
        Serial.println("[SD] ERREUR suppression");

        return false;
    }

    Serial.println("[SD] Fichier supprime");

    Serial.println("[SD] TEST 5 OK");

    // --------------------------------------------------------
    // RESULTAT
    // --------------------------------------------------------

    Serial.println();
    Serial.println("================================");
    Serial.println("[SD] DIAGNOSTIC TERMINE");
    Serial.println("[SD] RESULTAT = OK");
    Serial.println("================================");

    return true;
}