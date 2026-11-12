#include <Servo.h>

const int TRIG_PIN   = 7;
const int ECHO_PIN   = 6;
const int SERVO_PIN  = 5;

Servo myServo;
const int DISTANCE_THRESHOLD = 20; 
long duration;
int distance;
const int angles[] = {0, 90, 180};  

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  myServo.attach(SERVO_PIN);
  myServo.write(90); 
  
  randomSeed(analogRead(A0));
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  if (distance > 0 && distance <= DISTANCE_THRESHOLD) {
    
    
    int randomIndex = random(0, 3); 
    int targetAngle = angles[randomIndex];
    
    myServo.write(targetAngle);
    delay(300); 
    
   
  }
  
  delay(100);
}