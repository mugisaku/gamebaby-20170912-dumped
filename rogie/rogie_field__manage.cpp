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


    for(auto  p: piece_list)
    {
        if(p != master)
        {
//p->print();
            if(p->action_currency > 0)
            {
              ++n;
            }


          p->step();
        }
    }
//printf("****\n");


    if(!master)
    {
      return;
    }


    if(!n)
    {
      master->step();
    }
}




