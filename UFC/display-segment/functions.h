/* 
 * @description functions for controlling 4 digit 7 segment displays
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * TODO: enable up to 8, 7 segment displays by using pins 1,2 and 13 to be address lines for selecting
 *      which display to control. use a 3 to 8 decoder circuit to pass the control outputs to the display
 *      that we need to refresh. have each decoder ouput pin go to an input of an AND gate. the other
 *      input for each AND gate is the control output and the output of each AND gate will go to the
 *      control input on the 7 segment display to which it corresponds
 *      https://www.digikey.com/en/products/base-product/texas-instruments/296/74LS138/240
 */

String segmentDisplayStringArray[SEGMENT_DISPLAY_COUNT] = { "", "", "", "", "", "" };

/**
 * @description resets the seven segment display digits
 */
void reset7Segment() {
    digitalWrite(SEGMENT_DIGIT_1, !SEGMENT_DISPLAY_MODE);
    digitalWrite(SEGMENT_DIGIT_2, !SEGMENT_DISPLAY_MODE);
    digitalWrite(SEGMENT_DIGIT_3, !SEGMENT_DISPLAY_MODE);
    digitalWrite(SEGMENT_DIGIT_4, !SEGMENT_DISPLAY_MODE); 
}

/**
 * @description displays a character on the given digit of the 4 digit 7 segment display
 * @param characterToPrint the character to print
 * @param segmentDigitPin the pin to which the char will be printed
 */
void printCharTo7SegmentDigit(
    char charToPrint,
    int segmentDigitPin
){
    digitalWrite(segmentDigitPin, SEGMENT_DISPLAY_MODE);

    // find the index of the character to be displayed
    int characterIndex = -1; // id for non-displayable characters
    for (int i = 0; i < CHARACTER_COUNT; i++){
        if (charToPrint == CHARACTER_ARRAY[i][8]){
            characterIndex = i;
        }
    }

    if (characterIndex == -1) {
        // for non-displayable/unrecognized characters display a hyphen
        digitalWrite(SEGMENT_PIN_G, !SEGMENT_DISPLAY_MODE);
    } else {
        for (int i = 0; i < 8; i++) {
            if (SEGMENT_DISPLAY_MODE == SEGMENT_DISPLAY_MODE_COMMON_ANODE) {
                digitalWrite(SEGMENT_PINS[i], !CHARACTER_ARRAY[characterIndex][i]);
            } else if (SEGMENT_DISPLAY_MODE ==SEGMENT_DISPLAY_MODE_COMMON_CATHODE) {
                digitalWrite(SEGMENT_PINS[i], CHARACTER_ARRAY[characterIndex][i]);
            }
        }
    }
}

/**
 * @description prints a string to the 4 digit 7 segment display
 * @param stringToPrint the string to print only first 4 digits will be displayed
 * @param displayPeriod the period of time for which the string will be printed in milliseconds
 * @param displayIndex the display index that corresponds to the output display
 */
void printStringTo7SegmentDisplay(
    String stringToPrint,
    int displayIndex
) {
    reset7Segment();
    // TODO: use displayIndex to output to the correct display to enable multiple displays
    stringToPrint.toLowerCase();
    int length = stringToPrint.length();
    int paddingLength = 4 - length;
    if (paddingLength > 0) {
        for (int i = 0; i < paddingLength; i++) {
            stringToPrint = " " + stringToPrint;
        }
    }
    printCharTo7SegmentDigit(stringToPrint.charAt(0), SEGMENT_DIGIT_1);
    delay(2);
    printCharTo7SegmentDigit(stringToPrint.charAt(1), SEGMENT_DIGIT_2);
    delay(2);
    printCharTo7SegmentDigit(stringToPrint.charAt(2), SEGMENT_DIGIT_3);
    delay(2);
    printCharTo7SegmentDigit(stringToPrint.charAt(3), SEGMENT_DIGIT_4);
    delay(2);
}
