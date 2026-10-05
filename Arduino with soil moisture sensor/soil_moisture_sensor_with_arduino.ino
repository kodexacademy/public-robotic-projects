// C++ code
int moisture = 0;

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);

  pinMode(8, OUTPUT);  // Green LED
  pinMode(10, OUTPUT); // Yellow LED
  pinMode(12, OUTPUT); // Red LED
}

void loop()
{
  // Apply power to the soil moisture sensor
  digitalWrite(A0, HIGH);
  delay(10);

  moisture = analogRead(A1);

  // Turn off the sensor
  digitalWrite(A0, LOW);

  // Turn off all LEDs
  digitalWrite(8, LOW);
  digitalWrite(10, LOW);
  digitalWrite(12, LOW);

  Serial.println(moisture);

  if (moisture < 600) {
    // Dry soil
    digitalWrite(12, HIGH);
  }
  else if (moisture < 800) {
    // Medium moisture
    digitalWrite(10, HIGH);
  }
  else {
    // Wet soil
    digitalWrite(8, HIGH);
  }

  delay(100);
}