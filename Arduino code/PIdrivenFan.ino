// Regeltechniek Practicum
// Configuration: Arduino connected with a temperature sensor, display, fan (with gain from a transistor)

// Library for PID
#include <PID_v1.h>
#include <PID_AutoTune_v0.h>

// PI parameters
double Setpoint, Input, Output;
double Kp=0.041502, Ki=0.0013487, Kd=0;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
PID_ATune aTune(&Input, &Output);

// Library for display and temperature sensor
#include<LiquidCrystal.h>

#include <OneWire.h>
#include <DallasTemperature.h>


// arduino pin-out for transistor and temperature sensor
#define pwm 9
#define ONE_WIRE_BUS 6

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

  Setpoint = 34;
  myPID.SetMode(AUTOMATIC);

  Serial.begin(9600); 
  sensors.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Read temperature in Celsius
  sensors.requestTemperatures();
  float t = sensors.getTempCByIndex(0);

  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println("Failed to read from temperature sensor!");
    return;
  }

  // Display temperature reading in COM (PC) and then on the LCD display
  Serial.print("temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");

  lcd.setCursor(0,0);
  lcd.print("temp: ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0,1);

  // PID tuning and computing
  Input = t;
  myPID.Compute();

  aTune.Runtime();
  Kp = aTune.GetKp();
  Ki = aTune.GetKi();
  Kd = aTune.GetKd();
  myPID.SetTunings(Kp,Ki,Kd);
  myPID.Compute();

  int fanSpeed;
  fanSpeed = Output;

  // Display fanspeed in pwm on the COM (PC) and then on the lcd display
  analogWrite(pwm,fanSpeed);
  lcd.print("Fan ");
  lcd.print(fanSpeed);
  lcd.print("% ");
  Serial.print("\t fan: ");
  Serial.print(fanSpeed);
  Serial.print(" pwm ");
  Serial.print("Kp: ");
  Serial.print(Kp);
  Serial.print(" Ki: ");
  Serial.print(Ki);
  Serial.print("Kd: ");
  Serial.print(Kd);
  Serial.print("\n");
}
