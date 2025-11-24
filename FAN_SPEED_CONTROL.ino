#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 11
#define PIRPIN 12
#define FAN_PIN 6         // Main fan (shared)
#define FAN3_PIN 3        // Cold air fan
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastMotionTime = 0;
bool motionActive = false;
bool fanState = false;
bool fan3State = false;

const unsigned long motionTimeout = 10000; // 10 seconds

void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(PIRPIN, INPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(FAN3_PIN, OUTPUT);

  Serial.println("System initialized");
}

void loop() {
  float temp = dht.readTemperature();
  bool motion = digitalRead(PIRPIN);
  unsigned long now = millis();

  // Motion tracking
  if (motion) {
    lastMotionTime = now;
    motionActive = true;
  } else if (motionActive && (now - lastMotionTime > motionTimeout)) {
    motionActive = false;
  }

  // Main fan control (simplified)
  if (!isnan(temp)) {
    if (temp > 30 || motionActive) {
      digitalWrite(FAN_PIN, HIGH);
      digitalWrite(FAN3_PIN, HIGH);
      fanState = true;
      fan3State = true;
    } else {
      digitalWrite(FAN_PIN, LOW);
      digitalWrite(FAN3_PIN, LOW);
      fanState = false;
      fan3State = false;
    }
  }

  // Serial Output
  Serial.print("Temp: ");
  Serial.print(isnan(temp) ? 0 : temp);
  Serial.print("C | Motion: ");
  Serial.print(motionActive ? "YES" : "NO");
  Serial.print(" | Fan: ");
  Serial.print(fanState ? "ON" : "OFF");
  Serial.print(" | Cold Fan: ");
  Serial.println(fan3State ? "ON" : "OFF");

  // LCD Display
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(isnan(temp) ? 0 : temp);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(motionActive ? "Motion:YES " : "Motion:NO  ");
  lcd.print(fan3State ? "C:ON" : "C:OFF");

  delay(1000);
}
