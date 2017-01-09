#ifndef TRPT_PLAYER_HPP
#define TRPT_PLAYER_HPP


#include"trpt_movecontext.hpp"


namespace Direction{
constexpr int  north = 0;
constexpr int   east = 1;
constexpr int   west = 2;
constexpr int  south = 3;
}


enum class
PlayerState
{
  stop,

};


struct
Player
{
  MoveContext  movctx;

  int  weight=40;
  int  power_max=300;
  int  power_consumed=0;
  int  foods=100;
  int  nutrient=100;

  bool  pausing=true;

};


#endif




