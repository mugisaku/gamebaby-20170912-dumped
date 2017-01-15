#ifndef TRPT_BOARD_HPP
#define TRPT_BOARD_HPP


#include"trpt_square.hpp"
#include"gmbb.hpp"


namespace gmbb{
namespace trpt{


struct
Cursor
{
  int  x=0;
  int  y=0;

  bool  show;

};


struct
Board
{
  static Container  windowset;

  static Image  sprite_image;
  static Image      bg_image;

  int   width;
  int  height;

  Player  player;

  std::vector<Square>  square_table;

  Cursor   first_cursor;
  Cursor  second_cursor;

  Cursor*  current_cursor;

  Board(int  w=0, int  h=0);

  void  reset();

        Square&  get(int  x, int  y);
  const Square&  get_const(int  x, int  y) const;

  void  process(Controller&  ctrl);

  void  load(const File*  f);

  void  render(Image&  dst) const;

};


}}


#endif




