#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <TimerEvent.h>
#include <SPI.h>
#include "ssd1305.h"
#include "oled.h"

// oled display
const char* oledDisplayText[SCRATCHPAD_SECTIONS_COUNT] = {
    "",
    "",
    ""
};
const int sectionFontSize[SCRATCHPAD_SECTIONS_COUNT] = {
    SCRATCHPAD_1_FONT_SIZE,
    SCRATCHPAD_2_FONT_SIZE,
    SCRATCHPAD_3_FONT_SIZE
};
const int sectionOrigin[SCRATCHPAD_SECTIONS_COUNT][2] = {
    {SCRATCHPAD_1_ORIGIN_X, SCRATCHPAD_1_ORIGIN_Y},
    {SCRATCHPAD_2_ORIGIN_X, SCRATCHPAD_2_ORIGIN_Y},
    {SCRATCHPAD_3_ORIGIN_X, SCRATCHPAD_3_ORIGIN_Y}
};

/**
 * @description refreshes the OLED display using the display buffer
 */
void refreshOledDisplay() {
    SSD1305_clear(oled_buf);
    for (int i = 0; i < SCRATCHPAD_SECTIONS_COUNT; i++) {
        SSD1305_string(
            sectionOrigin[i][0], // origin x
            sectionOrigin[i][1], // origin y
            oledDisplayText[i], // text to display
            sectionFontSize[i], // font size
            MODE_WRITE, // mode 0 = write
            oled_buf // buffer where screen data/pages are stored
        );
    }
    SSD1305_display(oled_buf);
}

/**
 * @description prints a string to a given section of the OLED display
 * @param section the section number to print/overwrite
 * @param text the text string to print
 */
void printToOLEDDisplay(int section, char* text) {
    if (section >= SCRATCHPAD_SECTIONS_COUNT) {
        return;
    }
    oledDisplayText[section] = text;
    refreshOledDisplay();
}

/**
 * @description inits SPI connection to OLED display then displays boot sequence slideshow/video
 */
void setupOledDisplay() {
    SSD1305_boot();
}