//Regeltechniek

#include<LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// arduino pin-out
#define pwm 9
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
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
  lcd.print("   Fan Speed  ");
  lcd.setCursor(0,1);
  lcd.print("  Controlling ");
  delay(2000);
  analogWrite(pwm, 255);
  lcd.clear();
  lcd.print("Regeltecniek ");
  delay(2000);

  Serial.begin(9600); 
  sensors.begin();
}

 

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Read temperature as Celsius
  float t = sensors.getTempCByIndex(0);

  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println("Failed to read from temperature sensor!");
    return;
  }
  
  Serial.print("temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");

 

  lcd.setCursor(0,0);
  lcd.print("temp: ");
  lcd.print(t);   // Printing terature on LCD
  lcd.print(" C");
  lcd.setCursor(0,1);

  analogWrite(pwm,255);
  lcd.print("Fan 100%            ");
  Serial.print("\t fan: 100% \n");
}