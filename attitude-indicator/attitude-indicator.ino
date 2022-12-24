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

Servo sPitch; // pitch
Servo sBank; // bank / roll

float scalingFactor = 180 / 32768.0;

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
    // Serial.begin(9600);
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

    delay(100);
    sPitch.write(80);
    delay(100);
    sBank.write(45);
    delay(100);
    sPitch.write(70);
    delay(100);
    sBank.write(0);


    delay(100);
    sPitch.write(80);
    delay(100);
    sBank.write(45);
    delay(100);
    sPitch.write(90);
    delay(100);
    sBank.write(90);

    delay(100);
    sPitch.write(100);
    delay(100);
    sBank.write(135);
    delay(100);
    sPitch.write(110);
    delay(100);
    sBank.write(180);

    delay(100);
    sPitch.write(100);
    delay(100);
    sBank.write(135);
    delay(100);
    sPitch.write(90);
    delay(100);
    sBank.write(90);  
}

/********************************** end init functions **************************************/

/**************************** begin DCS BIOS event handlers *********************************/

void onSaiBankChange(unsigned int newValue) {
    int servoPos = map(newValue, 0, 65535, 0, 180); // range of motion [0, 180] degrees
    sBank.write(servoPos);
}
DcsBios::IntegerBuffer saiBankBuffer(0x74d6, 0xffff, 0, onSaiBankChange);

void onSaiPitchChange(unsigned int newValue) {
    int servoPos = max(70, min(110, map(newValue, 0, 65535, 0, 180))); // range of motion [70, 110] degrees
    sPitch.write(servoPos);
}
DcsBios::IntegerBuffer saiPitchBuffer(0x74d4, 0xffff, 0, onSaiPitchChange);

/***************************** end DCS BIOS event handlers **********************************/
