#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TimerEvent.h>
#include <Wire.h>
#include <SparkFun_Alphanumeric_Display.h>
#include "segment.h"

// 14 segment led displays
HT16K33 display;
const char segmentDisplayAddr[SEG_DISPLAY_COUNT] = {
    SEG_1_I2C_ADDR,
    SEG_2_I2C_ADDR,
    SEG_3_I2C_ADDR,
    SEG_4_I2C_ADDR,
    SEG_5_I2C_ADDR
};

uint8_t currentBus = 0;
const uint8_t displayBus[SEG_DISPLAY_COUNT] = {
    MULTIPLEXER_BUS_ADDR_1_TO_4,
    MULTIPLEXER_BUS_ADDR_1_TO_4,
    MULTIPLEXER_BUS_ADDR_1_TO_4,
    MULTIPLEXER_BUS_ADDR_1_TO_4,
    MULTIPLEXER_BUS_ADDR_5
};

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
    uint8_t busToWrite = displayBus[id];
    if (currentBus != busToWrite) {
        connectI2CBus(busToWrite);
    }

    // Serial.print("display.begin() start \n");
    display.begin(segmentDisplayAddr[id]);
    // unsigned long startTime = millis();
    // Serial.print("display.initialize() start \n");
    // TODO: do not initialize every time we print
    display.initialize();
    // Serial.print("time to initialize display: ");
    // Serial.print(millis() - startTime);
    // Serial.print(" ms \n");

    // startTime = millis();
    display.print(text);
    // Serial.print("time to print text to display: ");
    // Serial.print(millis() - startTime);
    // Serial.print(" ms \n");
}

/**
 * @description inits I2C bus for 14 segment LED displays
 * 
 */
void setup14segmentLedDisplays() {
    // Serial.print("starting segment displays\n");
    // join I2C bus
    Wire.begin();
    Wire.setClock(I2C_CLK_SPD);
    delay(10);
    // initialize bus connection
    connectI2CBus(currentBus);
    delay(10);
    // animated sequence
    printToSegmentDisplay(0, "----");
    delay(10);
    printToSegmentDisplay(1, "----");
    delay(10);
    printToSegmentDisplay(2, "----");
    delay(10);
    printToSegmentDisplay(3, "----");
    delay(10);
    printToSegmentDisplay(4, "----");
    delay(10);
    printToSegmentDisplay(0, "INIT");
    delay(10);
    printToSegmentDisplay(1, "0003");
    delay(10);
    printToSegmentDisplay(2, "0002");
    delay(10);
    printToSegmentDisplay(3, "0001");
    delay(10);
    printToSegmentDisplay(4, "0000");
    
    // clear the displays
    char* strToPrint = "    ";
    for (int j = 0; j < 5; j++) {
        printToSegmentDisplay(j, strToPrint);
        delay(10);
    }
    // Serial.print("segment displays initialized\n");
}