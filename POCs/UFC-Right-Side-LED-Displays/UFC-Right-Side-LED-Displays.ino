/*
 Showing numbers, chars and phrases
   A
  ---
F |   | B
 | G |
  ---
E |   | C
 |   |
  ---
   D
*/
#define common_cathode 0
#define common_anode 1
bool mode = common_cathode;// my display is common anode
#define pinA 2
#define pinB 3
#define pinC 4
#define pinD 5
#define pinE 7
#define pinF 12
#define pinG 8
#define pinDP 13
#define D1 6
#define D2 9
#define D3 10
#define D4 11
#include "array.h"
#include "functions.h"
void setup() {                
 // initialize the digital pins as outputs.
 pinMode(pinA, OUTPUT);     
 pinMode(pinB, OUTPUT);     
 pinMode(pinC, OUTPUT);     
 pinMode(pinD, OUTPUT);     
 pinMode(pinE, OUTPUT);     
 pinMode(pinF, OUTPUT);     
 pinMode(pinG, OUTPUT); 
 pinMode(pinDP, OUTPUT);  
 pinMode(D1, OUTPUT);  
 pinMode(D2, OUTPUT);  
 pinMode(D3, OUTPUT);  
 pinMode(D4, OUTPUT); 
 Serial.begin(9600);
}
// the loop routine runs over and over again forever:
void loop() {
printDisplay("jeff",1000);// use this function to print a string (has numbers, characters or phrases) when the length of string is 4 or less than 4, the second variable is the time for printing on display
Reset();// use this function to reset the display
delay(1000);
printDisplay("this text should scroll",300);// when the length of string is more than 4, the second variable is custom speed for movement
delay(1000);
// printDigit('y',D1);//print any char on any digit
}
