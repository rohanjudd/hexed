// Hexed Game
// Rohan Judd Feb 2018

#include "hex_byte.h"
#include "game.h"

const byte numChars = 9;
char receivedChars[numChars]; // an array to store the received data
boolean newData = false;

Game hex_game(0);

void setup()
{
  pinMode(A0, INPUT);
  randomSeed(analogRead(A0));
  Serial.begin(115200);
  Serial.println("Hexed");
  new_target();
}

void loop()
{
  recvWithEndMarker();
  if (newData == true)
  {
    Serial.print("");
    Serial.println(receivedChars);
    newData = false;
    byte input = parse_binary_input(receivedChars);
    hex_game.set_guess(input);
    if (hex_game.check_guess())
    {
      Serial.println("Correct");
      new_target();
    }
    else
    {
      Serial.println("Try Again");
    }
  }
}

void new_target()
{
  hex_game.new_target();
  print_hex(hex_game.get_target());
}

void print_all_formats(byte b)
{
  Serial.print("DEC: ");
  Serial.print(b);
  Serial.print("  HEX: ");
  Serial.print(get_hex_string(b));
  Serial.print("  BIN: ");
  Serial.println(get_binary_string(b));
}

void print_hex(byte b)
{
  Serial.print("0x ");
  Serial.println(get_hex_string(b));
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



