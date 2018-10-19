
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

const int stepsPerRevolution = 200 * 16; // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, A0, A1);

// read serial
char c;

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(80);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    c = Serial.read();
    Serial.println(c);
    if (c == '0') CW();
    if (c == '1') CCW();
  }
}

void CW() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
}

void CCW() {
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
}
