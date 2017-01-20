#ifndef TRPT_VIEW_HPP
#define TRPT_VIEW_HPP


#include"trpt_square.hpp"
#include"trpt_cursor.hpp"
#include"gmbb.hpp"


namespace gmbb{
namespace trpt{


struct Board;


class
View
{
  Board*  board;

  Image  board_image;

  Point  offset    ;
  Point  offset_max;

  int   width;
  int  height;

  Point  cursor_point;
  Point  window_point;

public:
  static Image  sprite_image;

  View(Board*  brd=nullptr);

  void  change_board(Board&  brd);

  void  change_width(int   v);
  void  change_height(int  v);

  void  process(Controller&  ctrl);

  void  move_window_point();

  void  draw_windows(Image&  dst) const;

  void  render(Image&  dst) const;

};


}}


#endif




