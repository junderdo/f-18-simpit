/* 
 * @description main script for attitude indicator controller board assumed to be an Arduino Pro Micro
 * @author Jeff Underdown <jeff.underdown@gmail.com>
 * 
 * notes from DCS BIOS author:
 *      default: '#define DCSBIOS_IRQ_SERIAL'
 *      use '#define DCSBIOS_DEFAULT_SERIAL' instead if your Arduino board
 *      does not feature an ATMega328 or ATMega2650 controller.
 * 
 * my notes:
 *      board: ELEGOO Nano Board CH 340/ATmega+328P (v3.0)
 *      need CH 340 usb driver installed to program it
 * arduino IDE programmer and board settings
 *      board: Arduino Mini
 *      processor: Atmega328P
 *      programmer: AVRISP mkII
 * 
 */
#include <Servo.h>
#include <Wire.h>
#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>

#define BANK_SERVO_PORT 2
#define PITCH_SERVO_PORT 3

#define BANK_ORIGIN 90 // both servos are centered at 90 degrees;
#define BANK_MIN 0
#define BANK_MAX 180
#define PITCH_ORIGIN 90
#define PITCH_MIN 70
#define PITCH_MAX 110

Servo sBank; // bank / roll
Servo sPitch; // pitch

/**
 * @description main program loop
 */
void loop() {
    DcsBios::loop();
}

/********************************* begin init functions *************************************/

/**
 * @description initializes output pins, serial connections and peripherals
 */
void setup() {
    setupServos();
    // DcsBios::setup();
}

/**
 * @description initializes servos
 */
void setupServos() {
    // attach to the bank and pitch servos
    sPitch.attach(PITCH_SERVO_PORT); 
    sBank.attach(BANK_SERVO_PORT);

    // center both axis servos
    setBank(BANK_ORIGIN);
    setPitch(PITCH_ORIGIN);

    selfTest();
}

/**
 * @description moves the bank and pitch servos through full range of motion then returns to center
 */
void selfTest() {
    int deltaT = 17; // 1000 ms / 60fps = 16.66...
    int deltaBank = 3; // 180 deg / 60 fps = 3 deg
    int deltaPitch = 1; // 40 deg / 60 fps =< 1 deg
    int halfRotationFrameCount = 30;
    for (
        int i = 0;
        i > 0 - halfRotationFrameCount;
        i--
    ) {
        setBank(BANK_ORIGIN + (deltaBank * i));
        setPitch(PITCH_ORIGIN + (deltaPitch * i));
        delay(deltaT);
    }

    for (
        int i = 0 - halfRotationFrameCount;
        i < halfRotationFrameCount;
        i++
    ) {
        setBank(BANK_ORIGIN + (deltaBank * i));
        setPitch(PITCH_ORIGIN + (deltaPitch * i));
        delay(deltaT);
    }

    for (
        int i = halfRotationFrameCount;
        i > 0;
        i--
    ) {
        setBank(BANK_ORIGIN + (deltaBank * i));
        setPitch(PITCH_ORIGIN + (deltaPitch * i));
        delay(deltaT);
    }
}

/********************************** end init functions **************************************/

/*************************** begin servo controller methods *********************************/

/**
 * @description sets bank servo rotation value
 * @param bank the new rotation angle in degrees
 */
void setBank(int bank) {
    sBank.write(
        max(0, min(180, bank))
    );
}

/**
 * @description sets pitch servo rotation value
 * @param pitch the new rotation angle in degrees
 */
void setPitch(int pitch) {
    sPitch.write(
        max(70, min(110, pitch))
    );
}

/**************************** end servo controller methods **********************************/

/**************************** begin DCS BIOS event handlers *********************************/

void onSaiBankChange(unsigned int newValue) {
    setBank(map(newValue, 0, 65535, 0, 180)); // range of motion [0, 180] degrees
}
DcsBios::IntegerBuffer saiBankBuffer(0x74d6, 0xffff, 0, onSaiBankChange);

void onSaiPitchChange(unsigned int newValue) {
    setPitch(map(newValue, 0, 65535, 0, 180)); // range of motion [70, 110] degrees
}
DcsBios::IntegerBuffer saiPitchBuffer(0x74d4, 0xffff, 0, onSaiPitchChange);

/***************************** end DCS BIOS event handlers **********************************/
