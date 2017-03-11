#ifndef ROGIE_SQUARE_HPP_INCLUDED
#define ROGIE_SQUARE_HPP_INCLUDED


#include<cstdint>
#include"gmbb.hpp"
#include"rogie_direction.hpp"


enum class
SquareKind
{
  null,
  
};


enum class
TrapKind
{
  null,

};


struct Piece;


struct
Square
{
  SquareKind       kind;
    TrapKind  trap_kind;

  bool  passable;

  gmbb::Point  point;

  Square*  link[static_cast<int>(Direction::END)];

  Piece*  current_piece;

  int  reaching_cost;

public:
  Square();

  Square*&  operator[](Direction  dir);

  void  clear();

  void  subsearch(Piece*  actor, int  cost);
  void     search(Piece*  actor           );

};




#endif




