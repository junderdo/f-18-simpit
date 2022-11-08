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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <DcsBios.h>
#include <TimerEvent.h>
#include <Wire.h>
#include <SPI.h>
#include <SparkFun_Alphanumeric_Display.h>
#include "ssd1305.h"

// oled display constants
#define WIDTH     128
#define HEIGHT     32
#define PAGES       4
// spi interface oled display pin assigments
#define OLED_RST    9 // reset pin
#define OLED_DC     8 // data/command pin -- set by controller (uc) to indicate whether data or command will be sent to peripheral
#define OLED_CS    10 // chip select pin
#define SPI_MOSI   11 // data in pin -- data and commands sent through this pin
#define SPI_SCK    13 // spi clock pin

#define I2C_CLK_SPD 100000 // in hz

// 14 segment display addresses
#define SEG_1_I2C_ADDR 0x70
#define SEG_2_I2C_ADDR 0x71
#define SEG_3_I2C_ADDR 0x72
#define SEG_4_I2C_ADDR 0x73
#define SEG_5_I2C_ADDR 0x70 // on a separate bus from the first 4 displays

// i2c segment bus multiplexer addresses
#define MULTIPLEXER_BUS_ADDR_1_TO_4 0 // bus connected to segment displays 1 through 4
#define MULTIPLEXER_BUS_ADDR_5 1 // bus connected to segment display 5


// TCA9548A i2c bus multiplexer
// tie A0, A1, A2 to VCC so that the 0x77 address is assigned to the TCA9548A multiplexer
// the default is 0x70 and the 14 segment displays can only be assigned 0x70 - 0x73
#define MUX_I2C_ADDR 0x77

// 14 segment led displays
HT16K33 display;
const char segmentDisplayAddr[] = {
    SEG_1_I2C_ADDR,
    SEG_2_I2C_ADDR,
    SEG_3_I2C_ADDR,
    SEG_4_I2C_ADDR,
    SEG_5_I2C_ADDR
};

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
    Serial.begin(9600);
    Serial.print("startup\n");
    setup14segmentLedDisplays();
    setupOledDisplay();
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
    // join I2C bus
    Wire.begin();
    Wire.setClock(I2C_CLK_SPD);
    
    // animated sequence
    printToSegmentDisplay(0, "----");
    printToSegmentDisplay(1, "----");
    printToSegmentDisplay(2, "----");
    printToSegmentDisplay(3, "----");
    printToSegmentDisplay(4, "----");
    printToSegmentDisplay(0, "INIT");
    printToSegmentDisplay(1, "0003");
    printToSegmentDisplay(2, "0002");
    printToSegmentDisplay(3, "0001");
    printToSegmentDisplay(4, "0000");
    for (int j = 0; j < 5; j++) {
        char* strToPrint = "    ";
        printToSegmentDisplay(j, strToPrint);
    }
}

/********************************** end init functions **************************************/

/******************************** begin utility functions ***********************************/
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
    
    Wire.beginTransmission(MUX_I2C_ADDR);
    Wire.write(1 << bus); // shift a '1' onto the position of the byte to select bus
    Wire.endTransmission();

    Serial.print("time to connect to bus: ");
    Serial.print(millis() - startTime);
    Serial.print(" ms \n");
    // Serial.print("bus #");
    // Serial.print(bus);
    // Serial.print("\n");
}

/**
 * @description prints a 4 character long string to a 14 segment led display
 * @param id the index of the print display
 * @param text the text to print -- length must always be 4 characters
 */
void printToSegmentDisplay(int id, char text[4]) {
    // Serial.print("printing to segment #");
    // Serial.print(id);
    // Serial.print("\n");
    // Serial.print(text);
    // Serial.print("\n");
    if (id < 4) {
        // the first four displays are on one bus and share one string buffer
        connectI2CBus(MULTIPLEXER_BUS_ADDR_1_TO_4);
    } else {
        // the 5th display is on a separate bus since there are only 4 possible
        // addresses on the segment display hardware
        connectI2CBus(MULTIPLEXER_BUS_ADDR_5);
    }
    display.begin(segmentDisplayAddr[id]);
    // TODO: do not initialize every time we print
    
    unsigned long startTime = millis();
    display.initialize();
    Serial.print("time to initialize display: ");
    Serial.print(millis() - startTime);
    Serial.print(" ms \n");

    startTime = millis();
    display.print(text);
    Serial.print("time to print text to display: ");
    Serial.print(millis() - startTime);
    Serial.print(" ms \n");
}

/********************************* end utility functions ************************************/

/**************************** begin DCS BIOS event handlers *********************************/

// /**
//  * @description handles output event to UFC options 1 display - 4 digit 14 segment display
//  */
// void onUfcOptionDisplay1Change(char* newValue) {
//     printToSegmentDisplay(0, newValue);
// }
// DcsBios::StringBuffer<4> ufcOptionDisplay1Buffer(0x7432, onUfcOptionDisplay1Change);

// /**
//  * @description handles output event to UFC options 2 display - 4 digit 14 segment display
//  */
// void onUfcOptionDisplay2Change(char* newValue) {
//     printToSegmentDisplay(1, newValue);
// }
// DcsBios::StringBuffer<4> ufcOptionDisplay2Buffer(0x7436, onUfcOptionDisplay2Change);

// /**
//  * @description handles output event to UFC options 3 display - 4 digit 14 segment display
//  */
// void onUfcOptionDisplay3Change(char* newValue) {
//     printToSegmentDisplay(2, newValue);
// }
// DcsBios::StringBuffer<4> ufcOptionDisplay3Buffer(0x743a, onUfcOptionDisplay3Change);

// /**
//  * @description handles output event to UFC options 4 display - 4 digit 14 segment display
//  */
// void onUfcOptionDisplay4Change(char* newValue) {
//     printToSegmentDisplay(3, newValue);
// }
// DcsBios::StringBuffer<4> ufcOptionDisplay4Buffer(0x743e, onUfcOptionDisplay4Change);

// /**
//  * @description handles output event to UFC options 5 display - 4 digit 14 segment display
//  */
// void onUfcOptionDisplay5Change(char* newValue) {
//     printToSegmentDisplay(4, newValue);
// }
// DcsBios::StringBuffer<4> ufcOptionDisplay5Buffer(0x7442, onUfcOptionDisplay5Change);

// /**
//  * @description handles output event to UFC scratchpad big digit 1 display - oled display
//  */
// void onUfcScratchpadString1DisplayChange(char* newValue) {
// }
// DcsBios::StringBuffer<2> ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);

// /**
//  * @description handles output event to UFC scratchpad big digit 2 display - oled display
//  */
// void onUfcScratchpadString2DisplayChange(char* newValue) {
// }
// DcsBios::StringBuffer<2> ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);

// /**
//  * @description handles output event to UFC scratchpad number display - oled display
//  */
// void onUfcScratchpadNumberDisplayChange(char* newValue) {
// }
// DcsBios::StringBuffer<8> ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);

/***************************** end DCS BIOS event handlers **********************************/
