/*
game.cpp - Class for game object
*/
#include "Arduino.h"
#include "game.h"


Game::Game(byte mode)
{
	_mode = mode;
}

void Game::new_target(byte b)
{
	_target = b;
	_guess = 0;
}

byte Game::get_target()
{
  return _target;
}

void Game::set_guess(byte b)
{
  _guess = b;
}

void Game::try_guess()
{
  if(_guess == _target)
  {
    Serial.println("Correct");
  }
  else
  {
    Serial.println("Wrong");
  }
}
