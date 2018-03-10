// Hexed Game
// Rohan Judd Feb 2018

#include "hex_byte.h"
#include "game.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const byte numChars = 9;
char receivedChars[numChars]; // an array to store the received data
boolean newData = false;

byte buttons[10] = {4, 5, 6, 7, 8, 9, 10, 12, 14, 15};
byte button_byte = 0;
byte last_button_byte = 0;
byte new_presses = 0;
byte guess = 0;
byte pot = 17;
byte led1 = 2;
byte led2 = 3;
byte piezo = 11;
boolean state = false;
int freq = 0;

Game hex_game(0);

void setup()
{
  pinMode(16, INPUT);
  randomSeed(analogRead(16));
  
  for (int i = 0; i <= 10; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(pot, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(piezo, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  delay(100);
  
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
  hex_game.check_guess(guess);
  update_screen();
  delay(50);
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
void check_serial()
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
      //hex_game.change_mode(receivedChars[1] - 48);
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

byte get_button_byte()
{
  byte output = 0;
  for (int i = 0; i <= 8; i++)
  {
    (!digitalRead(buttons[i])) ? (bitSet(output, i)) : (0);
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

