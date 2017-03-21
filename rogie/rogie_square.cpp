#include"rogie_square.hpp"
#include"rogie_piece.hpp"




Square::
Square():
current_piece(nullptr),
placed_item(nullptr)
{
}




Square*&
Square::
operator[](Direction  dir)
{
  return link[static_cast<int>(dir)];
}




void
Square::
clear()
{
    for(auto&  ln: link)
    {
      ln = nullptr;
    }


  kind = SquareKind::null;

  delete placed_item          ;
         placed_item = nullptr;

  current_piece = nullptr;

  passable = true;
}





