/* Button Test
  Tests the function of all the inputs and outputs on the hexed game
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

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

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(100);
  Serial.begin(115200);
}

void loop()
{
  button_byte = get_button_byte();
  debug_byte("button_byte", button_byte);

  update_new_presses();
  debug_byte("new presses", new_presses);
  
  update_guess();
  debug_byte("guess", guess);
  
  draw_byte(guess);
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
  delay(50);
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

String get_binary_string(byte b)
{
  String output = "";
  for (int i = 7; i >= 0; i--)
  {
    (bitRead(b, i)) ? (output += "1") : (output += "0");
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

