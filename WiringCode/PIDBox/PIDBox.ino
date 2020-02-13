//PIDBox.ino
//Alden Dent
//Main PID Box Code

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display.
// If 0x27 doesn't work, try 0x3F.

// rpm varibles
volatile int interruptCount = 0;  //How many times the wheel passes throught the interrupter
const int rpmCalcDelay = 166;  //Delay between calculations of rpm
long oldmillis = 0; //Old time value so the timer works

// motor control variables
const int interruptPin = 3;
const int motorPin = 6;
int actualSpeed = 0;  //Speed in RPM mapped from 0-100
int setPoint = 0; //How fast you want it to go
int motorPower = 0; //The amout of power sent to the motor
int error;  //Difference between set and actual speed
int adjustment; //proportional control adjustment

//PID variables
double kP = 6; //PID constant
double kI = .01; //PID constant
double kD = 0.0000; //PID constant
int oldError; //Previous error, used to find
float Derivative, Drive, Integral;  //PID values

// user control pins
const int modeSwitch = 5;
const int potPin = A0; //Speed potentiometer pin
int initialized = 0;  //Makes it so the message for control type ony appears once

//LED indicator pins
const int pidLed = 7; //Power indacator pin
const int pwrLed = 8;  //Mode indacator pin
const int ledBlink = 9; //Blinking led pin
const int led1 = 10;  //Speed led pin
const int led2 = 11;  //Speed led pin
const int led3 = 12;  //Speed led pin
const int led4 = 13;  //Speed led pin
bool ledblink = false;  //Blinking led state
int ledStartupDelay = 70; //Delay between blinks in initializing led show



void setup()
{
  Serial.begin(9600);

  lcd.init();   //Setup for LCD
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();

  pinMode(motorPin, OUTPUT);  //Sets modes for all pins
  pinMode(modeSwitch, INPUT);
  pinMode(pidLed, OUTPUT);
  pinMode(pwrLed, OUTPUT);
  digitalWrite(pwrLed, HIGH);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(ledBlink, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);  //Make sure you use INPUT_PULLUP for the interrupt pin

  attachInterrupt(digitalPinToInterrupt(interruptPin), count, CHANGE);
  initialized = digitalRead(modeSwitch);  //Makes sure it knows which mode it is in
  initSequence(); //Fancy leds

}




void loop()
{

  setPoint = map(analogRead(potPin), 0, 1023, 0, 100);  //Sets setPoint to mapped potentiometer value

  lcd.setCursor(0, 0);
  lcd.print("Setpoint: ");
  lcd.print(setPoint);
  lcd.print("       "); //Extra space so no messages overlap
  lcd.setCursor(0, 1);
  lcd.print("Speed: ");
  lcd.print(actualSpeed);
  lcd.print("       "); //Extra space so no messages overlap
  setLeds();  //Sets LEDs that show speed




  if (millis() >= oldmillis + rpmCalcDelay) {
    detachInterrupt(digitalPinToInterrupt(interruptPin)); //Detaches the interrupt so it doesn't mess up the math
    actualSpeed = map(calcRPM(), 0, 5000, 0, 100);  //Maps rpm from 0 to 100

    //No PID loop
    if (digitalRead(modeSwitch) == LOW) {
      if (initialized == 0) { //Initialization sequence
        digitalWrite(pidLed, LOW);  //LED shows which mode
        lcd.clear();
        lcd.print("PID OFF                       ");  //LCD prints the mode
        initialized = 1;  //Switches so it only initializes once
        delay(800); //Delay so user can read the message
      }

      analogWrite(motorPin, map(analogRead(potPin), 0, 1023, 0, 248)); //Sets motor power to a mapped potentiometer value

    }


    else  {
      //PID loop
      if (initialized == 1) { //Initialization sequence
        digitalWrite(pidLed, HIGH); //LED shows which mode
        lcd.clear();
        lcd.print("PID ON                     ");  //LCD prints the mode
        initialized = 0;  //Switches so it only initializes once
        delay(800); //Delay so user can read the message
      }

      error = setPoint - actualSpeed; //PID math
      Integral = Integral + (error * rpmCalcDelay); //PID math
      Derivative = (error - oldError) / rpmCalcDelay; //PID math
      motorPower = (error * kP) + (Integral * kI) + (Derivative * kD);  //PID math
      oldError = error;

      analogWrite(motorPin, constrain(motorPower + map(analogRead(potPin), 0, 1023, 0, 150), 0, 255));  //Sets motor power to PID correction power

    }
    interruptCount = 0; //Resets interrupt counter
    oldmillis = millis(); //Resets the timer

    Serial.print(setPoint); //Shows setpoint and speed as two lines on serial plotter
    Serial.print(",");  //Shows setpoint and speed as two lines on serial plotter
    Serial.println(actualSpeed);  //Shows setpoint and speed as two lines on serial plotter

    attachInterrupt(digitalPinToInterrupt(interruptPin), count, CHANGE);  //Reattaches the interrupt
  }

}

void count()  //Interrupt loop
{
  interruptCount = interruptCount + 1;  //Adds one to interrupt count
  ledblink = !ledblink; //Switches the state of the blinking led
  digitalWrite(ledBlink, ledblink); //Turns led on or off
}


int calcRPM()
{
  int rpm;
  rpm = interruptCount * (60000 / rpmCalcDelay) / 12; //Calculates rpm, interrupts times calculations per second divided by the number of interrupts per rotation
  return rpm;
}

void setLeds()  //Sets speed LEDs
{
  if (actualSpeed > 0) {  //If speed 1-24 one LED is on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }

  if (actualSpeed > 25) { //If speed is 25-49 two LEDs are on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }

  if (actualSpeed > 50) { //If speed is 50-74 three LEDs are on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  }

  if (actualSpeed > 75) { //If speed is above 75 all four LEDs are on
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  }
  if (actualSpeed == 0) { //If speed is 0 no LEDs are on
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  }
}


void initSequence() { //Types out my name and PID box and does fancy LED stuff
  lcd.print("A");
  delay(50);
  lcd.print("l");
  delay(50);
  lcd.print("d");
  delay(50);
  lcd.print("e");
  delay(50);
  lcd.print("n");
  delay(50);
  lcd.print("  ");
  lcd.print("D");
  delay(50);
  lcd.print("e");
  delay(50);
  lcd.print("n");
  delay(50);
  lcd.print("t");
  lcd.setCursor(0, 1);  //Puts the cursor on the next line
  lcd.print("P");
  delay(50);
  lcd.print("I");
  delay(50);
  lcd.print("D");
  delay(50);
  lcd.print("  B");
  delay(50);
  lcd.print("o");
  delay(50);
  lcd.print("x");
  digitalWrite(ledBlink, HIGH); //Turns LEDs on and off in pretty patterns
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
  delay(300);
  digitalWrite(ledBlink, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(300);
  digitalWrite(ledBlink, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  delay(300);
  digitalWrite(ledBlink, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(1000);
  lcd.clear();
  delay(1000);
}
