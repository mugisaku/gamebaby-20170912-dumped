#include"rpg_player.hpp"
#include"core/gmbb_environment.hpp"
#include<cstring>




namespace gmbb{
namespace rpg{




Player::
Player():
face(0),
action_phase(0),
interval_time(0),
next_time(0),
shapeshift(nullptr)
{
}




void
Player::
push(Action  action)
{
  action_q.push(action);
}


void
Player::
step()
{
  auto  now = env::get_time();

    if(now >= next_time)
    {
        while(now >= next_time)
        {
          next_time += interval_time;

          preaction(*this);

            if(action_q.size())
            {
              action_q.front()(*this);

              action_counter.value += 1;

                if(!action_phase)
                {
                  action_q.pop();
                }
            }


          postaction(*this);
        }


        if(shapeshift)
        {
          shapeshift(*this,sprite);
        }
    }
}


const Point&
Player::
get_sprite_point() const
{
  return sprite_point;
}


const Point&
Player::
get_square_point() const
{
  return square_point;
}


}}





