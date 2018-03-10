// Hexed Game
// Rohan Judd Feb 2018

#include "hex_byte.h"
#include "game.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const int c = 261;
const int d = 294;
const int e = 329;

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
  delay(2000);

  Serial.begin(115200);
  Serial.println("Hexed");
  hex_game.new_target();
}

void loop()
{
  button_byte = get_button_byte();
  update_new_presses();
  update_guess();
  update_screen();
  delay(50);
  if (hex_game.check_guess(guess)){
    beep();
    guess = 0;
  }
}

void update_screen()
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(hex_game.target_to_string());
  display.setCursor(0, 16);
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
  if (receivedChars[0] == 'm')
  {
    if (isDigit(receivedChars[1]))
    {
      //hex_game.change_mode(receivedChars[1] - 48);
      return true;
    }
  }
  return false;
}

void beep()
{
  tone(piezo, c, 80);
  delay(80);
  tone(piezo, e, 80);
  delay(100);
  tone(piezo, c, 80);
  delay(200);
}

byte get_button_byte()
{
  byte output = 0;
  for (int i = 0; i <= 8; i++){
    (!digitalRead(buttons[i])) ? (bitSet(output, i)) : (0);
  }
  return output;
}

void debug_byte(String s, byte b)
{
  Serial.print(s);
  Serial.print(": ");
  Serial.println(get_binary_string(b));
}

void update_guess()
{
  for (int i = 0; i <= 8; i++){
    if (bitRead(new_presses, i)){
      bitWrite(guess, i, !bitRead(guess, i));
    }
  }
}

void update_new_presses()
{
  new_presses = 0;
  for (int i = 0; i <= 8; i++){
    if ((bitRead(button_byte, i)) && (!bitRead(last_button_byte, i))){
      bitSet(new_presses, i);
    }
  }
  last_button_byte = button_byte;
}

