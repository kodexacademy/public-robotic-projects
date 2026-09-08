#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte START = 2;
const byte PAUSE = 3;
const byte STOP = 4;

bool running = false;
bool paused = false;

unsigned long savedTime = 0;
unsigned long startTime = 0;

bool oldStart = HIGH;
bool oldPause = HIGH;
bool oldStop = HIGH;

void setup()
{
  lcd.init();
  lcd.backlight();

  pinMode(START, INPUT_PULLUP);
  pinMode(PAUSE, INPUT_PULLUP);
  pinMode(STOP, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("STOPWATCH");

  showTime(0);
}

void loop()
{
  bool startButton = digitalRead(START);
  bool pauseButton = digitalRead(PAUSE);
  bool stopButton = digitalRead(STOP);

  // START button
  if (oldStart == HIGH && startButton == LOW)
  {
    if (!running)
    {
      running = true;
      paused = false;
      startTime = millis();
    }

    delay(200);
  }

  // PAUSE / RESUME button
  if (oldPause == HIGH && pauseButton == LOW)
  {
    if (running && !paused)
    {
      savedTime += millis() - startTime;
      paused = true;
    }
    else if (running && paused)
    {
      startTime = millis();
      paused = false;
    }

    delay(200);
  }

  // STOP button
  if (oldStop == HIGH && stopButton == LOW)
  {
    running = false;
    paused = false;
    savedTime = 0;

    showTime(0);

    delay(200);
  }

  oldStart = startButton;
  oldPause = pauseButton;
  oldStop = stopButton;

  // Calculate current time
  unsigned long currentTime = savedTime;

  if (running && !paused)
  {
    currentTime += millis() - startTime;
  }

  showTime(currentTime);

  delay(20);
}

void showTime(unsigned long time)
{
  unsigned long minutes = time / 60000;
  unsigned long seconds = (time / 1000) % 60;
  unsigned long hundredths = (time / 10) % 100;

  lcd.setCursor(0, 1);

  if (minutes < 10)
    lcd.print("0");

  lcd.print(minutes);
  lcd.print(":");

  if (seconds < 10)
    lcd.print("0");

  lcd.print(seconds);
  lcd.print(".");

  if (hundredths < 10)
    lcd.print("0");

  lcd.print(hundredths);

  lcd.print("       ");
}