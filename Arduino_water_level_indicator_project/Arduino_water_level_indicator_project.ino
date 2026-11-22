#include <LiquidCrystal_I2C.h>

#define FILTER_SIZE 20

// LCD Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Water Sensor
const int WaterSensorPin = A0;

// Traffic Light Module
const int RedLight = 9;
const int YellowLight = 8;
const int GreenLight = 7;

// Buzzer
const int Buzzer = 2;

// Sensor Calibration
// Replace with actual sensor readings
const int EMPTY_RAW = 0;
const int FULL_RAW = 1023;

// Filter Function
int Filter(int sensorValue);

// Traffic Light Control
void setLights(bool red, bool yellow, bool green) {
  digitalWrite(RedLight, red ? HIGH : LOW);
  digitalWrite(YellowLight, yellow ? HIGH : LOW);
  digitalWrite(GreenLight, green ? HIGH : LOW);
}

void setup() {

  Serial.begin(9600);

  // LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Traffic Light Setup
  pinMode(RedLight, OUTPUT);
  pinMode(YellowLight, OUTPUT);
  pinMode(GreenLight, OUTPUT);

  // Buzzer Setup
  pinMode(Buzzer, OUTPUT);

  // Initially OFF
  setLights(false, false, false);
  noTone(Buzzer);

  lcd.setCursor(2, 0);
  lcd.print("Kodex Academy");
  lcd.setCursor(3, 1);
  lcd.print("Water Level");

  delay(2000);
  lcd.clear();
}

void loop() {

  // Read Water Sensor
  int sensorValue = analogRead(WaterSensorPin);

  // Filter Sensor Reading
  int filteredValue = Filter(sensorValue);

  // Calculate Water Percentage
  int waterLevel = map(
    filteredValue,
    EMPTY_RAW,
    FULL_RAW,
    0,
    100
  );

  waterLevel = constrain(waterLevel, 0, 100);

  // Serial Monitor
  Serial.print("Sensor Value: ");
  Serial.print(filteredValue);

  Serial.print(" | Water Level: ");
  Serial.print(waterLevel);
  Serial.println("%");

  // LCD First Line
  lcd.setCursor(0, 0);
  lcd.print("Water Level: ");

  if (waterLevel < 100) lcd.print(" ");
  if (waterLevel < 10) lcd.print(" ");

  lcd.print(waterLevel);
  lcd.print("%");

  // CONDITION 1: 0% TO 10%
  // RED LIGHT + BUZZER ON

  if (waterLevel <= 10) {

    setLights(true, false, false);

    tone(Buzzer, 1000);

    lcd.setCursor(0, 1);
    lcd.print("LOW WATER - RED ");

  }

  // CONDITION 2: ABOVE 10% TO 50%
  // YELLOW LIGHT + BUZZER OFF

  else if (waterLevel <= 50) {

    setLights(false, true, false);

    noTone(Buzzer);

    lcd.setCursor(0, 1);
    lcd.print("MEDIUM - YELLOW ");

  }

  // CONDITION 3: ABOVE 50% TO 100%
  // GREEN LIGHT + BUZZER OFF

  else {

    setLights(false, false, true);

    noTone(Buzzer);

    lcd.setCursor(0, 1);
    lcd.print("HIGH WATER-GREEN");

  }

  delay(200);
}

// MOVING AVERAGE FILTER

int Filter(int sensorValue) {

  static int analogArray[FILTER_SIZE] = {0};
  static int count = 0;

  int filteredValue = 0;

  // Shift Previous Readings
  for (int i = 0; i < FILTER_SIZE - 1; i++) {
    analogArray[i] = analogArray[i + 1];
  }

  // Store New Reading
  analogArray[FILTER_SIZE - 1] = sensorValue;

  if (count < FILTER_SIZE) {
    count++;
  }

  // Calculate Average
  for (int i = FILTER_SIZE - count; i < FILTER_SIZE; i++) {
    filteredValue += analogArray[i];
  }

  return filteredValue / count;
}