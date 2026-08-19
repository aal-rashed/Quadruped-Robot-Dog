#include <Servo.h>

// ---- Servo Objects ----
Servo frontLeft;
Servo frontRight;
Servo backLeft;
Servo backRight;

// ---- Servo Pins ----
int FL = 3;
int FR = 5;
int BL = 6;
int BR = 9;

// ---- Ultrasonic Sensor ----
int trigPin = 10;
int echoPin = 11;

// ---- Your Offsets ----
int offsetFL = 0;
int offsetFR = 180;
int offsetBL = 180;
int offsetBR = 0;

// ---- Movement Settings ----
int stepDelay = 250;

// ---- Distance Function ----
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

// ---- Smart Movement (auto‑reverse based on offset) ----
void liftLeg(Servo &leg, int offset) {
  if (offset == 180) leg.write(offset + 25);   // reverse direction
  else leg.write(offset - 25);
}

void dropLeg(Servo &leg, int offset) {
  leg.write(offset);
}

void pushForward(Servo &leg, int offset) {
  if (offset == 180) leg.write(offset - 30);   // reverse direction
  else leg.write(offset + 30);
}

void pullBack(Servo &leg, int offset) {
  if (offset == 180) leg.write(offset + 30);   // reverse direction
  else leg.write(offset - 30);
}

// ---- Walking Sequence ----
void stepForward() {
  // Step 1: FL + BR
  liftLeg(frontLeft, offsetFL);
  liftLeg(backRight, offsetBR);
  pushForward(frontLeft, offsetFL);
  pushForward(backRight, offsetBR);
  delay(stepDelay);

  dropLeg(frontLeft, offsetFL);
  dropLeg(backRight, offsetBR);

  // Step 2: FR + BL
  liftLeg(frontRight, offsetFR);
  liftLeg(backLeft, offsetBL);
  pushForward(frontRight, offsetFR);
  pushForward(backLeft, offsetBL);
  delay(stepDelay);

  dropLeg(frontRight, offsetFR);
  dropLeg(backLeft, offsetBL);
}

// ---- Setup ----
void setup() {
  Serial.begin(9600);

  frontLeft.attach(FL);
  frontRight.attach(FR);
  backLeft.attach(BL);
  backRight.attach(BR);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  frontLeft.write(offsetFL);
  frontRight.write(offsetFR);
  backLeft.write(offsetBL);
  backRight.write(offsetBR);

  delay(1000);
}

// ---- Main Loop ----
void loop() {
  long distance = getDistance();
  Serial.println(distance);

  if (distance < 15) {
    frontLeft.write(offsetFL);
    frontRight.write(offsetFR);
    backLeft.write(offsetBL);
    backRight.write(offsetBR);
    delay(300);
  } else {
    stepForward();
  }
}
