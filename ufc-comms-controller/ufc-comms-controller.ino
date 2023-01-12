/* 
 * @description main script for UFC COMMS controller board assumed to be an Arduino Leonardo
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * 
 * @notes Arduino Leonardo has an ATmega32u4
 *      default: '#define DCSBIOS_IRQ_SERIAL'
 *          use '#define DCSBIOS_DEFAULT_SERIAL' instead if your Arduino board
 *          does not feature an ATMega328 or ATMega2650 controller.
 *      arduino IDE programmer and board settings:
 *          board: Arduino Leonardo
 *          programmer: AVRISP mkII
 */

#define DCSBIOS_DEFAULT_SERIAL
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <DcsBios.h>


#include <SPI.h>
#include <Wire.h>

#include <Adafruit_GFX.h>
#include <Adafruit_GrayOLED.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <Adafruit_SSD1306.h>
#include <splash.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN0_ADDRESS 0x3C /// < See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define SCREEN1_ADDRESS 0x3C
#define MUX_I2C_ADDR 0x77
#define I2C_MUX_ADDR0 0
#define I2C_MUX_ADDR1 1
#define I2C_CLK_SPD 400000



/************************** begin global variables and constants ****************************/

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
uint8_t currentBus = 0;

/*************************** end global variables and constants *****************************/

/******************************* begin main program loop ************************************/
/**
 * @description main program loop
 */
void loop() {
    DcsBios::loop();
}
/******************************** end main program loop *************************************/

/********************************* begin init functions *************************************/

/**
 * @description initializes output pins, serial connections and peripherals
 */
void setup() {
    // setupSerial();
    // Serial.println("Initializing UFC COMMS controller");
    DcsBios::setup();
    setupI2CBus();
    setupDisplay0();
    setupDisplay1();
}

// void setupSerial() {
//   Serial.begin(9600);
//   // do { ; } while (!Serial);
//   delay(1000);
// }

/********************************** end init functions **************************************/

/**************************** begin DCS BIOS event handlers *********************************/

void onUfcComm1DisplayChange(char* newValue) {
  updateDisplay(newValue, I2C_MUX_ADDR0);
}
DcsBios::StringBuffer<2> ufcComm1DisplayBuffer(0x7424, onUfcComm1DisplayChange);

void onUfcComm2DisplayChange(char* newValue) {
  updateDisplay(newValue, I2C_MUX_ADDR1);
}
DcsBios::StringBuffer<2> ufcComm2DisplayBuffer(0x7426, onUfcComm2DisplayChange);

/***************************** end DCS BIOS event handlers **********************************/


/********************************* begin display utils *************************************/

void setupI2CBus() {
    Wire.setClock(I2C_CLK_SPD);
    connectI2CBus(I2C_MUX_ADDR0);
}

/**
 * @description connects to the given i2c bus address using the TCA9548A i2c bus multiplexer
 * @param bus the address of the i2c bus with a range from 0 to 7
 * 
 * TODO: why does this function take 25 ms to execute? -- possibly due to the length of the i2c
 *      bus cables that extend from the multiplexer to the devices. for i2c the capacitance of the
 *      transmission wires is a big factor. a possible solution is to lower the baud rate which
 *      might make the capacitance less of a factor. It might also be the pull-up resistor on the Vin
 *      being too high or too low?
 */
void connectI2CBus(uint8_t bus) {
    unsigned long startTime = millis();
    // Serial.print("connecting to I2C bus #");
    // Serial.print(bus);
    // Serial.print("\n");
    // Serial.print("begin transmission \n");
    Wire.beginTransmission(MUX_I2C_ADDR);
    // Serial.print("write bus addr: ");
    // Serial.print(1 << bus);
    Wire.write(1 << bus); // shift a '1' onto the position of the byte to select bus
    // Serial.print("\nend transmission \n");
    Wire.endTransmission();

    currentBus = bus;

    // Serial.print("time to connect to bus: ");
    // Serial.print(millis() - startTime);
    // Serial.print(" ms \n");
    // Serial.print("bus #");
    // Serial.print(bus);
    // Serial.print("\n");
}

/**
 * @description initializes the display on I2C bus #0
 */
void setupDisplay0() {
  delay(100);
  connectI2CBus(I2C_MUX_ADDR0);
  delay(10);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN0_ADDRESS)) {
    // Serial.println(F("SSD1306 1 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Serial.print("connected!\n");

  display.setRotation(3);

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();

  printText("XL");
}

/**
 * @description initializes the display on I2C bus #1
 */
void setupDisplay1() {  
  delay(100);
  connectI2CBus(I2C_MUX_ADDR1);
  delay(10);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN1_ADDRESS)) {
    // Serial.println(F("SSD1306 2 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  // Serial.print("connected!\n");

  display.setRotation(3);
  display.display();

  printText("XR");
}

void printText(String text) {
  display.clearDisplay();
  display.setCursor(0, 42);
  display.setTextSize(5);
  display.setTextColor(SSD1306_WHITE);
  display.print(text);
  display.display();
}

void updateDisplay(String text, int busAddr) {
  connectI2CBus(busAddr);
  printText(text);
}

/********************************** end display utils **************************************/
