/*
  Sketch 1.2.1
  Control LED by Arduino

  modified 2018/5/02
  by http://www.thingerbits.com and www.arduino.lk
*/

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output
  pinMode(13, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}