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
    byte get_target();
    String get_target_string();
    void change_input_mode();
    void change_output_mode();
    String target_to_string();
    void check_guess(char c[]);
    boolean check_guess(byte b);

  private:
    byte _input_mode;
    byte _output_mode;
	  byte _target;
	  int _score;
};

#endif
