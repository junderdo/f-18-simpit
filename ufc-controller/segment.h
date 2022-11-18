/* 
 * @description 14-segment multiplexed display controller 
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 */

#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#define I2C_CLK_SPD 100000 // in hz

// 14 segment display addresses
#define SEG_1_I2C_ADDR 0x70
#define SEG_2_I2C_ADDR 0x71
#define SEG_3_I2C_ADDR 0x72
#define SEG_4_I2C_ADDR 0x73
#define SEG_5_I2C_ADDR 0x70 // on a separate bus from the first 4 displays
#define SEG_DISPLAY_COUNT 5

// i2c segment bus multiplexer addresses
#define MULTIPLEXER_BUS_ADDR_1_TO_4 0 // bus connected to segment displays 1 through 4
#define MULTIPLEXER_BUS_ADDR_5 1 // bus connected to segment display 5

// TCA9548A i2c bus multiplexer
// tie A0, A1, A2 to VCC so that the 0x77 address is assigned to the TCA9548A multiplexer
// the default is 0x70 and the 14 segment displays can only be assigned 0x70 - 0x73
#define MUX_I2C_ADDR 0x77

void connectI2CBus(uint8_t bus);
void printToSegmentDisplay(int id, char text[4]);
void setup14segmentLedDisplays();

#endif