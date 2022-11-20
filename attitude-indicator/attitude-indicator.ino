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

#define PITCH_SERVO_PORT 3
#define BANK_SERVO_PORT 2

Servo sPitch; // pitch
Servo sBank; // bank / roll

float scalingFactor = 180.0 / 32768.0;

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
    Serial.begin(9600);
    setupServos();
    DcsBios::setup();
}

/**
 * @description initializes servos
 */
void setupServos() {
    // attach to the bank and pitch servos
    sPitch.attach(PITCH_SERVO_PORT); 
    sBank.attach(BANK_SERVO_PORT);

    // move the bank servo through full range of motion and return to center
    sPitch.write(90);
    sBank.write(90);

    delay(1000);
    sPitch.write(0);

    delay(1000);
    sPitch.write(90);

    delay(1000);
    sPitch.write(180);

    delay(1000);
    sPitch.write(90);


    // move the pitch servo through full range of motion and return to center
    delay(1000);
    sBank.write(90);

    delay(1000);
    sBank.write(70);

    delay(1000);
    sBank.write(90);

    delay(1000);
    sBank.write(110);

    delay(1000);
    sBank.write(90);
}

/********************************** end init functions **************************************/

/**************************** begin DCS BIOS event handlers *********************************/

void onSaiBankChange(unsigned int newValue) {
    int servoPos = max(0, min(180, newValue * scalingFactor - 90)); // range of motion of 0 - 180 degrees
    sPitch.write(servoPos);
}
DcsBios::IntegerBuffer saiBankBuffer(0x74d6, 0xffff, 0, onSaiBankChange);

void onSaiPitchChange(unsigned int newValue) {
    int servoPos = max(70, min(110, newValue * scalingFactor - 90)); // range of motion of 70 - 110 degrees
    sBank.write(servoPos);
}
DcsBios::IntegerBuffer saiPitchBuffer(0x74d4, 0xffff, 0, onSaiPitchChange);

/***************************** end DCS BIOS event handlers **********************************/
