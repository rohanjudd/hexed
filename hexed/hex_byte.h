/*
  hex_byte.h - Class for hex byte object
*/
#ifndef hex_byte.h
#define hex_byte.h

#include "Arduino.h"

class Hex_Byte
{
  public:
	  Hex_Byte(byte b);
	  void set_value(byte b);
	  byte get_value();
	  byte get_high();
	  byte get_low();
	  void generate();
	  String get_hex_string();
	  String get_binary_string();
	  char nibble_to_ascii(byte b);
  
  private:
	  byte _value;
	  byte _high;
	  byte _low;
};

#endif