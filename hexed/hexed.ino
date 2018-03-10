// Hexed Game
// Rohan Judd Feb 2018

#include "hex_byte.h"
#include "game.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

byte bit_button[8] = {4, 5, 6, 7, 8, 9, 10, 12};
byte button_byte = 0;
byte last_button_byte = 0;
byte new_presses = 0;
byte guess = 0;
byte pot = 17;
byte led1 = 2;
byte led2 = 3;
byte button_a = 14;
byte button_b = 15;
byte piezo = 11;
boolean state = false;
int freq = 0;

Game hex_game(0);

void setup()
{
  for (int i = 0; i < 9; i++){
    pinMode(bit_button[i], INPUT_PULLUP);
  }
  pinMode(pot, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(piezo, OUTPUT);
  pinMode(16, INPUT);
  randomSeed(analogRead(16));

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  delay(1500);
  
  Serial.begin(115200);
  Serial.println("Hexed");
  new_target();
}

void loop()
{
  button_byte = get_button_byte();
  debug_byte("button_byte", button_byte);

  update_new_presses();
  debug_byte("new presses", new_presses);
  
  update_guess();
  debug_byte("guess", guess);
  update_screen();
  delay(50);
  if(hex_game.check_guess(guess))
  {
    beep();
    delay(200);
    guess = 0;
  }
}

void update_screen()
{
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(hex_game.target_to_string());
  display.setCursor(0,16);
  display.println(get_binary_string(guess));
  display.display();
}

void beep()
{
  for(int i=1912; i<=3038; i+=30){
    tone(piezo,i);
    delay(4);
  }
  noTone(piezo);
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

byte get_button_byte()
{
  byte output = 0;
  for (int i = 0; i <= 8; i++)
  {
    (!digitalRead(bit_button[i])) ? (bitSet(output, i)) : (0);
  }
  return output;
}

void draw_byte(byte b)
{
  String s = get_binary_string(b);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.clearDisplay();
  display.println(s);
  display.display();
}

void debug_byte(String s, byte b)
{
  Serial.print(s);
  Serial.print(": ");
  Serial.println(get_binary_string(b));
}

void update_guess()
{
  for(int i=0; i<=8; i++)
  {
    if(bitRead(new_presses, i))
    {
      bitWrite(guess, i, !bitRead(guess, i));
    }
  }
}

void update_new_presses()
{
  new_presses = 0;
  for(int i=0; i<=8; i++)
  {
    if((bitRead(button_byte, i)) && (!bitRead(last_button_byte, i)))
    {
      bitSet(new_presses, i);
    }
  }
  last_button_byte = button_byte;
}

