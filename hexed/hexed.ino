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
  Serial.begin(115200);
  Serial.println("Hexed");
  hex_game.new_target(generate_byte());
  print_all_formats(hex_game.get_target());
}

void loop()
{
  
  recvWithEndMarker();
  if (newData == true)
  {
    Serial.print("");
    Serial.println(receivedChars);
    newData = false;
    Serial.println(parse_binary_input(receivedChars));
  }
  //target = generate_byte();
  //print_target();
  //delay(400);
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



