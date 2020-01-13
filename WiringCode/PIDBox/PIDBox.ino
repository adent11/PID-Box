#include <LiquidCrystal_I2C.h>

//PIDBox.ino
//Alden Dent



#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display.
// If 0x27 doesn't work, try 0x3F.

// rpm varibles

volatile int interruptCount;
const int rpsCalcDelay = 200;
const int oldmillis = 0;

// motor control variables
const int interruptPin = 3;
const int motorPin = 6;
int actualspeed;
int setPoint;

// user control pins
const int pidSwitch = 5;
const int potPin = 1; //Analog pin, add later
int initialized = 0;


//LED indicator pins
const int pidLed = 7;
const int pwrLed = 8;
const int ledBlink = 9;
const int led1 = 10;
const int led2 = 11;
const int led3 = 12;
const int led4 = 13;
bool ledblink = false;
int ledStartupDelay = 70;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(motorPin, OUTPUT);
  pinMode(pidSwitch, INPUT);
  pinMode(pidLed, OUTPUT);
  pinMode(pwrLed, OUTPUT);
  digitalWrite(pwrLed, HIGH);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), count, CHANGE);
  initSequence();
}

void loop()
{

  //No PID loop
  if (digitalRead(pidSwitch) == LOW) {
    if (initialized == 0) {
      digitalWrite(pidLed, LOW);
      lcd.setCursor(0, 0);
      lcd.print("PID OFF                       ");
      initialized = 1;
      delay(100);
    }
    if (millis() == oldmillis + rpsCalcDelay) {
      // motor correction
    }

  }


  else  {
    //PID loop
    if (initialized == 1) {
      digitalWrite(pidLed, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("PID ON                     ");
      initialized = 0;
      delay(100);
    }
    if (millis() == oldmillis + rpsCalcDelay) {
      // pid code
    }
  }
  /*if(millis() >= oldmillis+rpsCalcDelay){
    detachInterrupt(digitalPinToInterrupt(interruptPin), count, CHANGE);
    //PID CODE GOES HERE
    //calcRPS()
    }*/

}

void count()
{
  interruptCount = interruptCount + 1;
  //ledblink = !ledblink;
}

void initSequence() {
  digitalWrite(ledBlink, HIGH);
  digitalWrite(led1, HIGH);
  delay(ledStartupDelay);
  digitalWrite(ledBlink, LOW);
  digitalWrite(led2, HIGH);
  delay(ledStartupDelay);
  digitalWrite(led1, LOW);
  digitalWrite(led3, HIGH);
  delay(ledStartupDelay);
  digitalWrite(led2, LOW);
  digitalWrite(led4, HIGH);
  delay(ledStartupDelay);
  digitalWrite(led3, LOW);
  delay(ledStartupDelay);
  digitalWrite(led4, LOW);
  delay(ledStartupDelay);
  digitalWrite(ledBlink, HIGH);
  digitalWrite(led1, HIGH);
  delay(ledStartupDelay);
  digitalWrite(ledBlink, LOW);
  digitalWrite(led2, HIGH);
  delay(ledStartupDelay);
  digitalWrite(led1, LOW);
  digitalWrite(led3, HIGH);
  delay(ledStartupDelay);
  digitalWrite(led2, LOW);
  digitalWrite(led4, HIGH);
  delay(ledStartupDelay);
  digitalWrite(led3, LOW);
  delay(ledStartupDelay);
  digitalWrite(led4, LOW);
  delay(ledStartupDelay);
  digitalWrite(ledBlink, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  delay(500);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(500);
}

/*int calcRPS(interruptCount)
  {
	rps = interruptCount*(1/rpsCalcDelay);
	attachInterrupt(digitalPinToInterrupt(interruptPin), count, CHANGE);
  return rps;
  }*/
