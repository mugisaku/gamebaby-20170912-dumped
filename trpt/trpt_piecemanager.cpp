#include"trpt_piecemanager.hpp"
#include"trpt_piece.hpp"
#include"trpt_board.hpp"
#include"trpt_square.hpp"




namespace gmbb{
namespace trpt{


Image  PieceManager::sprite_image;


PieceManager::
PieceManager(Board&  brd):
standby_piece(nullptr)
{
    for(int  n = 0;  n < 100;  ++n)
    {
      reserved_pieces.emplace_back(new Piece(brd));
    }


  previous = entrant_pieces.end();
  current  = entrant_pieces.begin();
}


PieceManager::
~PieceManager()
{
//    for(auto  p: reserved_pieces)
    {
    }
}




Piece*
PieceManager::
step()
{
    if(current != entrant_pieces.end())
    {
      previous = current;

      auto  p = *current++;

      auto  previous_square = p->current_square;

      p->step();

      auto  current_square = p->current_square;

        if((current_square != previous_square) && current_square->facility)
        {
          return p;
        }
    }

  else
    {
      current = entrant_pieces.begin();
    }


  return nullptr;
}




Piece*
PieceManager::
ready()
{
    if(!standby_piece && reserved_pieces.size())
    {
      standby_piece = reserved_pieces.back();

      reserved_pieces.pop_back();
    }


  return standby_piece;
}


void
PieceManager::
commit()
{
    if(standby_piece)
    {
      entrant_pieces.emplace_back(standby_piece);

      standby_piece = nullptr;
    }
}


void
PieceManager::
pullback(Piece*  p)
{
    if(!p)
    {
        if(standby_piece)
        {
          reserved_pieces.emplace_back(standby_piece)         ;
                                       standby_piece = nullptr;
        }
    }

  else
    {
      auto   it = entrant_pieces.begin();
      auto  end = entrant_pieces.end();

        while(it != end)
        {
            if(*it == p)
            {
              reserved_pieces.emplace_back(p);

              entrant_pieces.erase(it);

              previous = entrant_pieces.end();
              current  = entrant_pieces.begin();

              break;
            }


          ++it;
        }
    }
}


void
PieceManager::
pullback_previous_piece()
{
    if(previous != entrant_pieces.end())
    {
      reserved_pieces.emplace_back(*previous);

      previous = entrant_pieces.erase(previous);
    }
}


Piece*
PieceManager::
get_piece(int  x, int  y) const
{
  x -= 8;
  y -= 8;

  const int  x_end = (x+16);
  const int  y_end = (y+24);

    for(auto  p: entrant_pieces)
    {
      auto  pt = p->get_current_point();

        if((pt.x >= x    ) &&
           (pt.y >= y    ) &&
           (pt.x <  x_end) &&
           (pt.y <  y_end))
        {
//printf("%4d <= %4d < %4d\n",x,pt.x,x_end);
//printf("%4d <= %4d < %4d\n\n",y,pt.y,y_end);
          return p;
        }
    }


  return nullptr;
}


Piece*
PieceManager::
get_standby_piece() const
{
  return standby_piece;
}


void
PieceManager::
render(const Rectangle&  rect, Image&  dst) const
{
  const int  x_end = (rect.x+rect.w);
  const int  y_end = (rect.y+rect.h);

  static const int  table[] = {0,1,0,2};

    for(auto  p: entrant_pieces)
    {
      auto  pt = p->get_current_point();

        if((pt.x >= rect.x) &&
           (pt.y >= rect.y) &&
           (pt.x <  x_end) &&
           (pt.y <  y_end))
        {
          p->render(sprite_image,rect,dst);
        }
    }


    if(standby_piece)
    {
      auto  pt = standby_piece->get_current_point();

        if((pt.x >= rect.x) &&
           (pt.y >= rect.y) &&
           (pt.x <  x_end) &&
           (pt.y <  y_end))
        {
          standby_piece->render(sprite_image,rect,dst);
        }
    }
}




}}




