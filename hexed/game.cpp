/*
  game.cpp - Class for game object
*/
#include "Arduino.h"
#include "game.h"
#include "hex_byte.h"

String MODES[6] = {"HEX -> BIN", 
                   "HEX -> DEC", 
                   "BIN -> HEX", 
                   "BIN -> DEC", 
                   "DEC -> BIN", 
                   "DEC -> HEX"};

Game::Game(byte mode)
{
  _mode = mode;
}

void Game::new_target()
{
  _target = random(0, 255);
  show_target();
}

void Game::change_mode(int m)
{
  if ( m >= 0 && m < 6 && m != _mode)
  {
    _mode = m;
  }
  new_target();
}

byte Game::get_target()
{
  return _target;
}

void Game::show_target()
{
  String output = "";
  switch (_mode)
  {
    case 0:
      output += get_hex_string(_target);
      break;
    case 1:
      output += get_hex_string(_target);
      break;
    case 2:
      output += get_binary_string(_target);
      break;
    case 3:
      output += get_binary_string(_target);
      break;
    case 4:
      output += String(_target);
      break;
    case 5:
      output += String(_target);
      break;
    default:
      output = "Invalid Mode";
      break;
  }
  Serial.print(output);
  Serial.print("  ");
  Serial.println(MODES[_mode]);
}

void Game::check_guess(char c[])
{
  byte input = 0;
  switch (_mode)
  {
    case 0:
      input =  parse_binary_input(c);
      break;
    case 1:
      input = parse_decimal_input(c);
      break;
    case 2:
      input =  parse_hex_input(c);
      break;
    case 3:
      input = parse_decimal_input(c);
      break;
    case 4:
      input =  parse_binary_input(c);
      break;
    case 5:
      input =  parse_hex_input(c);
      break;
    default:
      Serial.println("Invalid Mode");
      break;
  }
  if (input == _target)
  {
    Serial.println("Correct");
    new_target();
  }
  else
  {
    Serial.println("Try Again");
    show_target();
  }
}


