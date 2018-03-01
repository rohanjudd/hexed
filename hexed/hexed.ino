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
  if(receivedChars[0] == 'm')
  {
    if(isDigit(receivedChars[1]))
    {
      hex_game.change_mode(receivedChars[1] - 48);
      return true;
    }
  }
  return false;
}

void new_target()
{
  hex_game.new_target();
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



