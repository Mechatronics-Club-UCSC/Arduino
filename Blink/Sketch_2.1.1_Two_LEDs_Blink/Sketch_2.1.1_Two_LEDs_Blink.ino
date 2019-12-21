/*
  Sketch 2.1.1
  Two LEDs Blink

  modified 2018/5/02
  by http://www.thingerbits.com and www.arduino.lk
*/

// set pin numbers:
int led1Pin = 4;            // the number of the LED1 pin
int led2Pin = 5;            // the number of the LED2 pin
int led3Pin = 6;

void setup() {
  // initialize the LED pin as an output:
  pinMode(led1Pin, OUTPUT);
  pinMode(led2Pin, OUTPUT);
}

void loop() {
  digitalWrite(led1Pin,HIGH);
  delay(2000);
  digitalWrite(led1Pin,LOW);
  delay(100);
  digitalWrite(led2Pin,HIGH);
  delay(1000);
  digitalWrite(led2Pin,LOW);
  delay(100);
  digitalWrite(led3Pin,HIGH);
  delay(5000);
  digitalWrite(led3Pin,LOW);
}

