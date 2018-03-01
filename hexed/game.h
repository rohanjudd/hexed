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
    void show_target();
    void change_mode(int m);
    byte get_target();
    void check_guess(char c[]);

  private:
    boolean solved = false;
	  byte _mode;
	  byte _target;
	  int _score;
};

#endif
