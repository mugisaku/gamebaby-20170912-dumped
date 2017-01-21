#ifndef TRPT_MASTER_HPP
#define TRPT_MASTER_HPP


#include"trpt_square.hpp"
#include"trpt_cursor.hpp"
#include"trpt_facility.hpp"
#include"trpt_town.hpp"
#include<list>
#include<array>
#include"gmbb.hpp"


namespace gmbb{
namespace trpt{


struct Board;
struct Porter;
struct Piece;


enum class
MasterState
{
  watch,
  decide_destination,

};


class
Master
{
  Board*  board;

  Image  board_image;

  Point  offset    ;
  Point  offset_max;

  int   width;
  int  height;

  MasterState  state;

  Point  cursor_point;
  Point  window_point;

  Cursor   first_cursor;
  Cursor  second_cursor;

  std::array<Facility,8>  facility_table;
  std::array<Town,8>          town_table;

  std::list<Porter*>  reserve_table;

  Cursor*  current_cursor;
  Piece*   current_piece;
  Piece*    called_piece;
  Square*  current_square;

  void  process_watch(Controller&  ctrl);
  void  process_decide_destination(Controller&  ctrl);

  void  update_current_piece();
  void  update_current_square();

public:
  static Image  sprite_image;

  Master(Board*  brd=nullptr);

  void  change_board(Board&  brd);

  void  change_width(int   v);
  void  change_height(int  v);

  const Cursor&   get_first_cursor() const;
  const Cursor&  get_second_cursor() const;
  const Cursor*  get_current_cursor() const;
  Piece*   get_current_piece() const;
  Square*  get_current_square() const;


  void  process(Controller&  ctrl);

  void  move_window_point();

  void  draw_windows(Image&  dst) const;

  void  render(Image&  dst) const;

  void  set_stage();

};


}}


#endif




