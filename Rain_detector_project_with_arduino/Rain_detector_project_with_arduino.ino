const int rainSensor = 2;
const int ledPin = 7;
const int buzzerPin = 8;

void setup() {
  pinMode(rainSensor, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int rainState = digitalRead(rainSensor);

  // Most rain sensor modules output LOW when wet
  if (rainState == LOW) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Rain detected!");
  } 
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
    Serial.println("No rain");
  }

  delay(200);
}