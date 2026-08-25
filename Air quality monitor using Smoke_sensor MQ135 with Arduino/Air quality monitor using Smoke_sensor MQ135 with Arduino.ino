#define MQ135_PIN A0
#define BUZZER_PIN 8

// Adjust this threshold according to your sensor readings
#define GAS_THRESHOLD 70  

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  Serial.println("MQ135 Gas Sensor Test Started...");
}

void loop() {
  int sensorValue = analogRead(MQ135_PIN);
  float voltage = sensorValue * (5.0 / 1023.0);

  Serial.print("Analog Value: ");
  Serial.print(sensorValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  // Check if gas detected (value above threshold)
  if (sensorValue > GAS_THRESHOLD) {
    Serial.println("⚠️ Gas Detected!");
    tone(BUZZER_PIN, 1000);   // Start buzzer (1kHz tone)
    delay(500);
    noTone(BUZZER_PIN);       // Stop buzzer
    delay(500);
  } 
  else {
    noTone(BUZZER_PIN);       // Ensure buzzer off
  }

  delay(500); // small delay for stable readings
}