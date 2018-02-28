/*
  hex_byte.cpp - Class for hex byte object
*/
#include "Arduino.h"
#include "hex_byte.h"

byte get_high(byte b)
{
  return b >> 4;
}

byte get_low(byte b)
{
  return b & 0x0F;
}

byte generate_byte()
{
  return byte(random(0, 255));
}

String get_hex_string(byte b)
{
  String output = "";
  output += nibble_to_ascii(get_high(b));
  output += nibble_to_ascii(get_low(b));
  return output;
}

char nibble_to_ascii(byte b)
{
  if (b < 10)
  {
    return b + 48;
  }
  else
  {
    return b - 10 + 65;
  }
}

String get_binary_string(byte b)
{
  String output = "";
  for (int i = 7; i >= 0; i--)
  {
    if bitRead(b, i)
    {
      output += "1";
    }
    else
    {
      output += "0";
    }
  }
  return output;
}

byte parse_binary_input(char c[])
{
  byte b  = 0;
  for(int i = 0; i < 8; i++)
  {
    if(c[i] == '1')
    {
      bitSet(b, 7 - i);
    }
  }
  return b;
}
