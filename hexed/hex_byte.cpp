/*
hex_byte.cpp - Class for hex byte object
*/
#include "Arduino.h"
#include "hex_byte.h"


Hex_Byte::Hex_Byte(byte b)
{
	set_value(b);	
}

void Hex_Byte::set_value(byte b)
{
	_value = b;
	_high = _value >> 4;
	_low = _value & 0x0F;
}

byte Hex_Byte::get_value()
{
	return _value;
}

byte Hex_Byte::get_high()
{
	return _value >> 4;
}

byte Hex_Byte::get_low()
{
	return _value & 0x0F;
}

void Hex_Byte::generate()
{
	set_value(random(0,255));
}

String Hex_Byte::get_hex_string()
{
String output = "";
output += nibble_to_char(high);
output += nibble_to_char(low);
return output;
}

char Hex_Byte::nibble_to_ascii(byte b)
{
if(b < 10)
{
  return b + 48;
}
else
{
  return b - 10 + 65;
}
}
};

#endif