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
        if(ctrl.test_pressing(up_flag))
        {
          pl.face = Face::back;

            if(!core::debugging())
            {
              auto&  sqpt = pl.square_point;

              auto&  sq = core::get_squaremap().get(sqpt.x,sqpt.y-1);

                if(!sq.is_enterable())
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
          pl.face = Face::left;

            if(!core::debugging())
            {
              auto&  sqpt = pl.square_point;

              auto&  sq = core::get_squaremap().get(sqpt.x-1,sqpt.y);

                if(!sq.is_enterable())
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
          pl.face = Face::right;

            if(!core::debugging())
            {
              auto&  sqpt = pl.square_point;

              auto&  sq = core::get_squaremap().get(sqpt.x+1,sqpt.y);

                if(!sq.is_enterable())
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
          pl.face = Face::front;

            if(!core::debugging())
            {
              auto&  sqpt = pl.square_point;

              auto&  sq = core::get_squaremap().get(sqpt.x,sqpt.y+1);

                if(!sq.is_enterable())
                {
                  return;
                }
            }


          pl.square_point.y += 1;

          pl.push_action(move_down);
        }
    }
}


void
shapeshift(const Player&  ply, Sprite&  spr)
{
  constexpr int  bases[] = {0,1,0,2};

  spr.source_point.x = (24*bases[ply.shape_phase])+4;
  spr.source_point.y = (40*ply.face)+4;
  spr.width  = 16;
  spr.height = 32;
  spr.point.x = ply.get_sprite_point().x+4;
  spr.point.y = ply.get_sprite_point().y-12;
}




}}




