#include"rogie_field.hpp"




void
Field::
process_input(Context&  ctx)
{
  auto&  field = *static_cast<Field*>(ctx.caller);

//    if(field.master->work_stack.empty())
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

  field.master->step();

    for(auto  p: field.piece_list)
    {
      p->step();
    }
}




