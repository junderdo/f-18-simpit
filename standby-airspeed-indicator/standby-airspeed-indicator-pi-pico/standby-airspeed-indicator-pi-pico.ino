#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library

// Put this in User_Setup.h
// #define RPI_DISPLAY_TYPE // 20MHz maximum SPI
// #define GC9A01_DRIVER
// #define TFT_WIDTH 240 // ST7789 240 x 240 and 240 x 320
// #define TFT_HEIGHT 240 // ST7789 240 x 240
// #define TFT_MISO -1
// #define TFT_MOSI 11 // In some display driver board, it might be written as "SDA" and so on.
// #define TFT_SCLK 10
// #define TFT_CS 9 //22 // Chip select control pin
// #define TFT_DC 8 //5 // Data Command control pin
// #define TFT_RST 12 // Reset pin (could connect to Arduino RESET pin)
// #define TFT_BL 25 // LED back-light
// #define LOAD_GLCD // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
// #define LOAD_FONT2 // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
// #define LOAD_FONT4 // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
// #define LOAD_FONT6 // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
// #define SMOOTH_FONT
// #define TFT_SPI_PORT 1 // Set to 0 if SPI0 pins are used, or 1 if spi1 pins used
// #define SPI_FREQUENCY 20000000
// #define TFT_BACKLIGHT_ON HIGH

TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

#define DEG2RAD 0.0174532925

byte inc = 0;
unsigned int col = 0;


void setup(void)
{
  tft.begin();

  tft.setRotation(1);

  tft.fillScreen(TFT_BLACK);
}

void loop() {

  // Draw 4 pie chart segments
  fillSegment(160, 120, 0, 60, 100, TFT_RED);
  fillSegment(160, 120, 60, 30, 100, TFT_GREEN);
  fillSegment(160, 120, 60 + 30, 120, 100, TFT_BLUE);
  fillSegment(160, 120, 60 + 30 + 120, 150, 100, TFT_YELLOW);

  delay(4000);

  // Erase old chart with 360 degree black plot
  fillSegment(160, 120, 0, 360, 100, TFT_BLACK);
}


// #########################################################################
// Draw circle segments
// #########################################################################

// x,y == coords of centre of circle
// start_angle = 0 - 359
// sub_angle   = 0 - 360 = subtended angle
// r = radius
// colour = 16 bit colour value

void fillSegment(int x, int y, int start_angle, int sub_angle, int r, unsigned int colour)
{
  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x1 = sx * r + x;
  uint16_t y1 = sy * r + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + sub_angle; i++) {

    // Calculate pair of coordinates for segment end
    int x2 = cos((i + 1 - 90) * DEG2RAD) * r + x;
    int y2 = sin((i + 1 - 90) * DEG2RAD) * r + y;

    tft.fillTriangle(x1, y1, x2, y2, x, y, colour);

    // Copy segment end to sgement start for next segment
    x1 = x2;
    y1 = y2;
  }
}


// #########################################################################
// Return the 16 bit colour with brightness 0-100%
// #########################################################################
unsigned int brightness(unsigned int colour, int brightness)
{
  byte red   = colour >> 11;
  byte green = (colour & 0x7E0) >> 5;
  byte blue  = colour & 0x1F;

  blue =  (blue * brightness)/100;
  green = (green * brightness)/100;
  red =   (red * brightness)/100;

  return (red << 11) + (green << 5) + blue;
}
