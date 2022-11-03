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

#define SEG_ADDR_BIT_0 7

// 14 segment display addresses
#define SEG_1_I2C_ADDR 0x70
#define SEG_2_I2C_ADDR 0x71
#define SEG_3_I2C_ADDR 0x72
#define SEG_4_I2C_ADDR 0x73
#define SEG_5_I2C_ADDR SEG_1_I2C_ADDR

// 14 segment led displays
HT16K33 display;
char *optionDisplayText[] = {"....", "....", "....", "....", "...."};


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
    Serial.print("setup \n");
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
    // set bus address output pinmode
    pinMode(SEG_ADDR_BIT_0, OUTPUT);
    digitalWrite(SEG_ADDR_BIT_0, LOW);
    // join I2C bus
    Wire.begin();
    display.begin(SEG_1_I2C_ADDR, SEG_2_I2C_ADDR, SEG_3_I2C_ADDR, SEG_4_I2C_ADDR);
    // animated sequence
    // for (int i = 0; i < 6; i++) {
    //     for (int j = 0; j < 5; j++) {
    //         char* strToPrint = "....";
    //         if (i == j) {
    //             strToPrint = "INIT";
    //         }
    //         printToSegmentDisplay(j, strToPrint);
    //     }
    //     delay(100);
    // }

    display.print("TEST");

    printToSegmentDisplay(0, "ABCD");
    delay(100);
    printToSegmentDisplay(1, "EFGH");
    delay(100);
    printToSegmentDisplay(2, "IJKL");
    delay(100);
    printToSegmentDisplay(3, "MNOP");
    // delay(100);
    // printToSegmentDisplay(4, "QRST");
}

/**
 * @description prints a 4 character long string to a 14 segment led display
 * @param id the index of the print display
 * @param text the text to print -- length must always be 4 characters
 */
void printToSegmentDisplay(int id, char* text) {
    optionDisplayText[id] = text;
    Serial.print("printToSegmentDisplay called \n");
    Serial.print(id);
    Serial.print("\n");
    Serial.print(text);
    Serial.print("\n");
    char displayText[] = "                "; // 16 chars
    if (id < 4) {
        // first four displays are on one bus
        digitalWrite(SEG_ADDR_BIT_0, LOW);
        strcpy(displayText, *optionDisplayText[0]);
        strcat(displayText, *optionDisplayText[1]);
        strcat(displayText, *optionDisplayText[2]);
        strcat(displayText, *optionDisplayText[3]);
    } else {
        // the 5th display is on a separate bus since there are only 4 possible
        // addresses on the segment display hardware
        digitalWrite(SEG_ADDR_BIT_0, HIGH);
        strcpy(displayText, *optionDisplayText[4]);
    }

    delay(10);
    display.initialize();
    delay(10);
    display.print(displayText);
    delay(10);
    free(displayText);
}

/********************************** end init functions **************************************/

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
