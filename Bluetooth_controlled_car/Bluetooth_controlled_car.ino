/* 
 *  Bluetooth_controlled_car by George Raveen 
 *  https://www.youtube.com/watch?v=BJFTK6K5j9s&t=20s
 *  www.georgeraveen.blogspot.com
 *  georgeraveen@gmail.com
*/





// 
const int mep = 4; //move enabling pin
const int bwp = 12; //backward pin

//
const int wap = A1; //wheel alignment pin
//
const int rxp = 0; //receiver pin
const int txp = 1; //transmitter pin


int wai; //wheel alignment indicator
int state;
int sst=1; //steering status 012 LMR
//


#include <Stepper.h>

const int stepsPerRevolution = 160;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);



void setup() {
  // put your setup code here, to run once:

pinMode(bwp,OUTPUT);
pinMode(wap,INPUT);
pinMode(mep,OUTPUT);
pinMode(13,OUTPUT);
//
  // set the speed at 60 rpm:
  myStepper.setSpeed(150);
  
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  
      
while(Serial.available())
  {
    state =Serial.read();//store string from serial command
  }

   if(!Serial.available()){     
        
          // Forward
    if (state == 'F') {
      state ='S';
      digitalWrite(mep,HIGH);
      digitalWrite(bwp,LOW);
      delay(200);
      
      }
      //backward
    else if (state == 'B'){
      state ='S';
      digitalWrite(mep,HIGH);
      digitalWrite(bwp,HIGH);
      delay(200);
      
      }
      //stop
    else if (state == 'S'){
      state ='S';
      digitalWrite(mep,LOW);
      digitalWrite(bwp,LOW);
      
      if(sst==0){
        myStepper.step(-stepsPerRevolution/2);
        sst = 1;        
        }
      else if(sst==2){
        myStepper.step(stepsPerRevolution/2);
        sst = 1;        
        }  
      }  
    //forward left
    else if (state == 'I'){
      state ='S';

      if(sst==1){
        digitalWrite(mep,LOW);
        digitalWrite(bwp,LOW);
        myStepper.step(stepsPerRevolution/2);
        sst = 0;
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,LOW);
      }
      else if(sst==0){ 
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,LOW);
      }
      delay(200);
       
    }
    //forward Right
    else if (state == 'G'){
      state ='S';

      if(sst==1){
        digitalWrite(mep,LOW);
        digitalWrite(bwp,LOW);
        myStepper.step(-stepsPerRevolution/2);
        sst = 2;
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,LOW);
      }
      else if(sst==2){ 
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,LOW);
      }
      delay(200);
       
    }

    //backward left
    else if (state == 'J'){
      state ='S';

      if(sst==1){
        digitalWrite(mep,LOW);
        digitalWrite(bwp,LOW);
        myStepper.step(stepsPerRevolution/2);
        sst = 0;
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,HIGH);
      }
      else if(sst==0){ 
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,HIGH);
      }
      delay(200);
       
    }
    //backward Right
    else if (state == 'H'){
      state ='S';

      if(sst==1){
        digitalWrite(mep,LOW);
        digitalWrite(bwp,LOW);
        myStepper.step(-stepsPerRevolution/2);
        sst = 2;
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,HIGH);
      }
      else if(sst==2){ 
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,HIGH);
      }
      delay(200);
       
    }
    else if(state== 'X')
      {
       state ='S';
       digitalWrite(mep,LOW); //stop 
       digitalWrite(bwp,LOW);
       
       //alignment started
       for(int i=0; i<3; i++)
       { 
         // step one revolution  in one direction:
      //clockwise
      myStepper.step(stepsPerRevolution);
      delay(500);
      //counterclockwise
      myStepper.step(-stepsPerRevolution);
      delay(500);
       }
       //mid point
      myStepper.step(stepsPerRevolution/2);
      //alignment completed

      }    
    
      
   }      
}
