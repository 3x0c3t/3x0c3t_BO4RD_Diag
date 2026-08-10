#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

#define TOUCH_MIN_Z 200

// ============================================================
// DIMENSIONS ECRAN - ROTATION 2
// ============================================================

#define SCREEN_WIDTH  240
#define SCREEN_HEIGHT 320

// ============================================================
// STRUCTURE TOUCH
// ============================================================

struct TouchPoint
{
  uint16_t x;
  uint16_t y;
  uint16_t z;
};

// ============================================================
// LECTURE TACTILE MOYENNE
// ============================================================

TouchPoint readTouch()
{
  TouchPoint p;

  uint32_t sumX = 0;
  uint32_t sumY = 0;
  uint32_t sumZ = 0;

  const int samples = 10;

  for (int i = 0; i < samples; i++)
  {
    uint16_t x;
    uint16_t y;

    tft.getTouchRaw(&x, &y);

    sumX += x;
    sumY += y;
    sumZ += tft.getTouchRawZ();

    delay(5);
  }

  p.x = sumX / samples;
  p.y = sumY / samples;
  p.z = sumZ / samples;

  return p;
}

// ============================================================
// AFFICHAGE CIBLE
// ============================================================

void drawTarget(int x, int y, const char *label)
{
  tft.fillCircle(x, y, 10, TFT_RED);

  tft.drawCircle(x, y, 15, TFT_WHITE);

  tft.drawLine(
    x - 20,
    y,
    x + 20,
    y,
    TFT_WHITE
  );

  tft.drawLine(
    x,
    y - 20,
    x,
    y + 20,
    TFT_WHITE
  );

  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);

  // Evite de sortir de l'écran
  int textX = x + 20;

  if (textX > SCREEN_WIDTH - 20)
  {
    textX = x - 30;
  }

  tft.setCursor(textX, y - 10);
  tft.print(label);
}

// ============================================================
// ATTENTE APPUI TACTILE
// ============================================================

bool waitForTouch(TouchPoint &p)
{
  while (true)
  {
    uint16_t x;
    uint16_t y;

    tft.getTouchRaw(&x, &y);

    uint16_t z = tft.getTouchRawZ();

    if (z > TOUCH_MIN_Z)
    {
      delay(50);

      p = readTouch();

      // Attendre que le doigt soit retiré
      while (tft.getTouchRawZ() > TOUCH_MIN_Z)
      {
        delay(20);
      }

      delay(200);

      return true;
    }

    delay(20);
  }
}

// ============================================================
// AFFICHAGE RESULTAT D'UN POINT
// ============================================================

void printPoint(const char *name, TouchPoint p)
{
  Serial.print(name);
  Serial.print(" : ");

  Serial.print("X = ");
  Serial.print(p.x);

  Serial.print(" | Y = ");
  Serial.print(p.y);

  Serial.print(" | Z = ");
  Serial.println(p.z);
}

