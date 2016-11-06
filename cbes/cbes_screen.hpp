#ifndef CBES_SCREEN_HPP
#define CBES_SCREEN_HPP


#include<SDL.h>
#include"cbes_container.hpp"


namespace cbes{


class
Screen
{
  SDL_Window*    window;
  SDL_Surface*  surface;

  CharacterTable  table;

  Object*  object;

  bool  refresh_flag;

public:
  Screen();

  void  open(int  w, int  h);
  void  close();

  void  change(Object*  obj, int  x, int  y);

  void  update();

  void  transfer();

  void  need_to_refresh();

};


extern Screen  screen;


}




#endif




