/*
 myhub.lk
 
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
*/
int buzzer = 5;

int trigPin = A2;    //Trig - green Jumper
int echoPin = A5;    //Echo - yellow Jumper
long duration, cm, inches;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(50);
}

void loop()
{


  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = (duration / 2) / 29.1;
  inches = (duration / 2) / 74;

  Serial.print(cm);
  Serial.print("cm, ");

  Serial.print(inches);
  Serial.print("inches");
  Serial.println();






  if (cm < 30) {
    //tone(buzzer, (30 - cm) * 300, 100);
    digitalWrite(5,HIGH);
  }
  // delay(50);
}


