//PIDBox.ino
//Alden Dent


#include "Arduino.h"
#include <LCD.h>
#include <LiquidCrystal_I2C/h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7)

// motor control variables
const int interruptPin = 3
const int motorPin = 6
int actualspeed;
int setPoint;


// user control pins
const int pidSwitch = 5
const int potPin = X //Analog pin, add later

//LED indicator pins
const int pidLed = 7
const int pwrLed = 8
const int ledBlink = 9
const int led1 = 10
const int led2 = 11
const int led3 = 12
const int led4 = 13
void setup()
{
	lcd.begin(16, 2); // for 16 x 2 LCD module
	lcd.setBacklightPin(3, POSITIVE);
	lcd.setBacklight(HIGH);

	pinMode(motorPin, OUTPUT);
	pinMode(pidSwitch, INPUT);
	pinMode(pidLed, OUTPUT);
	pinMode(pwrLed, OUTPUT);
	pinMode(led1, OUTPUT);
	pinMode(led2, OUTPUT);
	pinMode(led3, OUTPUT);
	pinMode(led4, OUTPUT);
}

void loop()
{
}
