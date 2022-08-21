/* 
 * @description functions for controlling 4 digit 7 segment displays
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * TODO: enable up to 8, 7 segment displays by using pins 1,2 and 13 to be address lines for selecting
 *      which display to control. use a 3 to 8 decoder circuit to pass the control outputs to the display
 *      that we need to refresh. have each decoder ouput pin go to an input of an AND gate. the other
 *      input for each AND gate is the control output and the output of each AND gate will go to the
 *      control input on the 7 segment display to which it corresponds
 */

/**
 * @description resets the seven segment display digits
 */
void reset7Segment() {
    for (int i = 0; i < SEGMENT_DIGIT_COUNT; i++) {
        digitalWrite(SEGMENT_DIGIT_PINS[i], !SEGMENT_DISPLAY_MODE);
    }
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
    // turn the digit on
    digitalWrite(segmentDigitPin, SEGMENT_DISPLAY_MODE);

    // find the index of the character to be displayed
    int characterIndex = -1; // id for non-displayable characters
    for (int i = 0; i < CHARACTER_COUNT; i++){
        // the data line bytes/bits are first and character is at the end of sub-array
        if (charToPrint == CHARACTER_ARRAY[i][SEGMENT_DATA_LINES]) {
            characterIndex = i;
        }
    }
    // write character to digit
    if (characterIndex >= 0 && characterIndex < CHARACTER_COUNT) {
        // write each data line output for this character
        for (int i = 0; i < SEGMENT_DATA_LINES; i++) {
            if (SEGMENT_DISPLAY_MODE == SEGMENT_DISPLAY_MODE_COMMON_ANODE) {
                digitalWrite(SEGMENT_DATA_PINS[i], !CHARACTER_ARRAY[characterIndex][i]);
            } else if (SEGMENT_DISPLAY_MODE == SEGMENT_DISPLAY_MODE_COMMON_CATHODE) {
                digitalWrite(SEGMENT_DATA_PINS[i], CHARACTER_ARRAY[characterIndex][i]);
            }
        }
    } else {
        // for non-displayable/unrecognized characters display a hyphen
        digitalWrite(SEGMENT_PIN_G, !SEGMENT_DISPLAY_MODE);
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

    // convert string to be displayable on our 7 segment led display
    stringToPrint.toLowerCase();
    int length = stringToPrint.length();
    int paddingLength = SEGMENT_DIGIT_COUNT - length;
    if (paddingLength > 0) {
        for (int i = 0; i < paddingLength; i++) {
            stringToPrint = " " + stringToPrint;
        }
    }
    // string now has same character count as display's digit count
    // also string characters have been converted to display's character set

    // write to the address lines to select a display
    for (int i = 0; i < SEGMENT_ADDRESS_LINES; i++) {
        digitalWrite(SEGMENT_ADDRESS_PINS[i], SEGMENT_ADDRESS_OUT[displayIndex][i]);
    }

    // write each character/digit
    for (int i = 0; i < SEGMENT_DIGIT_COUNT; i++) {
        printCharTo7SegmentDigit(stringToPrint.charAt(i), SEGMENT_DIGIT_PINS[i]);
        delay(2);
    }
    
}
