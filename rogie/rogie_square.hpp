#ifndef ROGIE_SQUARE_HPP_INCLUDED
#define ROGIE_SQUARE_HPP_INCLUDED


#include<cstdint>
#include"gmbb.hpp"
#include"rogie_direction.hpp"
#include"rogie_item.hpp"


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
struct Field;


struct
Square
{
  Field*  field;

  SquareKind       kind;
    TrapKind  trap_kind;

  bool  passable;

  gmbb::Point  point;

  Square*  link[static_cast<int>(Direction::END)];

  Piece*  current_piece;

  Item  placed_item;

  int  distance;

public:
  Square();

  Square*&  operator[](Direction  dir);

  void  clear();

  void  subsearch(Piece*  actor, int  dist);
  void     search(Piece*  actor           );

};




#endif




