#include"rogie_field.hpp"




void
Field::
manage()
{
  int  n = 0;

    if(!master)
    {
      return;
    }


  auto   it = piece_list.begin();
  auto  end = piece_list.end();

    while(it != end)
    {
      auto  now = it++;

      auto  p = *now;

        if(p != master)
        {
            if(p->test_flag(Piece::died_flag))
            {
              piece_list.erase(now);

              p->current_square->current_piece = nullptr;
              p->current_square                = nullptr;

                if(master == p)
                {
                  master = nullptr;

                  return;
                }


              dead_piece_list.emplace_back(p);

              continue;
            }

          else
            if(p->action_currency > 0)
            {
              ++n;
            }


          p->step();
        }
    }


    if(!master)
    {
      return;
    }


    if(!n)
    {
      master->step();
    }
}




