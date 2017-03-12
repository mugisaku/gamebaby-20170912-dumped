#include"rogie_square.hpp"
#include"rogie_piece.hpp"




void
Square::
subsearch_reaching_cost(Piece*  actor, int  cost)
{
    if(reaching_cost > cost)
    {
      reaching_cost = cost;

        for(auto  i = 0;  i < number_of_directions;  ++i)
        {
          auto  ln = link[i];

            if(ln && !ln->current_piece)
            {
              auto  d = static_cast<Direction>(i);

              ln->subsearch_reaching_cost(actor,reaching_cost+actor->get_moving_cost(d));
            }
        }
    }
}


void
Square::
search_reaching_cost(Piece*  actor)
{
  reaching_cost = 0;

    for(auto  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = link[i];

        if(ln && !ln->current_piece)
        {
          auto  d = static_cast<Direction>(i);

          ln->subsearch_reaching_cost(actor,actor->get_moving_cost(d));
        }
    }
}



void
Square::
subsearch_distance(Piece*  actor, int  dist)
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

              ln->subsearch_distance(actor,distance+1);
            }
        }
    }
}


void
Square::
search_distance(Piece*  actor)
{
  distance = 0;

    for(auto  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = link[i];

        if(ln && !ln->current_piece)
        {
          auto  d = static_cast<Direction>(i);

          ln->subsearch_distance(actor,1);
        }
    }
}




