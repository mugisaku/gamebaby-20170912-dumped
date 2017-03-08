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


constexpr Direction
opposite(Direction  d)
{
    switch(d)
    {
  case(Direction::back_left  ): return Direction::front_right;
  case(Direction::back       ): return Direction::front      ;
  case(Direction::back_right ): return Direction::front_left ;
  case(Direction::left       ): return Direction::right      ;
  case(Direction::right      ): return Direction::left       ;
  case(Direction::front_left ): return Direction::back_right ;
  case(Direction::front      ): return Direction::back       ;
  case(Direction::front_right): return Direction::back_left  ;
    }


  return Direction::front;
}


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

  bool  passable;

  gmbb::Point  point;

  Square*  link[static_cast<int>(Direction::END)];

  Piece*  current_piece;

public:
  Square();

  Square*&  operator[](Direction  dir);

  void  clear();

};




#endif




