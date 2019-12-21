/* 
 *  Bluetooth_controlled_crane_car by George Raveen 
 *  https://www.youtube.com/watch?v=1T6-KRvPzvc&t=1s
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

#include <Servo.h>
Servo servoR;
Servo servoA;  
Servo servoG;    
//
int srp = 90;
int sap = 90;
int sgp = 90;
//



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
    
    servoR.attach(5);
    servoA.attach(6);
    servoG.attach(7);
    
}

void loop() {
    // put your main code here, to run repeatedly:
    while(Serial.available())
    {
        state =Serial.read();//store string from serial command
    }
    // Forward
    if (state == 'w') {
        
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,LOW);
        delay(200);
        
    }
    //backward
    else if (state == 'x'){
        
        digitalWrite(mep,HIGH);
        digitalWrite(bwp,HIGH);
        delay(200);
        
    }
    //stop
    else if (state == 's'){
        
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
    //left
     else if (state == 'a'){
        
        
        if(sst==1){
            digitalWrite(mep,LOW);
            digitalWrite(bwp,LOW);
            myStepper.step(stepsPerRevolution/2);
            sst = 0;
        
        }
        delay(200); 
    }   
     //right
     else if (state == 'd'){
        
        
        if(sst==1){
            digitalWrite(mep,LOW);
            digitalWrite(bwp,LOW);
            myStepper.step(-stepsPerRevolution/2);
            sst = 2;
        
        }
        delay(200); 
    }      
    
    //forward left
    else if (state == 'q'){
        
        
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
    else if (state == 'e'){
        
        
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
    else if (state == 'z'){
        
        
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
    else if (state == 'c'){
        
        
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
    
    //manual rotation left
    else if(state=='R' && srp <= 150 )
    {
        servoR.write(srp);
        Serial.print("*o");
        Serial.print(srp);
        Serial.print("*o");
        srp+=2;
        delay(100);
    }
    //manual rotation Right
    else if(state=='r' && srp >= 30 )
    {
        servoR.write(srp);
        Serial.print("*o");
        Serial.print(srp);
        Serial.print("*o");
        srp -=2;
        delay(100);
    }
    //manual arm up
    else if(state=='T' && sap <= 150 )
    {
        servoA.write(sap);
        Serial.print("*k");
        Serial.print(sap);
        Serial.print("*k");
        sap+=2;
        delay(100);
    }
    //manual arm down
    else if(state=='t' && sap >= 40 )
    {
        servoA.write(sap);
        Serial.print("*k");
        Serial.print(sap);
        Serial.print("*k");
        sap -=2;
        delay(100);
    }
    //manual gripper close
    else if(state=='Y' && sgp <= 140 )
    {
        servoG.write(sgp);
        Serial.print("*m");
        Serial.print(sgp);
        Serial.print("*m");
        sgp+=2;
        delay(100);
    }
    //manual gripper open
    else if(state=='y' && sgp >= 30 )
    {
        servoG.write(sgp);
        Serial.print("*m");
        Serial.print(sgp);
        Serial.print("*m");
        sgp -=2;
        delay(100);
    }
    //auto arm up
    else if(state=='G'){
        while(sap<=150){
            servoA.write(sap);
            Serial.print("*k");
            Serial.print(sap);
            Serial.print("*k");
            sap+=2;
            delay(100);
        }
    }
    //auto arm down
    else if(state=='g'){
        while(sap>=40){
            servoA.write(sap);
            Serial.print("*k");
            Serial.print(sap);
            Serial.print("*k");
            sap -= 2;
            delay(100);
        }
    }
    //auto rotation left
    else if(state=='F'){
        while(srp<=150){
            servoR.write(srp);
            Serial.print("*o");
            Serial.print(srp);
            Serial.print("*o");
            srp+=2;
            delay(100);
        }
    }
    //auto rotaion right
    else if(state=='f'){
        while(srp>=30){
            servoR.write(srp);
            Serial.print("*o");
            Serial.print(srp);
            Serial.print("*o");
            srp -= 2;
            delay(100);
        }
    }    
    //auto rotaion mid
    else if(state=='v'){
        if(srp>90){              //left to mid
            while(srp>=90){
                servoR.write(srp);
                Serial.print("*o");
                Serial.print(srp);
                Serial.print("*o");
                srp -= 2;
                delay(100);
            }
            
        }
        else if(srp<90){              //right to mid
            while(srp<=90){
                servoR.write(srp);
                Serial.print("*o");
                Serial.print(srp);
                Serial.print("*o");
                srp += 2;
                delay(100);
            }
            
        }
    }        
    
    
    
    else if(state== 'u')
    {
        
        digitalWrite(mep,LOW); //stop 
        digitalWrite(bwp,LOW);
        
        //alignment started
        for(int i=0; i<2; i++)
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
