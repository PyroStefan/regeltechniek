int DC = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(DC, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int x = 0; x <= 255; x += 5) {
    Serial.print(String(x) + ", ");
    analogWrite(DC, x);
    delay(50);
  }

  delay(5000);

  for(int x = 255; x >= 0; x -= 5) {
    Serial.print(String(x) + ", ");
    analogWrite(DC, x);
    delay(50);
  }

  delay(5000);
}
