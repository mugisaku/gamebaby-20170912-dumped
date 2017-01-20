#ifndef TRPT_BOARD_HPP
#define TRPT_BOARD_HPP


#include"trpt_square.hpp"
#include"trpt_piece.hpp"
#include"trpt_facility.hpp"
#include"trpt_town.hpp"
#include"trpt_cursor.hpp"
#include"gmbb.hpp"
#include<list>
#include<array>


namespace gmbb{
namespace trpt{


enum class
BoardState
{
  watch,
  decide_destination,
  choose_porter,

};


class
Board
{
  std::array<Facility,8>  facility_table;
  std::array<Town,8>          town_table;

  std::list<Porter*>  reserve_table;

  int   width;
  int  height;

  std::list<Piece>  piece_list;

  std::vector<Square>  square_table;

  BoardState  state;

  Cursor   first_cursor;
  Cursor  second_cursor;

  Cursor*  current_cursor;
  Piece*   current_piece;
  Square*  current_square;

public:
  static Image  bg_image;

  Board(int  w=0, int  h=0);

  void  reset();

        Square&  get(int  x, int  y);
  const Square&  get_const(int  x, int  y) const;

  const Cursor&   get_first_cursor() const;
  const Cursor&  get_second_cursor() const;
  const Cursor*  get_current_cursor() const;

  int  get_width() const;
  int  get_height() const;

  void  step();

  Piece*  get_piece(int  x, int  y);

  Square*  get_current_square() const;

  void  get_pieces_that_are_in(int  x, int  y, int  w, int  h, std::vector<Piece*>  buf);

  void  process(Controller&  ctrl, int  x, int  y);

  void  load(const File*  f);

  void  render(Image&  dst) const;

};


}}


#endif




