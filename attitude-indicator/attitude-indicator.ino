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
 *      my Arduino Pro Micro has an ATmega32u4
 * 
 */
#include <Servo.h>
#include <Wire.h>
#define DCSBIOS_DEFAULT_SERIAL
#include <DcsBios.h>

// 

Servo s1;
Servo s2;

float scalingFactor = 180.0 / 32768.0;

/**
 * @description main program loop
 */
void loop() {
    // moveServos();
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
    s1.attach(2); 
    s2.attach(3);



    s1.write(90);
    s2.write(90);

    delay(1000);
    s1.write(0);

    delay(1000);
    s1.write(90);

    delay(1000);
    s1.write(180);

    delay(1000);
    s1.write(90);



    delay(1000);
    s2.write(90);

    delay(1000);
    s2.write(70);

    delay(1000);
    s2.write(90);

    delay(1000);
    s2.write(110);

    delay(1000);
    s2.write(90);
}

/********************************** end init functions **************************************/

/**************************** begin DCS BIOS event handlers *********************************/

void onSaiBankChange(unsigned int newValue) {
    int servoPos = max(0, min(180, newValue * scalingFactor - 90)); // range of motion of 0 - 180 degrees
    s1.write(servoPos);
}
DcsBios::IntegerBuffer saiBankBuffer(0x74d6, 0xffff, 0, onSaiBankChange);

void onSaiPitchChange(unsigned int newValue) {
    int servoPos = max(70, min(110, newValue * scalingFactor - 90)); // range of motion of 70 - 110 degrees
    s2.write(servoPos);
}
DcsBios::IntegerBuffer saiPitchBuffer(0x74d4, 0xffff, 0, onSaiPitchChange);




/***************************** end DCS BIOS event handlers **********************************/
