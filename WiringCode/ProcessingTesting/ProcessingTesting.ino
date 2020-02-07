

void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
}

void loop() {
  // send the value of analog input 0:
  Serial.println(map(analogRead(A0), 0, 1023, 0, 1000));
  // wait a bit for the analog-to-digital converter to stabilize after the last
  // reading:
  delay(2);
}
