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
    // unsigned long startTime = millis();
    
    Wire.beginTransmission(MUX_I2C_ADDR);
    Wire.write(1 << bus); // shift a '1' onto the position of the byte to select bus
    Wire.endTransmission();

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
    // Serial.print("time to initialize display: ");
    // Serial.print(millis() - startTime);
    // Serial.print(" ms \n");

    startTime = millis();
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
    // join I2C bus
    Wire.begin();
    Wire.setClock(I2C_CLK_SPD);
    delay(10);
    
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