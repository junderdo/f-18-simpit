#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27, if new version please use 0x3F instead.

void setup()
{
  lcd.init();  //initialize the lcd
  lcd.backlight();  //open the backlight
}

void loop()
{
  lcd.setCursor(0, 0); // set the cursor to column 3, line 0
  lcd.print("01234567");  // Print a message to the LCD
  lcd.print("8");

  // TODO: 
}
