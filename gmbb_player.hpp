#ifndef GMBB_PLAYER_HPP
#define GMBB_PLAYER_HPP


#include"gmbb_sprite.hpp"


namespace gmbb{



namespace Face{
constexpr int  front = 0;
constexpr int   back = 1;
constexpr int   left = 2;
constexpr int  right = 3;
}


struct
Player
{
  int  face;
  int  phase;

  uint32_t  last_time;

  Sprite  sprite;

public:
  void  process(Controller&  ctrl);

  void  step();

};


}




#endif




