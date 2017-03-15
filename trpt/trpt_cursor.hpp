#ifndef TRPT_CURSOR_HPP
#define TRPT_CURSOR_HPP


#include"gmbb_rectangle.hpp"


namespace gmbb{
namespace trpt{


struct Piece;


struct
Cursor: public Point
{
  bool  show=true;

  Piece*  linked_piece=nullptr;

  void    link(Piece&  p);
  void  unlink(         );

};


}}


#endif




