#ifndef ROGIE_FIELD_HPP_INCLUDED
#define ROGIE_FIELD_HPP_INCLUDED


#include"rogie_square.hpp"
#include"rogie_piece.hpp"
#include<list>


struct
Field
{
  static constexpr int   width = 6;
  static constexpr int  height = 6;

  Square  table[height][width];

  std::list<Piece*>  piece_list;

  Piece*  master;

public:
  Field();

  void  prepare();

  void  put(Piece*  p);

  void  process(const gmbb::Controller&  ctrl);

  void  render(gmbb::Image&  dst);

};




#endif




