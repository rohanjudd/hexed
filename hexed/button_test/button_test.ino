/* Button Test
  Tests the function of all the inputs and outputs on the hexed game
*/

#include "ssd1306.h"
#include "font6x8.h"

byte buttons[10] = {4, 5, 6, 7, 8, 9, 10, 12, 14, 15};
byte pot = 17;
byte led1 = 2;
byte led2 = 3;
byte piezo = 11;
boolean state = false;
int freq = 0;

void setup()
{
  for (int i = 0; i <= 10; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  pinMode(pot, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(piezo, OUTPUT);

  ssd1306_128x32_i2c_init();
  ssd1306_fillScreen(0x00);
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_printFixedN (0, 0, "HEXED", STYLE_BOLD, FONT_SIZE_2X);

  Serial.begin(115200);
}

void loop()
{
  Serial.print("button byte: ");
  Serial.println(get_button_byte());
  Serial.print("button A: ");
  Serial.println(!digitalRead(buttons[8]));
  Serial.print("button B: ");
  Serial.println(!digitalRead(buttons[9]));
  Serial.print("pot: ");
  int pot1 = analogRead(pot);
  Serial.println(pot1);
  //digitalWrite(led1, state);
  //digitalWrite(led2, !state);
  state = !state;
  freq = pot1 * 3 + (digitalRead(buttons[0]) * 200);
  //tone(piezo,freq);
  delay(300);
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

