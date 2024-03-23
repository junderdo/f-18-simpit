#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GC9A01A.h"
#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>

#include <TFT_eSPI.h>
#include <SPI.h>

// Define pins for display interface. You'll probably need to edit this for
// your own needs:

#define TFT_CS 10 // Chip select
#define TFT_DC 12 // Data/command
#define TFT_RST 9 // Reset
#define TFT_SDA 11 // Data
#define TFT_SCL 13 // Clock
// #define TFT_BL D6 // Backlight control

#define SCREEN_RADIUS 120
#define GUAGE_LINE_COUNT 22
#define SKIP_LINES 2
#define PI 3.1415927
#define HALF_PI PI / 2
#define DELTA_THETA 2 * PI / GUAGE_LINE_COUNT
#define LONG_LINE_LENGTH 30
#define SHORT_LINE_LENGTH 18
#define GUAGE_NEEDLE_LENGTH 90

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_SDA, TFT_SCL, TFT_RST);

void setup() {
  // Serial.begin(9600);
  tft.begin();

  tft.setRotation(2);
  tft.fillScreen(GC9A01A_BLACK);
  drawGuageBackground();
  DcsBios::setup();
}

void loop(void) {
  tft.setRotation(2);
  DcsBios::loop();

  for (int i; i < 65536; i+=100) {
    standbyAirspeedIndicator(i);
    delay(100);
  }
}

void onStbyAsiAirspeedChange(unsigned int newValue) {
    standbyAirspeedIndicator(newValue);
}
DcsBios::IntegerBuffer stbyAsiAirspeedBuffer(0x74e0, 0xffff, 0, onStbyAsiAirspeedChange);


unsigned long standbyAirspeedIndicator(unsigned int value) {
  unsigned long start = micros();

  drawGuageBackground();
  drawGuagePosition(value);

  // return screen render time
  return micros() - start;
}

void drawGuageBackground() {
  // draw text
  tft.setCursor(94, 140);
  // tft.setTextColor(GC9A01A_WHITE); 
  tft.setTextColor(TFT_WHITE); 
  tft.setTextSize(2);
  tft.println("KNOTS");
  tft.setCursor(94, 160);
  tft.println("x100");

  // draw background guage lines
  for (int i = 0; i < GUAGE_LINE_COUNT; i++) {

    // draw guage lines and numbers
    int lineLength = SHORT_LINE_LENGTH;
    if (i % 2 == 0) {
      lineLength = LONG_LINE_LENGTH;
    }
    float sinTheta = sin(HALF_PI - i * DELTA_THETA);
    float cosTheta = cos(HALF_PI - i * DELTA_THETA);
    int fx1 = SCREEN_RADIUS + SCREEN_RADIUS * sinTheta;
    int fy1 = SCREEN_RADIUS + SCREEN_RADIUS * cosTheta;
    int fx2 = SCREEN_RADIUS + (SCREEN_RADIUS - lineLength) * sinTheta;
    int fy2 = SCREEN_RADIUS + (SCREEN_RADIUS - lineLength) * cosTheta;
    if (i % 2 == 0) {
      tft.setTextColor(GC9A01A_WHITE);
      tft.setTextSize(2);
      int offsetX = 5;
      int offsetY = 0;
      if (i >= 10) {
        offsetX += 5;
        offsetY += 5;
      }
      int fxt = fx2 - offsetX - (16 * sinTheta);
      int fyt = fy2 - offsetY - (16 * cosTheta);
      tft.setCursor(fxt, fyt);
      tft.println(i / 2);
    }
    // tft.drawLine(fx1, fy1, fx2, fy2, GC9A01A_WHITE);
    tft.drawLine(fx1, fy1, fx2, fy2, TFT_WHITE);
  }
}

void drawGuagePosition(unsigned int value) {
  // 3rd order polynomial curve of best fit for data
  // https://docs.google.com/spreadsheets/d/1rkVR-3BWy7RBI-uuxGb-Q3Bv4VO65dlPMLXHH3KxFz4/edit#gid=0
  float airSpeed = 44.3 + 0.0086 * value - 0.000000346 * pow(value, 2) + 0.00000000000638 * pow(value, 3);
  float maxAirSpeed = GUAGE_LINE_COUNT / SKIP_LINES * 100;
  float ratio = airSpeed / maxAirSpeed;
  float theta = ratio * 2 * PI;
  // Serial.print("ratio = ");
  // Serial.print(ratio);
  // Serial.print(", theta = ");
  // Serial.print(theta);
  // Serial.print("\n");
  float sinTheta = sin(HALF_PI - theta);
  float cosTheta = cos(HALF_PI - theta);
  int fx1 = SCREEN_RADIUS + SCREEN_RADIUS * sinTheta;
  int fy1 = SCREEN_RADIUS + SCREEN_RADIUS * cosTheta;
  int fx2 = SCREEN_RADIUS + (SCREEN_RADIUS - GUAGE_NEEDLE_LENGTH) * sinTheta;
  int fy2 = SCREEN_RADIUS + (SCREEN_RADIUS - GUAGE_NEEDLE_LENGTH) * cosTheta;
  tft.drawLine(fx1, fy1, fx2, fy2, GC9A01A_WHITE);
}
