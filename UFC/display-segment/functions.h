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

    int character = -1; // id for non-displayable characters
    for (int i = 0; i < CHARACTER_COUNT; i++){
        if (charToPrint == CHARACTER_ARRAY[i][8]){
            character = i;
        }
    }

    if (character == -1) {
        // for non-displayable characters display a hyphen
        digitalWrite(SEGMENT_PIN_G, !SEGMENT_DISPLAY_MODE);
    } else {
        for (int i = 0; i <= 7; i++) {
            if (SEGMENT_DISPLAY_MODE == SEGMENT_DISPLAY_MODE_COMMON_CATHODE) {
                digitalWrite(SEGMENT_DIGIT[i], !CHARACTER_ARRAY[character][i]);
            } else if(SEGMENT_DISPLAY_MODE == SEGMENT_DISPLAY_MODE_COMMON_CATHODE) {
                digitalWrite(SEGMENT_DIGIT[i], CHARACTER_ARRAY[character][i]);
            }
        }
    }
}

/**
 * @description prints a string to the 4 digit 7 segment display
 * @param stringToPrint the string to print
 * @param displayPeriod the period of time for which the string will be printed in milliseconds
 * TODO: set this on a timer instead of looping for a long display period
 */
void printStringTo7Segment(
    String stringToPrint,
    int displayPeriod
) {
    char char1 = stringToPrint.charAt(0);
    char char2 = stringToPrint.charAt(1);
    char char3 = stringToPrint.charAt(2);
    char char4 = stringToPrint.charAt(3);
    int stringLength = stringToPrint.length();
    if (stringLength < 5) {
        for (int ti = 0; ti <= (displayPeriod / 8); ti++) {
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
            delay(DIGIT_SWITCH_DELAY);
            printCharTo7SegmentDigit(char2, SEGMENT_DIGIT_2);
            delay(DIGIT_SWITCH_DELAY);
            printCharTo7SegmentDigit(char3, SEGMENT_DIGIT_3);
            delay(DIGIT_SWITCH_DELAY);
            printCharTo7SegmentDigit(char4, SEGMENT_DIGIT_4);
            delay(DIGIT_SWITCH_DELAY);
        }
    } else {
        for (int t = 0; t <= stringLength; t++) {
            for (int ti = 0; ti <= (displayPeriod / 8); ti++) {
                // reset();
                // delay(DIGIT_SWITCH_DELAY);
                printCharTo7SegmentDigit(char1, SEGMENT_DIGIT_1);
                delay(DIGIT_SWITCH_DELAY);
                printCharTo7SegmentDigit(char2, SEGMENT_DIGIT_2);
                delay(DIGIT_SWITCH_DELAY);
                printCharTo7SegmentDigit(char3, SEGMENT_DIGIT_3);
                delay(DIGIT_SWITCH_DELAY);
                printCharTo7SegmentDigit(char4, SEGMENT_DIGIT_4);
                delay(DIGIT_SWITCH_DELAY);
            }
            if (t + 1 > stringLength)
                char1 = ' ';
            else
                char1 = stringToPrint.charAt(t);
            if ((t + 2) > stringLength)
                char2 = ' ';
            else
                char2 = stringToPrint.charAt(t + 1);
            if ((t + 3) > stringLength)
                char3 = ' ';
            else
                char3 = stringToPrint.charAt(t + 2);
            if ((t + 4) > stringLength)
                char4 = ' ';
            else
                char4 = stringToPrint.charAt(t + 3);
        }
    }
}

/**
 * @description refreshes a 7 segment display
 * @param displayString the character String to display
 * @param displayIndex the number corresponding to the display component to refresh
 */
void refreshSegmentDisplay(String displayString, int displayIndex) {
    printStringTo7Segment(displayString, SEGMENT_DISPLAY_PERIOD);
}
