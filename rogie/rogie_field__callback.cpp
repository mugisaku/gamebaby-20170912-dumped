#include"rogie_field.hpp"




void
Field::
process_input(Context&  ctx)
{
  auto&  field = *static_cast<Field*>(ctx.caller);

    if(field.master->work_stack.size() == 1)
    {
        if(gmbb::env::ctrl.test_pressed(gmbb::p_flag))
        {
          field.master->push_action(Piece::use_weapon);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::left_flag))
        {
          field.master->push_action(Piece::turn_left);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::right_flag))
        {
          field.master->push_action(Piece::turn_right);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::up_flag))
        {
          field.master->push_action(Piece::move_to_direction);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::down_flag))
        {
          field.master->push_action(Piece::cancel_ready);
        }

      else
        if(gmbb::env::ctrl.test_pressed(gmbb::shift_flag))
        {
          field.master->push_action(Piece::change_weapon);
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
manage_pieces(Context&  ctx)
{
  auto&  field = *static_cast<Field*>(ctx.caller);

  bool  flag = false;

    for(auto  p: field.piece_list)
    {
      p->step();

      flag |= (p->work_stack.size() > 1);
    }


    if(!flag)
    {
      field.master->step();
    }
}




