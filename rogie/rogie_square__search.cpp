#include"rogie_square.hpp"
#include"rogie_piece.hpp"




void
Square::
subsearch(Piece*  actor, int  dist)
{
    if(distance > dist)
    {
      distance = dist;

        for(auto  i = 0;  i < number_of_directions;  ++i)
        {
          auto  ln = link[i];

            if(ln && !ln->current_piece)
            {
              auto  d = static_cast<Direction>(i);

              ln->subsearch(actor,distance+(is_diagonal(d)? 1333:1000));
            }
        }
    }
}


void
Square::
search(Piece*  actor)
{
  distance = 0;

    for(auto  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = link[i];

        if(ln && !ln->current_piece)
        {
          auto  d = static_cast<Direction>(i);

          ln->subsearch(actor,is_diagonal(d)? 1333:1000);
        }
    }
}




