#include"rpg_routine.hpp"




namespace gmbb{
namespace rpg{




/*
Garden  garden;
Player  player;


void
move_up(rpg::Player&  pl)
{
  pl.point.y -= 2;

    if(++pl.action_phase >= 6)
    {
      pl.action_phase = 0;
    }
}


void
move_left(rpg::Player&  pl)
{
  pl.point.x -= 2;

    if(++pl.action_phase >= 6)
    {
      pl.action_phase = 0;
    }
}


void
move_right(rpg::Player&  pl)
{
  pl.point.x += 2;

    if(++pl.action_phase >= 6)
    {
      pl.action_phase = 0;
    }
}


void
move_down(rpg::Player&  pl)
{
  pl.point.y += 2;

    if(++pl.action_phase >= 6)
    {
      pl.action_phase = 0;
    }
}


void
operate_player()
{
    if(player.action_q.size())
    {
      return;
    }


    if(ctrl.test_pressing(up_flag))
    {
      player.face = rpg::Face::back;

      player.push(move_up);
    }

  else
    if(ctrl.test_pressing(left_flag))
    {
      player.face = rpg::Face::left;

      player.push(move_left);
    }

  else
    if(ctrl.test_pressing(right_flag))
    {
      player.face = rpg::Face::right;

      player.push(move_right);
    }

  else
    if(ctrl.test_pressing(down_flag))
    {
      player.face = rpg::Face::front;

      player.push(move_down);
    }
}


void
shapeshift(const rpg::Player&  ply, Sprite&  spr)
{
  constexpr int  bases[] = {0,1,0,2};

  spr.source_point.x = (24*bases[(ply.action_counter.value>>2)&3])+4;
  spr.source_point.y = (40*ply.face)+4;
  spr.width  = 16;
  spr.height = 32;
  spr.point.x = ply.point.x+4;
  spr.point.y = ply.point.y+4+20;
}




  player.sprite.reset(&chr_img,0,0,24,32);

  player.shapeshift = shapeshift;

  player.interval_time = 40;

  garden.join(player.sprite);
*/


}}




