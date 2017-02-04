#ifndef TRPT_MASTER_HPP
#define TRPT_MASTER_HPP


#include"trpt_square.hpp"
#include"trpt_cursor.hpp"
#include"trpt_facility.hpp"
#include"trpt_town.hpp"
#include"trpt_entrybook.hpp"
#include"trpt_piecemanager.hpp"
#include"trpt_board.hpp"
#include<list>
#include<array>
#include"gmbb.hpp"


namespace gmbb{
namespace trpt{


struct Porter;
struct Piece;


enum class
MasterState
{
  watch,
  change_destination,
  choose_porter,

};


class
Master
{
  Image  board_image;

  Board  board;

  Rectangle  view;

  MasterState  state;

  bool  haste_flag;

  Point  window_point;

  Cursor   first_cursor;
  Cursor  second_cursor;

  std::array<Facility,8>  facility_table;
  std::array<Town,8>          town_table;

  std::list<Porter*>*  porter_list;

  Cursor*  current_cursor;
  Piece*   current_piece;
  Square*  current_square;

  Piece*     designated_piece;
  Square*    designated_square;
  Facility*  designated_facility;

  EntryBook<std::list<Porter*>::iterator,6,5>  entrybook;

  Point  book_index;

  PieceManager  pm;

  void  process_watch(Controller&  ctrl);
  void  process_choose_porter(Controller&  ctrl);
  void  process_change_destination(Controller&  ctrl);

  void  update_current_piece();
  void  update_current_square();

  void  update_entrybook(Town&  t);

  void  move_up();
  void  move_left();
  void  move_right();
  void  move_down();

public:
  static Image  sprite_image;

   Master();
  ~Master();

  void  change_size(int  w, int  h);

  const Cursor&   get_first_cursor() const;
  const Cursor&  get_second_cursor() const;
  const Cursor*  get_current_cursor() const;
  Piece*   get_current_piece() const;
  Square*  get_current_square() const;


  void  process(Controller&  ctrl);
  void  step();

  void  load(const File*  f);

  void  move_window_point();

  void  draw_windows(Image&  dst) const;
  void  draw_porter(int  x, int  y, Image&  dst) const;
  void  draw_entrybook(Image&  dst) const;

  void  render(Image&  dst) const;

  void  set_stage();

};


}}


#endif




