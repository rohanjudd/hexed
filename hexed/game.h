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
	  void new_target(byte b);
    byte get_target();
	  void set_guess(byte b);
    void try_guess();

  private:
    boolean solved = false;
	  byte _mode;
	  byte _target;
	  byte _guess;
	  int _score;
};

#endif
