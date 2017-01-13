#ifndef TRPT_PLAYER_HPP
#define TRPT_PLAYER_HPP


#include"trpt_vector.hpp"
#include"core/gmbb_object.hpp"


namespace gmbb{
namespace trpt{


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
Distance
{
  int  value;

  constexpr Distance(int  v=0): value(v){}

};


struct Board;


struct
Player
{
  Board*  board;

  int  offense;
  int  defense;
  int  physical;
  int  mental;
  int  fame;
  int  charm;
  int  luck;

  const char16_t*  hobby;
  const char16_t*  wish;

  Point  destination_point;
  Point  progressive_point;

  Vector   willing_vector;
  Vector  inertial_vector;
  Vector    forced_vector;

  int  animation_timer;
  int  animation_counter;

  int  weight=40;
  int  power_max=300;
  int  power_consumed=0;
  int  foods=100;
  int  nutrient=100;

  bool  pausing=true;

  void  set_current_point(    int  x, int  y);
  void  set_destination_point(int  x, int  y);

  void  step();

  Point  get_current_point() const;

  Distance  update_willing_vector();

  void  render(const Image&  src, Image&  dst) const;

};


}}


#endif




