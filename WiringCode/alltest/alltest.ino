#include <Wire.h>
#include <LiquidCrystal_I2C.h> 
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display.  
// If 0x27 doesn't work, try 0x3F.



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);           
lcd.init();
lcd.backlight();
lcd.print("hello world");
//pinMode(3, INPUT);
pinMode(5, INPUT);
pinMode(6, OUTPUT);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(10, OUTPUT);
pinMode(11, OUTPUT);
pinMode(12, OUTPUT);
pinMode(13, OUTPUT);
/*digitalWrite(7, HIGH);
digitalWrite(8, HIGH);
digitalWrite(9, HIGH);
digitalWrite(10, HIGH);
digitalWrite(11, HIGH);
digitalWrite(12, HIGH);
digitalWrite(13, HIGH);
*/
  pinMode(3, INPUT_PULLUP);
 // pinMode(4, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(3), on, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
//Serial.print("potreading: ");
//Serial.println(analogRead(0));
//Serial.print("pidswitch: ");
//Serial.println(digitalRead(3));
//Serial.println("");
digitalWrite(6, HIGH); 

delay(1000);

//analogWrite(6, 0);
delay(1000);

}
void on()
{
  Serial.println("awklfskjdgfasklgfasjkfhgs");
}
