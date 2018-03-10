/*
  game.cpp - Class for game object
*/
#include "Arduino.h"
#include "game.h"
#include "hex_byte.h"

static String FORMAT[3] = {"HEX","BIN","DEC"};
// 0 HEX
// 1 BIN
// 2 DEC

Game::Game(byte arg)
{
  _input_mode = 1;
  _output_mode = 0;
}

void Game::new_target()
{
  _target = random(0, 255);
  show_target();
}

byte Game::get_target()
{
  return _target;
}

void Game::change_input_mode()
{
  _input_mode = (_input_mode +1 ) % 3;
  if(_input_mode == _output_mode)
  {
    _input_mode = (_input_mode + 1) % 3;
  }
  new_target();
}

void Game::change_output_mode()
{
  _output_mode = (_output_mode +1 ) % 3;
  if(_output_mode == _input_mode)
  {
    _output_mode = (_output_mode + 1) % 3;
  }
  new_target();
}

void Game::show_target()
{
  Serial.print(target_to_string());
  Serial.print("  ");
  Serial.print(FORMAT[_input_mode]);
  Serial.print(" -> ");
  Serial.println(FORMAT[_output_mode]);
}

String Game::target_to_string()
{
  String target_text = "";
  switch (_output_mode)
  {
    case 0:
      target_text += get_hex_string(_target);
      break;
    case 1:
      target_text += get_binary_string(_target);
      break;
    case 2:
      target_text += String(_target);
      break;
    default:
      target_text = "Invalid Mode";
      break;
  }
  return target_text;
}

void Game::check_guess(char c[])
{
  byte guess = 0;
  switch (_input_mode)
  {
    case 0:
      guess =  parse_hex_input(c);
      break;
    case 1:
      guess =  parse_binary_input(c);
      break;
    case 3:
      guess = parse_decimal_input(c);
      break;
    default:
      Serial.println("Invalid Mode");
      break;
  }
  if (guess == _target)
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

void Game::check_guess(byte b)
{
  if (b == _target)
  {
    Serial.println("Correct");
    new_target();
  }
  else
  {
    Serial.println("Try Again");
  }
}

