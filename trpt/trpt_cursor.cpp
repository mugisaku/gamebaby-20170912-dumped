#include"trpt_cursor.hpp"
#include"trpt_piece.hpp"




namespace gmbb{
namespace trpt{


void
Cursor::
link(Piece&  p)
{
  p.linked_cursor = this;
  linked_piece    = &p;
}


void
Cursor::
unlink()
{
    if(linked_piece)
    {
      linked_piece->linked_cursor = nullptr;
      linked_piece                = nullptr;
    }
}


}}




