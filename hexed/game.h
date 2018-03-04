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
    void change_input_mode();
    void change_output_mode();
    byte get_target();
    void check_guess(char c[]);

  private:
    byte _input_mode;
    byte _output_mode;
	  byte _target;
	  int _score;
};

#endif
