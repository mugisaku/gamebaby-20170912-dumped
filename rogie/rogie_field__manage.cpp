#include"rogie_field.hpp"




void
Field::
manage()
{
  int  n = 0;

    for(auto  p: piece_list)
    {
//auto&  mgr = p->get_task_manager();

//printf("q%6d st%6d \n",mgr.get_queue().size(),mgr.get_stack().size());

        if(p != master)
        {
            if(p->action_currency > 0)
            {
              ++n;
            }


          p->step();
        }
    }


    if(!n)
    {
      master->step();
    }
}




