#include"rpg_routine.hpp"
#include"rpg_core.hpp"




namespace gmbb{
namespace rpg{




Counter
move(Context&  ctx)
{
  ctx.counter.value += 1;

    if(ctx.counter.value >= 12)
    {
      ctx->reset_shape_counter();
      ctx->change_shape_phase(0);

        if(!core::debugging())
        {
          auto  prev = ctx->get_previous_square();
          auto  curr = ctx->get_current_square();

            if(prev){prev->get_event()(*prev,Trigger::end_to_leave);}
            if(curr){curr->get_event()(*curr,Trigger::end_to_enter);}
        }


      return 0;
    }

  else
    {
        if(ctx->advance_shape_counter(1) >= 3)
        {
          ctx->reset_shape_counter();
          ctx->advance_shape_phase(1);
        }
    }


  return ctx.counter;
}


Counter
move_up(Context&  ctx)
{
  ctx->move_sprite_point(0,-2);

  return move(ctx);
}


Counter
move_left(Context&  ctx)
{
  ctx->move_sprite_point(-2,0);

  return move(ctx);
}


Counter
move_right(Context&  ctx)
{
  ctx->move_sprite_point(2,0);

  return move(ctx);
}


Counter
move_down(Context&  ctx)
{
  ctx->move_sprite_point(0,2);

  return move(ctx);
}




Counter  turn_to_front(Context&  ctx){  ctx->turn_direction(Face::front);  return 0;}
Counter   turn_to_left(Context&  ctx){  ctx->turn_direction(Face::left);  return 0;}
Counter  turn_to_right(Context&  ctx){  ctx->turn_direction(Face::right);  return 0;}
Counter   turn_to_back(Context&  ctx){  ctx->turn_direction(Face::back);  return 0;}


Counter    set_quiet(Context&  ctx){  ctx->set_flag(quiet_flag);  return 0;}
Counter  unset_quiet(Context&  ctx){  ctx->unset_flag(quiet_flag);  return 0;}

Counter    set_facefixed(Context&  ctx){  ctx->set_flag(facefixed_flag);  return 0;}
Counter  unset_facefixed(Context&  ctx){  ctx->unset_flag(facefixed_flag);  return 0;}




Counter
rest(Context&  ctx)
{
  ctx.counter.value += 1;

    if(ctx.counter.value >= 8)
    {
      ctx.counter.value = 0;
    }


  return ctx.counter.value;
}


void
basic_play(Player&  pl, const Controller&  ctrl)
{
    if(!pl.test_whether_busy())
    {
        if(ctrl.test_pressed(p_flag))
        {
          auto  next = pl.get_next_square();

            if(next)
            {
              next->get_event()(*next,Trigger::press);
            }


         return;
       }

      else
        if(ctrl.test_pressing(up_flag))
        {
          pl.change_direction(Direction::up);

            if(!pl.test_flag(facefixed_flag))
            {
              pl.change_face(Face::back);
            }


            if(!core::debugging())
            {
              auto  next = pl.get_next_square();

                if(!next || !next->is_enterable())
                {
                  return;
                }
            }


          pl.move_square_point(0,-1);

          pl.push_action({move_up});
        }

      else
        if(ctrl.test_pressing(left_flag))
        {
          pl.change_direction(Direction::left);

            if(!pl.test_flag(facefixed_flag))
            {
              pl.change_face(Face::left);
            }


            if(!core::debugging())
            {
              auto  next = pl.get_next_square();

                if(!next || !next->is_enterable())
                {
                  return;
                }
            }


          pl.move_square_point(-1,0);

          pl.push_action({move_left});
        }

      else
        if(ctrl.test_pressing(right_flag))
        {
          pl.change_direction(Direction::right);

            if(!pl.test_flag(facefixed_flag))
            {
              pl.change_face(Face::right);
            }


            if(!core::debugging())
            {
              auto  next = pl.get_next_square();

                if(!next || !next->is_enterable())
                {
                  return;
                }
            }


          pl.move_square_point(1,0);

          pl.push_action({move_right});
        }

      else
        if(ctrl.test_pressing(down_flag))
        {
          pl.change_direction(Direction::down);

            if(!pl.test_flag(facefixed_flag))
            {
              pl.change_face(Face::front);
            }


            if(!core::debugging())
            {
              auto  next = pl.get_next_square();

                if(!next || !next->is_enterable())
                {
                  return;
                }
            }


          pl.move_square_point(0,1);

          pl.push_action({move_down});
        }

      else
        {
          return;
        }


      pl.advance();

        if(!core::debugging())
        {
          auto  prev = pl.get_previous_square();
          auto  curr = pl.get_current_square();

            if(prev){prev->get_event()(*prev,Trigger::begin_to_leave);}
            if(curr){curr->get_event()(*curr,Trigger::begin_to_enter);}
        }
    }
}


void
shapeshift(const Player&  ply, Sprite&  spr)
{
  constexpr int  x_bases[] = {0,1,0,2};
  constexpr int  y_bases[] = {0,1,1,2};

  int  x_base = ply.test_flag(quiet_flag)? 0:x_bases[ply.get_shape_phase()];

  spr.source_point.x = (24*x_base);
  spr.source_point.y = (40*y_bases[ply.get_face()]);
  spr.width  =  24;
  spr.height =  40;
  spr.point.x = ply.get_sprite_point().x;
  spr.point.y = ply.get_sprite_point().y-24;

    if(ply.get_face() == Face::right)
    {
      spr.width *= -1;
    }
}




}}




