#include"gmbb_player.hpp"
#include"gmbb_core.hpp"
#include<cstring>




namespace gmbb{




Player::
Player():
face(0),
phase(0),
last_time(0)
{
}




void
Player::
process(Controller&  ctrl)
{
    if(ctrl.test_pressing(keyflag::up))
    {
      point.y -= 1;
    }

  else
    if(ctrl.test_pressing(keyflag::left))
    {
      point.x -= 1;
    }

  else
    if(ctrl.test_pressing(keyflag::right))
    {
      point.x += 1;
    }

  else
    if(ctrl.test_pressing(keyflag::down))
    {
      point.y += 1;
    }
}


void
Player::
step()
{
  static uint32_t  last;

  auto  now = get_time();

    if(now >= last+200)
    {
      last = now;

      phase += 1;

        if(phase >= 4)
        {
          phase = 0;
        }
    }


  constexpr int  bases[] = {0,1,0,2};

    if(sprite)
    {
      sprite->transfer(source_point.x+(width*bases[phase]),source_point.y,width,height,dst,point.x,point.y);
    }
}



}





