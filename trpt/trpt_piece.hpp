#ifndef TRPT_PIECE_HPP
#define TRPT_PIECE_HPP


#include"trpt_vector.hpp"
#include"trpt_cursor.hpp"
#include"gmbb_rectangle.hpp"
#include"gmbb_image.hpp"


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
struct Porter;
struct Facility;


struct
Piece
{
  Board*  board;

  Point  destination_point;
  Point  progressive_point;

  Vector   willing_vector;
  Vector  inertial_vector;
  Vector    forced_vector;

  Distance  distance;

  int  resistance;

  int  animation_timer=0;
  int  animation_phase=0;

  bool  pausing=true;

  Porter*          porter=nullptr;
  Square*  current_square=nullptr;

  Cursor*  linked_cursor=nullptr;

  Piece(Board&  brd): board(&brd), resistance(0){}

  void  set_current_point(    int  x, int  y);
  void  set_destination_point(int  x, int  y);

  void  step();

  void  sync();

  Point  get_current_point() const;

  void  update_current_square();
  void  update_willing_vector();

  void  render(const Image&  src, const Point&  offset, Image&  dst) const;

};


}}


#endif




