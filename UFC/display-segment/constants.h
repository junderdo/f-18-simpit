// #define DP 30
#define SEGMENT_DISPLAY_MODE_COMMON_CATHODE 0
#define SEGMENT_DISPLAY_MODE_COMMON_ANODE 1

// display mode is common cathode for my 7 segment display
const bool SEGMENT_DISPLAY_MODE = SEGMENT_DISPLAY_MODE_COMMON_CATHODE; // common cathode

const int SEGMENT_DISPLAY_COUNT = 5;

// pin number assignments for segment anodes
const int SEGMENT_PIN_A = 0;
const int SEGMENT_PIN_B = 1;
// note: On the Arduino Leonardo pins 2 and 3 do not work as digital outputs in combination with I2C (which is used by the lcd controller)
const int SEGMENT_PIN_C = 4;
const int SEGMENT_PIN_D = 5;
const int SEGMENT_PIN_E = 7;
const int SEGMENT_PIN_F = 12;
const int SEGMENT_PIN_G = 8;
const int SEGMENT_PIN_DP = 13; // decimal points on each digit not used

const int SEGMENT_DATA_LINES = 8;

const int SEGMENT_DATA_PINS[SEGMENT_DATA_LINES] = {
    SEGMENT_PIN_A,
    SEGMENT_PIN_B,
    SEGMENT_PIN_C,
    SEGMENT_PIN_D,
    SEGMENT_PIN_E,
    SEGMENT_PIN_F,
    SEGMENT_PIN_G,
    SEGMENT_PIN_DP
};
// note: missing controls for the single colon in the middle and single upper dot on the right side

// pin number assignments for segment digit pins (common cathodes)
const int SEGMENT_DIGIT_1 = 6;
const int SEGMENT_DIGIT_2 = 9;
const int SEGMENT_DIGIT_3 = 10;
const int SEGMENT_DIGIT_4 = 11;

const int SEGMENT_DIGIT_COUNT = 4;

const byte SEGMENT_DIGIT_PINS[SEGMENT_DIGIT_COUNT] {
    SEGMENT_DIGIT_1,
    SEGMENT_DIGIT_2,
    SEGMENT_DIGIT_3,
    SEGMENT_DIGIT_4
};

// display address pin assignments
const int SEGMENT_DISPLAY_ADDRESS_1 = 18;
const int SEGMENT_DISPLAY_ADDRESS_2 = 19;
const int SEGMENT_DISPLAY_ADDRESS_3 = 20;

const int SEGMENT_ADDRESS_LINES = 3;

const int SEGMENT_ADDRESS_PINS[SEGMENT_ADDRESS_LINES] = {
    SEGMENT_DISPLAY_ADDRESS_1,
    SEGMENT_DISPLAY_ADDRESS_2,
    SEGMENT_DISPLAY_ADDRESS_3
};

const byte SEGMENT_ADDRESS_OUT[SEGMENT_DISPLAY_COUNT][SEGMENT_ADDRESS_LINES] = { // lsb first
    {0, 0, 0},
    {1, 0, 0},
    {0, 1, 0},
    {1, 1, 0},
    {0, 0, 1},
};

const int CHARACTER_COUNT = 37;
const int BYTES_PER_CHAR = SEGMENT_DATA_LINES + 1; // the extra byte is the character
const byte CHARACTER_ARRAY[CHARACTER_COUNT][BYTES_PER_CHAR] { 
    {1, 1, 1, 1, 1, 1, 0, 0, '0'}, //0
    {0, 1, 1, 0, 0, 0, 0, 0, '1'}, //1
    {1, 1, 0, 1, 1, 0, 1, 0, '2'}, //2
    {1, 1, 1, 1, 0, 0, 1, 0, '3'}, //3
    {0, 1, 1, 0, 0, 1, 1, 0, '4'}, //4
    {1, 0, 1, 1, 0, 1, 1, 0, '5'}, //5
    {1, 0, 1, 1, 1, 1, 1, 0, '6'}, //6
    {1, 1, 1, 0, 0, 0, 0, 0, '7'}, //7
    {1, 1, 1, 1, 1, 1, 1, 0, '8'}, //8
    {1, 1, 1, 1, 0, 1, 1, 0, '9'}, //9
    {1, 1, 1, 0, 1, 1, 1, 0, 'a'}, //A/1
    {0, 0, 1, 1, 1, 1, 1, 0, 'b'}, //b/2
    {0, 0, 0, 1, 1, 0, 1, 0, 'c'}, //C/3
    {0, 1, 1, 1, 1, 0, 1, 0, 'd'}, //d/4
    {1, 0, 0, 1, 1, 1, 1, 0, 'e'}, //E/5
    {1, 0, 0, 0, 1, 1, 1, 0, 'f'}, //F/6
    {1, 0, 1, 1, 1, 1, 0, 0, 'g'}, //G/7
    {0, 1, 1, 0, 1, 1, 1, 0, 'h'}, //H/8
    {0, 1, 1, 0, 0, 0, 0, 0, 'i'}, //I/9
    {0, 1, 1, 1, 1, 0, 0, 0, 'j'}, //J/10
    {0, 0, 0, 1, 1, 1, 0, 0, 'l'}, //L/11
    {0, 0, 1, 0, 1, 0, 1, 0, 'n'}, //n/12
    {0, 0, 1, 1, 1, 0, 1, 0, 'o'}, //o/13
    {1, 1, 0, 0, 1, 1, 1, 0, 'p'}, //P/14
    {1, 1, 1, 0, 0, 1, 1, 0, 'q'}, //q/15
    {0, 0, 0, 0, 1, 0, 1, 0, 'r'}, //r/16
    {1, 0, 1, 1, 0, 1, 1, 0, 's'}, //S/17   looks like number 5
    {0, 0, 0, 1, 1, 1, 1, 0, 't'}, //t/18
    {0, 1, 1, 1, 1, 1, 0, 0, 'u'}, //U/19
    {0, 1, 1, 1, 0, 1, 1, 0, 'y'}, //y/20
    {0, 0, 0, 0, 0, 0, 0, 1, '.'}, //.
    {0, 0, 0, 0, 0, 0, 1, 0, '-'}, //dash/negative
    {0, 0, 0, 1, 0, 0, 0, 0, '_'}, //underscore
    {1, 0, 0, 1, 1, 1, 0, 0, '['}, //[
    {1, 1, 1, 1, 0, 0, 0, 0, ']'}, //]
    {1, 1, 0, 0, 1, 0, 1, 0, '?'}, //?
    {0, 0, 0, 0, 0, 0, 0, 0, ' '}//blank
};
