#include"rpg_routine.hpp"




namespace gmbb{
namespace rpg{




void
move_up(Player&  pl)
{
  pl.point.y -= 2;

    if(++pl.action_phase >= 6)
    {
      pl.action_phase = 0;
    }
}


void
move_left(Player&  pl)
{
  pl.point.x -= 2;

    if(++pl.action_phase >= 6)
    {
      pl.action_phase = 0;
    }
}


void
move_right(Player&  pl)
{
  pl.point.x += 2;

    if(++pl.action_phase >= 6)
    {
      pl.action_phase = 0;
    }
}


void
move_down(Player&  pl)
{
  pl.point.y += 2;

    if(++pl.action_phase >= 6)
    {
      pl.action_phase = 0;
    }
}


void
shapeshift(const Player&  ply, Sprite&  spr)
{
  constexpr int  bases[] = {0,1,0,2};

  spr.source_point.x = (24*bases[(ply.action_counter.value>>2)&3])+4;
  spr.source_point.y = (40*ply.face)+4;
  spr.width  = 16;
  spr.height = 32;
  spr.point.x = ply.point.x+4;
  spr.point.y = ply.point.y+4+20;
}




}}




