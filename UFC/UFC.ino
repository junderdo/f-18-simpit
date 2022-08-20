/* 
 * @description main script for UFC controller board assumed to be an Arduino Leonardo
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * 
 * notes from DCS BIOS author:
 *      default: '#define DCSBIOS_IRQ_SERIAL'
 *      use '#define DCSBIOS_DEFAULT_SERIAL' instead if your Arduino board
 *      does not feature an ATMega328 or ATMega2650 controller.
 * 
 * my notes:
 *      my Arduino Leo has an ATmega32u4
 * 
 */
#define DCSBIOS_DEFAULT_SERIAL
#include "display-segment/constants.h"
#include "display-segment/functions.h"
#include "display-lcd/constants.h"
#include <DcsBios.h>
#include <LiquidCrystal_I2C.h>
#include <TimerEvent.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_CHARS_PER_LINE, LCD_LINE_COUNT);

/**
 * @description main program loop
 */
void loop() {
    digitalWrite( 13, HIGH);
    Serial.println("Hello");
    delay(1000);
    digitalWrite( 13, LOW);

    // DcsBios::loop();
    // segmentTimer.update();
}

/********************************* begin init functions *************************************/

/**
 * @description initializes output pins, serial connections and peripherals
 */
void setup() {
    Serial.begin(9600);
    pinMode( 13, OUTPUT );
    // setupLCDDisplays();
    // setupSegmentDisplays();
    // DcsBios::setup();
}

/**
 * @description initializes backlit lcd display(s)
 */
void setupLCDDisplays() {
    // init backlit lcd 2 line screen
    lcd.init();
    lcd.backlight(); // enable backlight
    lcd.setCursor(0, 0); // set the cursor to column 0, line 0
    lcd.print("initializing..."); // Print a message to the LCD
}

/**
 * @description initializes 4 character 7 segment led displays
 */
void setupSegmentDisplays() {
    // set the pin mode to output for segment driver pins
    pinMode(SEGMENT_PIN_A, OUTPUT);
    pinMode(SEGMENT_PIN_B, OUTPUT);
    pinMode(SEGMENT_PIN_C, OUTPUT);
    pinMode(SEGMENT_PIN_D, OUTPUT);
    pinMode(SEGMENT_PIN_E, OUTPUT);
    pinMode(SEGMENT_PIN_F, OUTPUT);
    pinMode(SEGMENT_PIN_G, OUTPUT);
    pinMode(SEGMENT_PIN_DP, OUTPUT);
    pinMode(SEGMENT_DIGIT_1, OUTPUT);
    pinMode(SEGMENT_DIGIT_2, OUTPUT);
    pinMode(SEGMENT_DIGIT_3, OUTPUT);
    pinMode(SEGMENT_DIGIT_4, OUTPUT);
    printStringTo7SegmentDisplay("ABCD", 0);
    
}
/********************************** end init functions **************************************/

/**************************** begin DCS BIOS event handlers *********************************/

/**
 * @description handles output event to UFC options 1 - 4 digit 7 segment display
 */
void onUfcOptionDisplay1Change(char* newValue) {
    printStringTo7SegmentDisplay((String) newValue, 0);
}
DcsBios::StringBuffer<4> ufcOptionDisplay1Buffer(0x7432, onUfcOptionDisplay1Change);

/**
 * @description handles output event to UFC scratchpad big digit 1 display - 2 line lcd display
 */
void onUfcScratchpadString1DisplayChange(char* newValue) {
    lcd.setCursor(0, 0); // set the cursor to col 0, line 0
    lcd.print(newValue);  // Print a message to the LCD
}
DcsBios::StringBuffer<2> ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);

/**
 * @description handles output event to UFC scratchpad big digit 2 display - 2 line lcd display
 */
void onUfcScratchpadString2DisplayChange(char* newValue) {
    lcd.setCursor(1, 0); // set the cursor to col 2, line 0
    lcd.print(newValue);  // Print a message to the LCD
}
DcsBios::StringBuffer<2> ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);

/**
 * @description handles output event to UFC scratchpad number display - 2 line lcd display
 */
void onUfcScratchpadNumberDisplayChange(char* newValue) {
    int col = LCD_CHARS_PER_LINE - strlen(newValue);
    lcd.setCursor(col, 0); // set the cursor to col, line 0
    lcd.print(newValue);  // Print a message to the LCD
}
DcsBios::StringBuffer<8> ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);

/***************************** end DCS BIOS event handlers **********************************/
