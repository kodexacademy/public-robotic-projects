#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <math.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String input = "";
String lastAnswer = "";

unsigned long lastPressA = 0, lastPressB = 0, lastPressC = 0;
int indexA = 0, indexB = 0, indexC = 0;
int lastPosA = -1, lastPosB = -1, lastPosC = -1;

char opsA[] = {'+', '-', '*', '/'};
String opsB[] = {"√", "^2"};
char opsC[] = {'(', ')'};

bool showingAnswer = false;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to Kodex");
  lcd.setCursor(4, 1);
  lcd.print("Academy");
  delay(2000);
  lcd.clear();
  lcd.print("Calculator mode");
  lcd.setCursor(7, 1);
  lcd.print("on");
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    lcd.clear();

    // === If showing answer and press *, clear everything ===
    if (showingAnswer && key == '*') {
      input = "";
      lastAnswer = "";
      showingAnswer = false;
      lcd.print("Cleared");
      resetIndexes();
      delay(500);
      lcd.clear();
      return;
    }

    // === If showing answer and press anything else, start fresh ===
    if (showingAnswer && key != '*') {
      input = "";
      showingAnswer = false;
      resetIndexes();
    }

    // === Digits ===
    if (key >= '0' && key <= '9') {
      input += key;
      resetIndexes();
    }

    // === A: + → - → * → / ===
    else if (key == 'A') {
      if (millis() - lastPressA < 1000 && lastPosA != -1) {
        indexA = (indexA + 1) % 4;
        input.setCharAt(lastPosA, opsA[indexA]);
      } else {
        indexA = 0;
        input += opsA[indexA];
        lastPosA = input.length() - 1;
      }
      lastPressA = millis();
    }

    // === B: √ ↔ ^2 ===
    else if (key == 'B') {
      if (millis() - lastPressB < 1000 && lastPosB != -1) {
        indexB = (indexB + 1) % 2;
        input.remove(lastPosB);
        input += opsB[indexB];
        lastPosB = input.length() - opsB[indexB].length();
      } else {
        indexB = 0;
        input += opsB[indexB];
        lastPosB = input.length() - opsB[indexB].length();
      }
      lastPressB = millis();
    }

    // === C: ( ↔ ) ===
    else if (key == 'C') {
      if (millis() - lastPressC < 1000 && lastPosC != -1) {
        indexC = (indexC + 1) % 2;
        input.setCharAt(lastPosC, opsC[indexC]);
      } else {
        indexC = 0;
        input += opsC[indexC];
        lastPosC = input.length() - 1;
      }
      lastPressC = millis();
    }

    // === D: Evaluate Expression ===
    else if (key == 'D') {
      float result = evaluateExpression(input);
      lcd.setCursor(0, 0);
      lcd.print("Ans: ");
      lcd.setCursor(0, 1);
      lcd.print(result);
      lastAnswer = String(result);
      showingAnswer = true;
      return;
    }

    // === *: Backspace single char (if not showing answer) ===
    else if (key == '*') {
      if (input.length() > 0) {
        input.remove(input.length() - 1);
      }
      resetIndexes();
    }

    // === #: Clear expression ===
    else if (key == '#') {
      input = "";
      lcd.print("Cleared");
      resetIndexes();
      delay(500);
      lcd.clear();
      return;
    }

    // === Display current expression ===
    lcd.setCursor(0, 0);
    lcd.print("Expr:");
    lcd.setCursor(0, 1);
    lcd.print(input);
  }
}

void resetIndexes() {
  lastPosA = -1;
  lastPosB = -1;
  lastPosC = -1;
}

// Basic evaluator
float evaluateExpression(String expr) {
  expr.replace("√", "s"); // use 's' for sqrt
  float num1 = 0, num2 = 0;
  char op = '+';
  bool parsingSecond = false;

  for (int i = 0; i < expr.length(); i++) {
    char c = expr[i];

    if (c >= '0' && c <= '9') {
      if (!parsingSecond)
        num1 = num1 * 10 + (c - '0');
      else
        num2 = num2 * 10 + (c - '0');
    }
    else if (c == '^' && i + 1 < expr.length() && expr[i + 1] == '2') {
      num1 = num1 * num1;
      i++;
    }
    else if (c == 's') {
      num1 = sqrt(num1);
    }
    else if (c == '+' || c == '-' || c == '*' || c == '/') {
      op = c;
      parsingSecond = true;
      num2 = 0;
    }
  }

  switch (op) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case '*': return num1 * num2;
    case '/': return num2 != 0 ? num1 / num2 : 0;
  }

  return 0;
}