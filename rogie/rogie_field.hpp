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

  gmbb::Image  image;

  std::list<Piece*>  piece_list;

  Piece*  master;

public:
  Field();

  void  prepare();

  void  put(Piece*  p, int  x, int  y);
  void  put(Item&&  itm, int  x, int  y);

  void  process(const gmbb::Controller&  ctrl);

  void  cycle();

  void  prepare_to_search();

  void  render(gmbb::Image&  dst);

  void  print() const;

};




#endif




