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

  int  reaching_cost;
  int  distance;

public:
  Square();

  Square*&  operator[](Direction  dir);

  void  clear();

  void  subsearch_reaching_cost(Piece*  actor, int  cost);
  void     search_reaching_cost(Piece*  actor           );

  void  subsearch_distance(Piece*  actor, int  dist);
  void     search_distance(Piece*  actor           );

};




#endif




