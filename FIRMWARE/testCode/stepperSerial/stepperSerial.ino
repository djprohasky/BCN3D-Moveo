/*
  Stepper Motor Control - one revolution
 
 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.
 
 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.
 
 
 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe
 
 */

#include <Stepper.h>
#include <Servo.h>

Servo myServo0;
Servo myServo1;
int pos = 90;

const int stepsPerRevolution = 200 * 16;  // change this to fit the number of steps per revolution
int rpm = 18;
float res = 0.1;
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper0(stepsPerRevolution, 2, 3);
Stepper myStepper1(stepsPerRevolution, 4, 5);
Stepper myStepper2(stepsPerRevolution, 6, 7);
Stepper myStepper3(stepsPerRevolution, A0, A1);
Stepper myStepper4(stepsPerRevolution, A2, A3);

// read serial
String cs;

void setup() {

  myServo0.attach(8);
  myServo1.attach(9);

  // set the speed at 60 rpm:
  myStepper0.setSpeed(rpm);
  myStepper1.setSpeed(rpm*14);
  myStepper2.setSpeed(rpm*14);
  myStepper3.setSpeed(rpm*14/5);
  myStepper4.setSpeed(rpm);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0) {
    cs = Serial.readString();
    Serial.println(cs);
    if(cs.charAt(0)=='G'){
      switch (cs.charAt(1)){
      case '0':
        CW(0);
        break;
      case '1':
        CCW(0);
        break;
      case '2':
        CW(1);
        break;
      case '3':
        CCW(1);
        break;
      case '4':
        CW(2);
        break;
      case '5':
        CCW(2);
        break;
      case '6':
        CW(3);
        break;
      case '7':
        CCW(3);
        break;
      case '8':
        CW(4);
        break;
      case '9':
        CCW(4);
        break;
      case 'a':
        CLAW(1);
        break;
      case 's':
        CLAW(0);
        break;
      case 'n':
        res = 1;
        break;
      case 'h':
        res = .1;
        break;
      }
    }
  }
}


void CLAW(boolean isClose){
  if (isClose){
    for(int pos = 50; pos <= 140; pos++){
      myServo0.write(pos);
      myServo1.write(pos);
      delay(15);
    }
  }
  else{
    for(int pos = 140; pos >= 50; pos--){
      myServo0.write(pos);
      myServo1.write(pos);
      delay(15);
    }
  }
}


void CW(int ID) {
  // step one revolution  in one direction:
  Serial.print("clockwise: ");
  switch(ID){
  case 0:
    Serial.println("J0"); 
    myStepper0.step(stepsPerRevolution*res);
    break;
  case 1:
    Serial.println("J1");
    for(int i=0; i < 14; i++){
      myStepper1.step(stepsPerRevolution*res);
    }
    break;
  case 2:
    Serial.println("J2");
    for(int i=0; i < 14; i++){
      myStepper2.step(stepsPerRevolution*res);
    }
    break;
  case 3:
    Serial.println("J3");
    for(int i=0; i < 14; i++){
      myStepper3.step(stepsPerRevolution*res);
    }
    break;
  case 4:
    Serial.println("J4");
    for(int i=0; i < 1; i++){
      myStepper4.step(stepsPerRevolution*res);
    }
    break;
  }


}

void CCW(int ID) {
  Serial.print("counterclockwise: ");
  switch(ID){
  case 0:
    Serial.println("J0");  
    myStepper0.step(-stepsPerRevolution*res);
    break;
  case 1:
    Serial.println("J1");  
    for(int i=0; i < 14; i++){
      myStepper1.step(-stepsPerRevolution*res);
    }
    break;
  case 2:
    Serial.println("J2");  
    for(int i=0; i < 14; i++){
      myStepper2.step(-stepsPerRevolution*res);
    }
    break;
  case 3:
    Serial.println("J3");  
    for(int i=0; i < 14; i++){
      myStepper3.step(-stepsPerRevolution*res);
    }
    break;
  case 4:
    Serial.println("J4");  
    for(int i=0; i < 1; i++){
      myStepper4.step(-stepsPerRevolution*res);
    }
    break;
  }
}












