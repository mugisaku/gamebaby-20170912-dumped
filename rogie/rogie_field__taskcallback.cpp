#include"rogie_field.hpp"




namespace{
Field&
get(Task&  tsk)
{
  return *static_cast<Field*>(tsk.get_manager()->get_owner());
}
}


void
Field::
process_input(Task&  tsk)
{
  auto&  field = get(tsk);

  auto&  q = field.master->get_task_manager().get_context_queue();

    if(q.empty())
    {
        if(gmbb::env::ctrl.test_pressed(gmbb::p_flag))
        {
          field.master->get_task_manager().push(Piece::use_weapon);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::left_flag))
        {
          field.master->get_task_manager().push(Piece::turn_left);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::right_flag))
        {
          field.master->get_task_manager().push(Piece::turn_right);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::up_flag))
        {
          field.master->get_task_manager().push(Piece::move_to_direction);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::down_flag))
        {
          field.master->get_task_manager().push(Piece::cancel_ready);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::shift_flag))
        {
          field.master->get_task_manager().push(Piece::change_weapon);
        }


      auto&  a = field.master->action_currency;

        if(a < 0)
        {
            for(auto  p:  field.piece_list)
            {
                if(p != field.master)
                {
                  p->action_currency += -a;
                }
            }


          a = 0;
        }
    }
}


void
Field::
manage_pieces(Task&  tsk)
{
  auto&  field = get(tsk);

  int  n = 0;

    for(auto  p: field.piece_list)
    {
        if(p != field.master)
        {
          p->step();

            if(p->action_currency > 0)
            {
              ++n;
            }
        }
    }


    if(!n)
    {
      field.master->step();
    }
}




