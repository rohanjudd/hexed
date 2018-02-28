/*
  hex_byte.h - Class for hex byte object
*/
#ifndef hex_byte.h 
#define hex_byte.h 

#include "Arduino.h"

byte get_high(byte b);
byte get_low(byte b);
byte generate_byte();
String get_hex_string(byte b);
String get_binary_string(byte b);
char nibble_to_ascii(byte b);
byte parse_binary_input(char c[]);

#endif
