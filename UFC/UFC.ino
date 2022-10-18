/* 
 * @description main script for UFC controller board assumed to be an Arduino Uno R3
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * 
 * @notes Arduino Uno has an ATMega328P -- Arduino Leo does not like the OLED screen
 * default: '#define DCSBIOS_IRQ_SERIAL'
 *      use '#define DCSBIOS_DEFAULT_SERIAL' instead if your Arduino board
 *      does not feature an ATMega328 or ATMega2650 controller.
 * 
 */
#define DCSBIOS_IRQ_SERIAL
#include <DcsBios.h>
#include <TimerEvent.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_Alphanumeric_Display.h> //Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_Alphanumeric_Display by SparkFun
#include "ssd1305.h"

// oled display constants
#define WIDTH     128
#define HEIGHT     32
#define PAGES       4
// oled display pin assigments
#define OLED_RST    9 
#define OLED_DC     8
#define OLED_CS    10
#define SPI_MOSI   11    /* connect to the DIN pin of OLED */
#define SPI_SCK    13     /* connect to the CLK pin of OLED */

// 14 segment led displays
HT16K33 display;


/**
 * @description main program loop
 */
void loop() {
    // DcsBios::loop();
}

/********************************* begin init functions *************************************/

/**
 * @description initializes output pins, serial connections and peripherals
 */
void setup() {
    setupOledDisplay();
    setup14segmentLedDisplays();
    // DcsBios::setup();
}

/**
 * @description inits SPI connection to OLED display then displays boot sequence slideshow/video
 */
void setupOledDisplay() {
    SSD1305_boot();
}

/**
 * @description inits I2C bus for 14 segment LED displays
 * 
 */
void setup14segmentLedDisplays() {
    Wire.begin(); //Join I2C bus

    if (display.begin() == false) {
        Serial.println("Device did not acknowledge! Freezing.");
    }
    Serial.println("Display acknowledged.");

    display.print("Milk");
}

/********************************** end init functions **************************************/

/**************************** begin DCS BIOS event handlers *********************************/

/**
 * @description handles output event to UFC options 1 display - 4 digit 14 segment display
 */
void onUfcOptionDisplay1Change(char* newValue) {
}
DcsBios::StringBuffer<4> ufcOptionDisplay1Buffer(0x7432, onUfcOptionDisplay1Change);

//TODO: add the other 5 options displays

/**
 * @description handles output event to UFC scratchpad big digit 1 display - oled display
 */
void onUfcScratchpadString1DisplayChange(char* newValue) {
}
DcsBios::StringBuffer<2> ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);

/**
 * @description handles output event to UFC scratchpad big digit 2 display - oled display
 */
void onUfcScratchpadString2DisplayChange(char* newValue) {
}
DcsBios::StringBuffer<2> ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);

/**
 * @description handles output event to UFC scratchpad number display - oled display
 */
void onUfcScratchpadNumberDisplayChange(char* newValue) {
}
DcsBios::StringBuffer<8> ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);

/***************************** end DCS BIOS event handlers **********************************/
