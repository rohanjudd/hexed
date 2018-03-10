byte piezo = 11;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  for(int i=1912; i<=3038; i+=30){
    tone(piezo,i);
    delay(4);
  }
  noTone(piezo);
  delay(500);

}
