/*
  game.h - Class for hex byte object
*/
#ifndef game.h
#define game.h

#include "Arduino.h"

class Game
{
  public:
	  Game(byte mode);
	  void new_target();
	  void try_guess();
	  String get_value_string();

  private:
	  byte _mode;
	  byte _target;
	  byte _guess;
	  int _score;
};

#endif