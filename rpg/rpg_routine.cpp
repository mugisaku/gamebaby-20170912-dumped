#include"rpg_routine.hpp"
#include"rpg_core.hpp"




namespace gmbb{
namespace rpg{




void
move(Player&  pl)
{
  pl.action_counter.value += 1;

    if(pl.action_counter.value >= 12)
    {
      pl.action_counter.value = 0;
      pl.shape_counter.value  = 0;
      pl.shape_phase          = 0;

      pl.pop_action();


      auto  prev = pl.get_previous_square();
      auto  curr = pl.get_current_square();

        if(prev){prev->get_event()(Trigger::end_to_leave);}
        if(curr){curr->get_event()(Trigger::end_to_enter);}
    }

  else
    {
      pl.shape_counter.value += 1;

        if(pl.shape_counter.value >= 3)
        {
          pl.shape_counter.value  = 0;
          pl.shape_phase         += 1;
        }
    }
}


void
move_up(Player&  pl)
{
  pl.sprite_point.y -= 2;

  move(pl);
}


void
move_left(Player&  pl)
{
  pl.sprite_point.x -= 2;

  move(pl);
}


void
move_right(Player&  pl)
{
  pl.sprite_point.x += 2;

  move(pl);
}


void
move_down(Player&  pl)
{
  pl.sprite_point.y += 2;

  move(pl);
}


void
walk(Player&  pl, const Controller&  ctrl)
{
    if(pl.action_q.empty())
    {
        if(ctrl.test_pressing(p_flag))
        {
          auto  next = pl.get_next_square();

            if(next)
            {
              next->get_event()(Trigger::press);
            }


         return;
       }

      else
        if(ctrl.test_pressing(up_flag))
        {
          pl.change_direction(Direction::up);
          pl.change_face(Face::back);

            if(!core::debugging())
            {
              auto  next = pl.get_next_square();

                if(!next || !next->is_enterable())
                {
                  return;
                }
            }


          pl.square_point.y -= 1;

          pl.push_action(move_up);
        }

      else
        if(ctrl.test_pressing(left_flag))
        {
          pl.change_direction(Direction::left);
          pl.change_face(Face::left);

            if(!core::debugging())
            {
              auto  next = pl.get_next_square();

                if(!next || !next->is_enterable())
                {
                  return;
                }
            }


          pl.square_point.x -= 1;

          pl.push_action(move_left);
        }

      else
        if(ctrl.test_pressing(right_flag))
        {
          pl.change_direction(Direction::right);
          pl.change_face(Face::right);

            if(!core::debugging())
            {
              auto  next = pl.get_next_square();

                if(!next || !next->is_enterable())
                {
                  return;
                }
            }


          pl.square_point.x += 1;

          pl.push_action(move_right);
        }

      else
        if(ctrl.test_pressing(down_flag))
        {
          pl.change_direction(Direction::down);
          pl.change_face(Face::front);

            if(!core::debugging())
            {
              auto  next = pl.get_next_square();

                if(!next || !next->is_enterable())
                {
                  return;
                }
            }


          pl.square_point.y += 1;

          pl.push_action(move_down);
        }

      else
        {
          return;
        }


      pl.advance();

      auto  prev = pl.get_previous_square();
      auto  curr = pl.get_current_square();

        if(prev){prev->get_event()(Trigger::begin_to_leave);}
        if(curr){curr->get_event()(Trigger::begin_to_enter);}
    }
}


void
shapeshift(const Player&  ply, Sprite&  spr)
{
  constexpr int  x_bases[] = {0,1,0,2};
  constexpr int  y_bases[] = {0,1,1,2};

  spr.source_point.x = (24*x_bases[ply.shape_phase]);
  spr.source_point.y = (40*y_bases[ply.face]);
  spr.width  =  24;
  spr.height =  40;
  spr.point.x = ply.get_sprite_point().x;
  spr.point.y = ply.get_sprite_point().y-24;

    if(ply.face == Face::right)
    {
      spr.width *= -1;
    }
}




}}




