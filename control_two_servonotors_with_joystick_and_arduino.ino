#include <Servo.h>

int ledPin = 13;

int xPin = A0;
int yPin = A1;
int buttonPin = 2;

int xVal;
int yVal;
int buttonState;

int xServoPin = 9;
int yServoPin = 10;

int xServoPos;
int yServoPos;

Servo xServo;
Servo yServo;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Attach servos to Arduino pins
  xServo.attach(xServoPin);
  yServo.attach(yServoPin);
}

void loop() {
  // Read joystick values
  xVal = analogRead(xPin);
  yVal = analogRead(yPin);
  buttonState = digitalRead(buttonPin);

  // Map joystick values to servo angles
  xServoPos = map(xVal, 0, 1023, 0, 180);
  yServoPos = map(yVal, 0, 1023, 0, 180);

  // Move servos
  xServo.write(xServoPos);
  yServo.write(yServoPos);

  // Turn LED on when button is pressed
  if (buttonState == LOW) {
    digitalWrite(ledPin, HIGH);
  }

  // Turn LED off when button is not pressed
  if (buttonState == HIGH) {
    digitalWrite(ledPin, LOW);
  }
}