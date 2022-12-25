/* 
 * @description oled controller 
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 */
#ifndef _OLED_H_
#define _OLED_H_

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

// oled scratchpad output locations
#define SCRATCHPAD_SECTIONS_COUNT 3
// scratchpad 1 - 2 char display
#define SCRATCHPAD_1_ADDR 0
#define SCRATCHPAD_1_ORIGIN_X 6
#define SCRATCHPAD_1_ORIGIN_Y 9
#define SCRATCHPAD_1_FONT_SIZE 16
// scratchpad 1 - 2 char display
#define SCRATCHPAD_2_ADDR 1
#define SCRATCHPAD_2_ORIGIN_X 32
#define SCRATCHPAD_2_ORIGIN_Y 9
#define SCRATCHPAD_2_FONT_SIZE 16
// scratchpad 1 - 8+ char display
#define SCRATCHPAD_3_ADDR 2
#define SCRATCHPAD_3_ORIGIN_X 58
#define SCRATCHPAD_3_ORIGIN_Y 9
#define SCRATCHPAD_3_FONT_SIZE 16

#define MODE_WRITE 0

void refreshOledDisplay();
void printToOLEDDisplay(int section, char* text);
void setupOledDisplay();

#endif