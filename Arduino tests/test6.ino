// Regeltechniek
// Fan speed is controlled by changing the fanSpeed variable
// temperature is being measured against the back of the mobile with
// a DS18B20 temperature sensor

#include<LiquidCrystal.h>

// OneWire is used for the DS18B20 sensor and calculations with DallasTemperature
#include <OneWire.h>
#include <DallasTemperature.h>

// Arduino pin-out used in the experiments
#define pwm 9
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
// used for the intro animation
byte degree[8] = 
              {
                0b00011,
                0b00011,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };
 
void setup() {
  lcd.begin(16, 2);
  lcd.createChar(1, degree);
  lcd.clear();
  lcd.print("  Regeltechniek  ");
  lcd.setCursor(0,1);
  lcd.print("  Project ");
  delay(2000);

  Serial.begin(9600); 
  sensors.begin();
}

void loop() {
  // Read temperature as Celsius
  float t = sensors.getTempCByIndex(0);

  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println("Failed to read from temperature sensor!");
    return;
  }
  
  // Temperature readings displayed
  Serial.print("temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");

  lcd.setCursor(0,0);
  lcd.print("temp: ");
  lcd.print(t);
  lcd.print(" *C");

  // Fan speed
  // %   - pwm
  // 100 - 255
  // 80  - 204
  // 75  - 191
  // 60  - 153
  // 40  - 102
  // 25  - 64
  // 20  - 51
  int fanSpeed = 255;
  analogWrite(pwm, fanSpeed); 

  Serial.print("\t fan: ");
  Serial.print(fanSpeed);
  Serial.print(" %\n");

  lcd.setCursor(0,1);
  lcd.print("Fan ");
  lcd.print(fanSpeed);
  lcd.print(" %");

  // Wait a couple of seconds between measurements.
  delay(2000);
}
