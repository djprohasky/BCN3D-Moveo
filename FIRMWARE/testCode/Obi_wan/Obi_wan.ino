#include <Stepper.h>
#include <Servo.h>

// initialise servo library
Servo myServo0;
Servo myServo1;
int pos = 90;

const int stepsPerRevolution = 200 * 16;  // change this to fit the number of steps per revolution
int rpm = 18;
float res = 0.1;


// initialise the stepper library:
Stepper myStepper0(stepsPerRevolution, 2, 3);
Stepper myStepper1(stepsPerRevolution, 4, 5);
Stepper myStepper2(stepsPerRevolution, 6, 7);
Stepper myStepper3(stepsPerRevolution, A0, A1);
Stepper myStepper4(stepsPerRevolution, A2, A3);

// read serial
String cs;

// initialise haptics
int pressure0 = 0, pressure1 = 0; // claw
bool lim2_trig = 0;
int lim2_pin = 12;

void setup() {
  pinMode(lim2_pin, INPUT_PULLUP);

  myServo0.attach(8);
  myServo1.attach(9);

  // set the speed at 60 rpm:
  myStepper0.setSpeed(rpm / 2);
  myStepper1.setSpeed(rpm * 14);
  myStepper2.setSpeed(rpm * 14);
  myStepper3.setSpeed(rpm * 14 / 5);
  myStepper4.setSpeed(rpm);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {

  // sensors
  CLAW_pressure();

  if (Serial.available() > 0) {
    cs = Serial.readString();
    Serial.println(cs);
    if (cs.charAt(0) == 'G') {
      switch (cs.charAt(1)) {
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
        case 's':
          CLAW(1);
          break;
        case 'z':
          CLAW(0);
          break;
        case 'w':
          CLAW_wc(1);
          break;
        case 'n':
          res = .25;
          break;
        case 'h':
          res = .1;
          break;
      }
    }
  }
}


void CLAW_pressure() {
  pressure0 = analogRead(A7);
  Serial.print("pressure0: ");
  Serial.print(pressure0);
  pressure1 = analogRead(A6);
  Serial.print("\t pressure1: ");
  Serial.print(pressure1);
  if (pressure0 < 380 && pressure1 < 580) {
    Serial.println(" fully engaged");
  }
  else if (pressure0 < 400 && pressure1 < 600) {
    Serial.println(" partially engaged");
  }
  else Serial.println(" disengaged");
}

void CLAW(boolean isClose) {
  if (isClose) {
    for (int pos = 20; pos <= 140; pos++) {
      myServo0.write(pos);
      myServo1.write(pos);
      delay(15);
    }
  }
  else {
    for (int pos = 140; pos >= 20; pos--) {
      myServo0.write(pos);
      myServo1.write(pos);
      delay(15);
    }
  }
}


void CLAW_wc(boolean isClose) {
  if (isClose) {
    for (int pos = 20; pos <= 115; pos++) {
      myServo0.write(pos);
      myServo1.write(pos);
      delay(15);
    }
  }
  else {
    for (int pos = 100; pos >= 20; pos--) {
      myServo0.write(pos);
      myServo1.write(pos);
      delay(15);
    }
  }
}

void CW(int ID) {
  // step one revolution  in one direction:
  Serial.print("clockwise: ");
  switch (ID) {
    case 0:
      Serial.println("J0");
      for (int i = 0; i < stepsPerRevolution * res; i++) {
        myStepper0.step(1);
      }
      break;
    case 1:
      Serial.println("J1");
      for (int j = 0; j < 14; j++) {
        for (int i = 0; i < stepsPerRevolution * res; i++) {
          myStepper1.step(1);
        }
      }
      break;
    case 2:
      Serial.println("J2");
      for (int j = 0; j < 14; j++) {
        for (int i = 0; i < stepsPerRevolution * res; i++) {
          myStepper2.step(1);
          lim2_trig = digitalRead(lim2_pin);
          if (i % stepsPerRevolution == 0) {
            Serial.print("lim2_trig: ");
            Serial.println(lim2_trig);
          }
          if (!lim2_trig) {
            myStepper2.step(-stepsPerRevolution);
            break;
          }
          if (!lim2_trig) break;
        }
        if (!lim2_trig) break;
      }
      break;
    case 3:
      Serial.println("J3");
      for (int j = 0; j < 14 / 5; j++) {
        for (int i = 0; i < stepsPerRevolution * res; i++) {
          myStepper3.step(1);
        }
      }
      break;
    case 4:
      Serial.println("J4");
      for (int i = 0; i < stepsPerRevolution * res; i++) {
        myStepper4.step(1);
      }
      break;
  }


}

void CCW(int ID) {
  Serial.print("counterclockwise: ");
  switch (ID) {
    case 0:
      Serial.println("J0");
      for (int i = 0; i < stepsPerRevolution * res; i++) {
        myStepper0.step(-1);
      }
      break;
    case 1:
      Serial.println("J1");
      for (int j = 0; j < 14; j++) {
        for (int i = 0; i < stepsPerRevolution * res; i++) {
          myStepper1.step(-1);
        }
      }
      break;
    case 2:
      Serial.println("J2");
      for (int j = 0; j < 14; j++) {
        for (int i = 0; i < stepsPerRevolution * res; i++) {
          myStepper2.step(-1);
          lim2_trig = digitalRead(lim2_pin);
          if (i % stepsPerRevolution == 0) {
            Serial.print("lim2_trig: ");
            Serial.println(lim2_trig);
          }
          if (!lim2_trig) {
            myStepper2.step(stepsPerRevolution);
            break;
          }
          if (!lim2_trig) break;
        }
        if (!lim2_trig) break;
      }
      break;
    case 3:
      Serial.println("J3");
      for (int j = 0; j < 14/5; j++) {
        for (int i = 0; i < stepsPerRevolution * res; i++) {
          myStepper3.step(-1);
        }
      }
      break;
    case 4:
      Serial.println("J4");
      for (int i = 0; i < stepsPerRevolution * res; i++) {
        myStepper4.step(-1);
      }
      break;
  }
}
















