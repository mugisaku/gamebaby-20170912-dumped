#ifndef ROGIE_SQUARE_HPP_INCLUDED
#define ROGIE_SQUARE_HPP_INCLUDED


#include<cstdint>
#include"gmbb.hpp"


enum class
Direction
{
  back_left,
  back,
  back_right,
  left,
  right,
  front_left,
  front,
  front_right,

  END,

};


enum class
SquareKind
{
  null,
  
};


struct Piece;


struct
Square
{
  SquareKind  kind;

  gmbb::Point  point;

  Square*  link[static_cast<int>(Direction::END)];

  Piece*  current_piece;

public:
  Square();

  Square*&  operator[](Direction  dir);

  void  clear();

};




#endif




