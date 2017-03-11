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





void
Square::
subsearch(Piece*  actor, int  cost)
{
    if(reaching_cost > cost)
    {
      reaching_cost = cost;

        for(auto  i = 0;  i < number_of_directions;  ++i)
        {
          auto  ln = link[i];

            if(ln)
            {
              auto  d = static_cast<Direction>(i);

              ln->subsearch(actor,reaching_cost+actor->get_moving_cost(d));
            }
        }
    }
}


void
Square::
search(Piece*  actor)
{
  reaching_cost = 0;

    for(auto  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = link[i];

        if(ln)
        {
          auto  d = static_cast<Direction>(i);

          ln->subsearch(actor,actor->get_moving_cost(d));
        }
    }
}




