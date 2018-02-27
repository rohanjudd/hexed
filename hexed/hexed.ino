// Hexed Game 
// Rohan Judd Feb 2018

#include "hex_byte.h"

byte guess = 0;
int score = 0;

Hex_Byte target(0);

void setup() 
{
  Serial.begin(115200);
  while(!Serial)
  Serial.println("Hexed");
}

void loop() 
{
  target.generate();
  print_target();
  delay(400);
}

void print_target()
{
  Serial.print("DEC: ");
  Serial.print(target.get_value());
  Serial.print("  HEX: ");
  Serial.print(target.get_hex_string());
  Serial.print("  BIN: ");
  Serial.println(target.get_binary_string());
}



  
