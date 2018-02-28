/*
  game.cpp - Class for game object
*/
#include "Arduino.h"
#include "game.h"
#include "hex_byte.h"

// Mode 0 HEX to BIN
// Mode 1 HEX to DEC
// Mode 2 BIN to HEX
// Mode 3 BIN to DEC
// Mode 4 DEC to BIN
// Mode 5 DEC to HEX

Game::Game(byte mode)
{
  _mode = mode;
}

void Game::new_target()
{
  _target = random(0, 255);
  _guess = 0;
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
  switch (_mode) {
    case 0:
      output += get_hex_string(_target);
      break;
    case 1:
      output += get_hex_string(_target);
      break;
    case 2:
      output += "Not Implemented";
      break;
    case 3:
      output += "Not Implemented";
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
  Serial.print("MODE: ");
  Serial.print(_mode);
  Serial.print("  Target: ");
  Serial.println(output);
}
void Game::set_guess(byte b)
{
  _guess = b;
}

boolean Game::check_guess()
{
  return (_guess == _target);
}


