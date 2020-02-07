#include <LiquidCrystal_I2C.h>

//PIDBox.ino
//Alden Dent



#include <Wire.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display.
// If 0x27 doesn't work, try 0x3F.

// rpm varibles
volatile int interruptCount = 0;
const int rpmCalcDelay = 200;  //Delay between calculations of rpm
long oldmillis = 0;

// motor control variables
const int interruptPin = 3;
const int motorPin = 6;
int actualSpeed = 0;
int setPoint = 0;
int motorPower = 0;
int error;
int adjustment; //proportional control adjustment

double kp = 8; //PID constant
double ki = .005; //PID constant
double kd = 7; //PID constant
int oldError, Actual;
float Derivative, Drive, Integral;

// user control pins
const int modeSwitch = 5;
const int potPin = A0; //Analog
int initialized = 0;

//LED indicator pins
const int pidLed = 7; //Power indacator pin
const int pwrLed = 8;  //Mode indacator pin
const int ledBlink = 9; //Blinking led pin
const int led1 = 10;  //Speed led pins
const int led2 = 11;
const int led3 = 12;
const int led4 = 13;
bool ledblink = false;  //Blinking led state
int ledStartupDelay = 70; //Delay between blinks in initializing led show



void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();
  pinMode(motorPin, OUTPUT);
  pinMode(modeSwitch, INPUT);
  pinMode(pidLed, OUTPUT);
  pinMode(pwrLed, OUTPUT);
  digitalWrite(pwrLed, HIGH);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(ledBlink, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), count, CHANGE);
  initialized = digitalRead(modeSwitch);
  //initSequence();
  
}




void loop()
{
  
  //setPoint = map(analogRead(potPin), 0, 1023, 0, 100);
  setPoint = map(analogRead(potPin), 0, 1023, 0, 255);
  lcd.setCursor(0, 0);
  lcd.print("Setpoint: ");
  lcd.print(setPoint);
  lcd.print("       ");
  lcd.setCursor(0, 1);
  lcd.print("Speed: ");
  lcd.print(actualSpeed);
  setLeds();
  
  if(motorPower > 255){ //ensures that the power isn't above 255
    motorPower = 255;
  }
  if(motorPower < 0){ //ensures that the power isn't below 0
    motorPower = 0;
  }

  //analogWrite(motorPin, motorPower);
  analogWrite(motorPin, setPoint);
     
  if (millis() >= oldmillis + rpmCalcDelay) {
    detachInterrupt(digitalPinToInterrupt(interruptPin));
    actualSpeed = calcRPM(); //map(calcRPM(), 0, 45, 0, 100);
    attachInterrupt(digitalPinToInterrupt(interruptPin), count, CHANGE);
    interruptCount = 0;
    oldmillis = millis();
  }

  //No PID loop
  if (digitalRead(modeSwitch) == LOW) {
    if (initialized == 0) {
      digitalWrite(pidLed, LOW);
      lcd.setCursor(0, 0);
      lcd.print("PID OFF                       ");
      initialized = 1;
      delay(500);
    }
    error = setPoint - actualSpeed;
    adjustment = map(error, -100, 100, -10, 10);
    motorPower = motorPower + adjustment;
  }


  else  {
    //PID loop
    if (initialized == 1) {
      digitalWrite(pidLed, HIGH);
      lcd.setCursor(0, 0);
      lcd.print("PID ON                     ");
      initialized = 0;
      delay(500);
    }
    
   error = setPoint-actualSpeed;
   Integral = Integral + (error*rpmCalcDelay);
   Derivative = (error - oldError)/rpmCalcDelay;
   motorPower = (error*kp) + (Integral*ki) + (Derivative*kd);
   oldError = error;
   delay(rpmCalcDelay);
   
  }
  
}

void count()
{
  interruptCount = interruptCount + 1;
  ledblink = !ledblink;
  digitalWrite(ledBlink, ledblink);
}


int calcRPM()
  {
  int rpm;
	rpm = interruptCount *(60000/rpmCalcDelay) / 12;
  return rpm;
  }

void setLeds()
  {   //Try making with switch case
  if(actualSpeed > 0){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);  
  }

  if(actualSpeed > 25){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);  
  }
    
  if(actualSpeed > 75){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, LOW);  
  }
    
  if(actualSpeed > 100){
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);    
  }
}






















void initSequence() {
  lcd.print("Alden  Dent");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("PID Box");
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
    delay(150);
  digitalWrite(ledBlink, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  delay(140);
  digitalWrite(ledBlink, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
    delay(130);
  digitalWrite(ledBlink, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  delay(120);
  digitalWrite(ledBlink, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
      delay(110);
  digitalWrite(ledBlink, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  delay(100);
  digitalWrite(ledBlink, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
    delay(90);
  digitalWrite(ledBlink, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  delay(80);
  digitalWrite(ledBlink, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(1000);
  lcd.clear();
  delay(1000);
}
