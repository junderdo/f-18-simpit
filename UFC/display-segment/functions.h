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
 * @param outputDigitPin the pin to which the char will be printed
 */
void printCharTo7SegmentDigit(
    char charToPrint,
    int outputDigitPin
){
    reset7Segment(); 
    digitalWrite(outputDigitPin, SEGMENT_DISPLAY_MODE);

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
        for (int i = 0; i <= 7; i++) {
            if (SEGMENT_DISPLAY_MODE == SEGMENT_DISPLAY_MODE_COMMON_CATHODE) {
                digitalWrite(SEGMENT_DIGIT[i], !CHARACTER_ARRAY[characterIndex][i]);
            } else if(SEGMENT_DISPLAY_MODE == SEGMENT_DISPLAY_MODE_COMMON_CATHODE) {
                digitalWrite(SEGMENT_DIGIT[i], CHARACTER_ARRAY[characterIndex][i]);
            }
        }
    }

    Serial.print(!CHARACTER_ARRAY[characterIndex]);
}

/**
 * @description prints a string to the 4 digit 7 segment display
 * @param stringToPrint the string to print
 * @param displayPeriod the period of time for which the string will be printed in milliseconds
 * @param displayIndex the display index that corresponds to the output display
 */
void printStringTo7SegmentDisplay(
    String stringToPrint,
    int displayIndex
) {
    segmentDisplayStringArray[displayIndex] = stringToPrint;
    // TODO: use displayIndex to output to the correct display to enable multiple displays
    char char1 = stringToPrint.charAt(0);
    char char2 = stringToPrint.charAt(1);
    char char3 = stringToPrint.charAt(2);
    char char4 = stringToPrint.charAt(3);
    int stringLength = stringToPrint.length();

    if (1 > stringLength)
        char1 = ' ';
    else
        char1 = stringToPrint.charAt(0);
    if (2 > stringLength)
        char2 = ' ';
    else
        char2 = stringToPrint.charAt(1);
    if (3 > stringLength)
        char3 = ' ';
    else
        char3 = stringToPrint.charAt(2);
    if (4 > stringLength)
        char4 = ' ';
    else
        char4 = stringToPrint.charAt(3);

    printCharTo7SegmentDigit(char1, SEGMENT_DIGIT_1);
    printCharTo7SegmentDigit(char2, SEGMENT_DIGIT_2);
    printCharTo7SegmentDigit(char3, SEGMENT_DIGIT_3);
    printCharTo7SegmentDigit(char4, SEGMENT_DIGIT_4);
}
