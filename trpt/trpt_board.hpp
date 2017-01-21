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


class
Board
{
  int   width;
  int  height;

  std::list<Piece>  piece_list;

  std::vector<Square>  square_table;

public:
  static Image  bg_image;

  Board(int  w=0, int  h=0);

        Square&  get(int  x, int  y);
  const Square&  get_const(int  x, int  y) const;

  int  get_width() const;
  int  get_height() const;

  void  step();

  Piece*  get_piece(int  x, int  y);

  void  get_pieces_that_are_in(int  x, int  y, int  w, int  h, std::vector<Piece*>  buf);

  void  load(const File*  f);

  void  render(Image&  dst) const;

};


}}


#endif




