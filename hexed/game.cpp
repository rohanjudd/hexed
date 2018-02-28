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
}

byte Game::get_target()
{
  return _target;
}

void Game::set_guess(byte b)
{
  _guess = b;
}

boolean Game::check_guess()
{
  return(_guess == _target);
}
