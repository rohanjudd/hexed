// Hexed Game
// Rohan Judd Feb 2018

#include "hex_byte.h"
#include "game.h"

const byte numChars = 9;
char receivedChars[numChars]; // an array to store the received data
boolean newData = false;

const byte button[] = {4,5,6,7,8,9,10,11};
const byte ok = 12;
const byte cancel = 13;

#define encoder0PinA  2
#define encoder0PinB  3

volatile int encoder0Pos = 0;
volatile boolean PastA = 0;
volatile boolean PastB = 0;

Game hex_game(0);

void setup()
{
  for(int i=0; i<9; i++)
  {
    pinMode(button[i], INPUT_PULLUP);
  }
  pinMode(ok, INPUT_PULLUP);
  pinMode(cancel, INPUT_PULLUP);
  
  pinMode(A2, INPUT);
  randomSeed(analogRead(A2));

  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  PastA = (boolean)digitalRead(encoder0PinA); //initial value of channel A;
  PastB = (boolean)digitalRead(encoder0PinB); //and channel B

  attachInterrupt(0, doEncoderA, RISING);
  attachInterrupt(1, doEncoderB, CHANGE);
  
  Serial.begin(115200);
  Serial.println("Hexed");
  hex_game.new_target();
}

void loop()
{
  recvWithEndMarker();
  if (newData == true)
  {
    Serial.println(receivedChars);
    newData = false;
    if (!check_for_mode_change())
    {
      hex_game.check_guess(receivedChars);
    }
  }
}

boolean check_for_mode_change()
{
  if(receivedChars[0] == 'i')
  {
    hex_game.change_input_mode();
    return true;
  }
  if(receivedChars[0] == 'o')
  {
    hex_game.change_output_mode();
    return true;
  }
  return false;
}

void recvWithEndMarker()
{
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false)
  {
    rc = Serial.read();
    if (rc != endMarker)
    {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars)
      {
        ndx = numChars - 1;
      }
    }
    else
    {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void doEncoderA()
{
  PastB ? encoder0Pos-- :  encoder0Pos++;
}

void doEncoderB()
{
  PastB = !PastB;
}


