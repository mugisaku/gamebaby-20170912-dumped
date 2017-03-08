#include"rogie_square.hpp"




Square::
Square()
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


  current_piece = nullptr;
}




