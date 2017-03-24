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

        if(p->test_flag(Piece::died_flag))
        {
            if(!p->own_task.callback)
            {
              piece_list.erase(now);

                if(master == p)
                {
                  master = nullptr;

                  return;
                }


              dead_piece_list.emplace_back(p);
            }
        }

      else
        if(p != master)
        {
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




