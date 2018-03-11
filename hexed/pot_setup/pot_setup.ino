byte pot = 17;
byte value = 0;

void setup() {
  pinMode(pot, INPUT);
  Serial.begin(115200);
}

void loop() {
  value = analogRead(pot) / 64;
  Serial.println(value);
  delay(50);
}
