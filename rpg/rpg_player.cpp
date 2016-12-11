#include"rpg_player.hpp"
#include"rpg_core.hpp"
#include<cstring>




namespace gmbb{
namespace rpg{




Player::
Player():
face(0),
action_phase(0),
shape_phase(0),
interval_time(0),
next_time(0),
shapeshift(nullptr)
{
}




void
Player::
change_direction(int  d)
{
  direction = d;

  auto&  x = square_point.x;
  auto&  y = square_point.y;

    switch(d)
    {
  case(Direction::up   ): if(y                        ){next_square = &map->get(x  ,y-1);}break;
  case(Direction::left ): if(x                        ){next_square = &map->get(x-1,y  );}break;
  case(Direction::right): if(x < (map->get_width() -1)){next_square = &map->get(x+1,y  );}break;
  case(Direction::down ): if(y < (map->get_height()-1)){next_square = &map->get(x  ,y+1);}break;

  default:
      next_square = nullptr;
    }
}


void
Player::
change_face(int  f)
{
  face = f;
}


void
Player::
standby(SquareMap&  map_, int  dir, int  fac, int  x, int  y)
{
  map = &map_;

  change_direction(dir);
  change_face(fac);

  square_point.x = x;
  square_point.y = y;

  sprite_point.x = 24*x;
  sprite_point.y = 24*y;

  previous_square = nullptr;
  current_square = &map->get(x,y);
}


void
Player::
push_action(Action  action)
{
  action_q.push(action);
}


void
Player::
pop_action()
{
    if(action_q.size())
    {
      action_q.pop();
    }
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
            }


          postaction(*this);
        }


        if(shapeshift)
        {
          shapeshift(*this,sprite);
        }
    }
}


void
Player::
advance()
{
  previous_square = current_square              ;
                    current_square = next_square;

  auto&  x = square_point.x;
  auto&  y = square_point.y;

    switch(direction)
    {
  case(Direction::up   ): if(y                        ){next_square = &map->get(x  ,y-1);}break;
  case(Direction::left ): if(x                        ){next_square = &map->get(x-1,y  );}break;
  case(Direction::right): if(x < (map->get_width() -1)){next_square = &map->get(x+1,y  );}break;
  case(Direction::down ): if(y < (map->get_height()-1)){next_square = &map->get(x  ,y+1);}break;

  default:
      next_square = nullptr;
    }
}


const Square*
Player::
get_previous_square() const
{
  return previous_square;
}


const Square*
Player::
get_current_square() const
{
  return current_square;
}


const Square*
Player::
get_next_square() const
{
  return next_square;
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