// ============================================================
// SETUP
// ============================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  // ----------------------------------------------------------
  // TFT
  // ----------------------------------------------------------

  tft.init();

  // ROTATION 2 = PORTRAIT 240x320
  tft.setRotation(2);

  tft.fillScreen(TFT_BLACK);

  // ----------------------------------------------------------
  // MESSAGE SERIAL
  // ----------------------------------------------------------

  Serial.println();
  Serial.println("======================================");
  Serial.println(" XPT2046 CALIBRATION");
  Serial.println("======================================");
  Serial.println();

  Serial.println("ROTATION TFT = 2");
  Serial.println("RESOLUTION = 240 x 320");
  Serial.println();

  Serial.println("Touchez chaque cible.");
  Serial.println();

  // ==========================================================
  // CIBLE 1 - HAUT GAUCHE
  // ==========================================================

  tft.fillScreen(TFT_BLACK);

  drawTarget(20, 20, "1");

  Serial.println("--------------------------------------");
  Serial.println("CIBLE 1 - HAUT GAUCHE");
  Serial.println("Position ecran : X=20 Y=20");
  Serial.println("--------------------------------------");

  TouchPoint p1;

  waitForTouch(p1);

  printPoint("P1 RAW", p1);

  Serial.println();

  // ==========================================================
  // CIBLE 2 - HAUT DROIT
  // ==========================================================

  tft.fillScreen(TFT_BLACK);

  drawTarget(SCREEN_WIDTH - 20, 20, "2");

  Serial.println("--------------------------------------");
  Serial.println("CIBLE 2 - HAUT DROIT");
  Serial.print("Position ecran : X=");
  Serial.print(SCREEN_WIDTH - 20);
  Serial.println(" Y=20");
  Serial.println("--------------------------------------");

  TouchPoint p2;

  waitForTouch(p2);

  printPoint("P2 RAW", p2);

  Serial.println();

  // ==========================================================
  // CIBLE 3 - BAS GAUCHE
  // ==========================================================

  tft.fillScreen(TFT_BLACK);

  drawTarget(20, SCREEN_HEIGHT - 20, "3");

  Serial.println("--------------------------------------");
  Serial.println("CIBLE 3 - BAS GAUCHE");
  Serial.print("Position ecran : X=20 Y=");
  Serial.println(SCREEN_HEIGHT - 20);
  Serial.println("--------------------------------------");

  TouchPoint p3;

  waitForTouch(p3);

  printPoint("P3 RAW", p3);

  Serial.println();

  // ==========================================================
  // CIBLE 4 - BAS DROIT
  // ==========================================================

  tft.fillScreen(TFT_BLACK);

  drawTarget(
    SCREEN_WIDTH - 20,
    SCREEN_HEIGHT - 20,
    "4"
  );

  Serial.println("--------------------------------------");
  Serial.println("CIBLE 4 - BAS DROIT");

  Serial.print("Position ecran : X=");
  Serial.print(SCREEN_WIDTH - 20);

  Serial.print(" Y=");
  Serial.println(SCREEN_HEIGHT - 20);

  Serial.println("--------------------------------------");

  TouchPoint p4;

  waitForTouch(p4);

  printPoint("P4 RAW", p4);

  Serial.println();

  // ==========================================================
  // RESULTATS
  // ==========================================================

  Serial.println();
  Serial.println("======================================");
  Serial.println(" RESULTATS");
  Serial.println("======================================");

  Serial.println();

  Serial.print("P1 HAUT GAUCHE : ");
  Serial.print(p1.x);
  Serial.print(" / ");
  Serial.println(p1.y);

  Serial.print("P2 HAUT DROIT  : ");
  Serial.print(p2.x);
  Serial.print(" / ");
  Serial.println(p2.y);

  Serial.print("P3 BAS GAUCHE  : ");
  Serial.print(p3.x);
  Serial.print(" / ");
  Serial.println(p3.y);

  Serial.print("P4 BAS DROIT   : ");
  Serial.print(p4.x);
  Serial.print(" / ");
  Serial.println(p4.y);

  Serial.println();

  // ==========================================================
  // BORNES RAW
  // ==========================================================

  uint16_t minX = min(
    min(p1.x, p2.x),
    min(p3.x, p4.x)
  );

  uint16_t maxX = max(
    max(p1.x, p2.x),
    max(p3.x, p4.x)
  );

  uint16_t minY = min(
    min(p1.y, p2.y),
    min(p3.y, p4.y)
  );

  uint16_t maxY = max(
    max(p1.y, p2.y),
    max(p3.y, p4.y)
  );

  Serial.println("BORNES RAW :");

  Serial.print("MIN X = ");
  Serial.println(minX);

  Serial.print("MAX X = ");
  Serial.println(maxX);

  Serial.print("MIN Y = ");
  Serial.println(minY);

  Serial.print("MAX Y = ");
  Serial.println(maxY);

  Serial.println();

  // ==========================================================
  // ANALYSE ORIENTATION
  // ==========================================================

  Serial.println("======================================");
  Serial.println(" ANALYSE ORIENTATION");
  Serial.println("======================================");

  Serial.println();

  Serial.println("Correspondance attendue :");

  Serial.println();
  Serial.println("ECRAN             RAW");

  Serial.print("HAUT GAUCHE  -> ");
  Serial.print(p1.x);
  Serial.print(" / ");
  Serial.println(p1.y);

  Serial.print("HAUT DROIT   -> ");
  Serial.print(p2.x);
  Serial.print(" / ");
  Serial.println(p2.y);

  Serial.print("BAS GAUCHE   -> ");
  Serial.print(p3.x);
  Serial.print(" / ");
  Serial.println(p3.y);

  Serial.print("BAS DROIT    -> ");
  Serial.print(p4.x);
  Serial.print(" / ");
  Serial.println(p4.y);

  Serial.println();

  // ==========================================================
  // CODE DE CALIBRATION PROPOSE
  // ==========================================================

  Serial.println("======================================");
  Serial.println(" CODE CALIBRATION");
  Serial.println("======================================");

  Serial.println();

  Serial.println("// Calibration XPT2046");

  Serial.print("#define TOUCH_RAW_X_MIN ");
  Serial.println(minX);

  Serial.print("#define TOUCH_RAW_X_MAX ");
  Serial.println(maxX);

  Serial.print("#define TOUCH_RAW_Y_MIN ");
  Serial.println(minY);

  Serial.print("#define TOUCH_RAW_Y_MAX ");
  Serial.println(maxY);

  Serial.println();

  // ==========================================================
  // FIN
  // ==========================================================

  Serial.println("======================================");
  Serial.println(" CALIBRATION TERMINEE");
  Serial.println("======================================");

  // ----------------------------------------------------------
  // Ecran
  // ----------------------------------------------------------

  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(2);

  tft.setCursor(10, 20);
  tft.println("CALIBRATION OK");

  tft.setCursor(10, 60);
  tft.print("X: ");
  tft.print(minX);
  tft.print(" -> ");
  tft.println(maxX);

  tft.setCursor(10, 100);
  tft.print("Y: ");
  tft.print(minY);
  tft.print(" -> ");
  tft.println(maxY);

  tft.setCursor(10, 140);
  tft.println("ROTATION: 2");

  delay(5000);
}

// ============================================================
// LOOP
// ============================================================

void loop()
{
}