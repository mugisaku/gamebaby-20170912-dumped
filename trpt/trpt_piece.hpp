#ifndef TRPT_PIECE_HPP
#define TRPT_PIECE_HPP


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


struct
Distance
{
  int  value;

  constexpr Distance(int  v=0): value(v){}

};


struct Board;
struct Square;


struct
Piece
{
  Board*  board;

  Point  destination_point;
  Point  progressive_point;

  Vector   willing_vector;
  Vector  inertial_vector;
  Vector    forced_vector;

  int  animation_timer=0;
  int  animation_phase=0;

  bool  pausing=true;

  Piece(){}

  void  set_current_point(    int  x, int  y);
  void  set_destination_point(int  x, int  y);

  void  step();

  Point  get_current_point() const;

  const Square&  get_entering_square() const;

  Distance  update_willing_vector();

  void  render(const Image&  src, const Point&  offset, Image&  dst) const;

};


}}


#endif




