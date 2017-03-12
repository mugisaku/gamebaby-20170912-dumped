#include"rogie_square.hpp"
#include"rogie_piece.hpp"




Square::
Square():
reaching_cost(0)
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

  current_piece = nullptr;

  passable = true;
}





