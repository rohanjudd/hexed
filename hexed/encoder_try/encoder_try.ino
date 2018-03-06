#define encoder0PinA  2
#define encoder0PinB  3

volatile int encoder0Pos = 0;
volatile boolean PastA = 0;
volatile boolean PastB = 0;

void setup() 
{
  Serial.begin(115200);
  Serial.println("Encoder Test");

  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  PastA = (boolean)digitalRead(encoder0PinA); //initial value of channel A;
  PastB = (boolean)digitalRead(encoder0PinB); //and channel B

  attachInterrupt(0, doEncoderA, RISING);
  attachInterrupt(1, doEncoderB, CHANGE);
}

void loop() 
{
  Serial.print("pos: ");
  Serial.println(encoder0Pos);
  delay(100);
}

void doEncoderA()
{
  PastB ? encoder0Pos-- :  encoder0Pos++;
}

void doEncoderB()
{
  PastB = !PastB;
}
