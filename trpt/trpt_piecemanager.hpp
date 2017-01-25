#ifndef TRPT_PIECEMANAGER_HPP
#define TRPT_PIECEMANAGER_HPP


#include<list>
#include<vector>
#include"trpt_piece.hpp"


namespace gmbb{
namespace trpt{


class
PieceManager
{
public:
  static Image  sprite_image;

  std::vector<Piece*>  reserved_pieces;

  std::list<Piece*>  entrant_pieces;

  std::list<Piece*>::iterator  previous;
  std::list<Piece*>::iterator   current;

  Piece*  standby_piece;

  PieceManager(Board&  brd);
 ~PieceManager();
  

  Piece*  step();

  Piece*   ready();
  void  commit();
  void  pullback(Piece*  p=nullptr);
  void  pullback_previous_piece();

  Piece*  get_piece(int  x, int  y) const;

  Piece*  get_standby_piece() const;

  void  render(const Rectangle&  rect, Image&  dst) const;

};


}}


#endif




