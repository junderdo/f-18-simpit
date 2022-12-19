/* 
 * @description main script for UFC controller board assumed to be an Arduino Uno R3
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * 
 * @notes Arduino Uno has an ATMega328P -- Arduino Leo does not like the OLED screen
 *      default: '#define DCSBIOS_IRQ_SERIAL'
 *          use '#define DCSBIOS_DEFAULT_SERIAL' instead if your Arduino board
 *          does not feature an ATMega328 or ATMega2650 controller.
 *      board: ELEGOO Nano Board CH 340/ATmega+328P (v3.0)
 *          need CH 340 usb driver installed to program it
 *      arduino IDE programmer and board settings:
 *          board: Arduino Uno
 *          programmer: AVRISP mkII
 */

#define DCSBIOS_IRQ_SERIAL
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include <DcsBios.h>
#include "oled.h"
#include "segment.h"
/************************** begin global variables and constants ****************************/

/*************************** end global variables and constants *****************************/

/******************************* begin main program loop ************************************/
/**
 * @description main program loop
 */
void loop() {
    // DcsBios::loop();
}
/******************************** end main program loop *************************************/

/********************************* begin init functions *************************************/

/**
 * @description initializes output pins, serial connections and peripherals
 */
void setup() {
    Serial.begin(9600);
    Serial.print("startup\n");
    setupOledDisplay();
    printToOLEDDisplay(SCRATCHPAD_1_ADDR, "XP");
    printToOLEDDisplay(SCRATCHPAD_2_ADDR, "AF");
    printToOLEDDisplay(SCRATCHPAD_3_ADDR, "30.0000");

    setup14segmentLedDisplays();
    // DcsBios::setup();
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
//     printToOLEDDisplay(SCRATCHPAD_1_ADDR, newValue);
// }
// DcsBios::StringBuffer<2> ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);

// /**
//  * @description handles output event to UFC scratchpad big digit 2 display - oled display
//  */
// void onUfcScratchpadString2DisplayChange(char* newValue) {
//     printToOLEDDisplay(SCRATCHPAD_2_ADDR, newValue);
// }
// DcsBios::StringBuffer<2> ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);

// /**
//  * @description handles output event to UFC scratchpad number display - oled display
//  */
// void onUfcScratchpadNumberDisplayChange(char* newValue) {
//     
// }
// DcsBios::StringBuffer<8> ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);

/***************************** end DCS BIOS event handlers **********************************/
