#include"rpg_player.hpp"
#include"rpg_core.hpp"
#include<cstring>




namespace gmbb{
namespace rpg{




Player::
Player():
flags(0),
face(0),
action_phase(0),
shape_phase(0),
interval_time(0),
next_time(0),
preaction(nullptr),
postaction(nullptr),
play(nullptr),
shapeshift(nullptr)
{
}




void
Player::
operator()(const Controller&  ctrl)
{
  step();

    if(play)
    {
      play(*this,ctrl);
    }
}


void    Player::set_flag(int  v){flags |=  v;}
void  Player::unset_flag(int  v){flags &= ~v;}
bool   Player::test_flag(int  v) const{return flags&v;}


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
turn_direction(int  f)
{
  int  d = Direction::unknown;

    switch(f)
    {
  case(Face::front): d = Direction::down;break;
  case(Face::left ): d = Direction::left;break;
  case(Face::right): d = Direction::right;break;
  case(Face::back ): d = Direction::up;break;
    }


  change_face(f);
  change_direction(d);
}


int  Player::get_face() const{return face;}
int  Player::get_direction() const{return direction;}


void
Player::
move_square_point(int  x, int  y)
{
  square_point.x += x;
  square_point.y += y;
}


void
Player::
move_sprite_point(int  x, int  y)
{
  sprite_point.x += x;
  sprite_point.y += y;
}


bool
Player::
test_whether_busy() const
{
  return action_q.size();
}


void  Player::change_shape_phase(int  v){shape_phase  = v;}
int  Player::advance_shape_phase(int  v){return shape_phase += v;}
int      Player::get_shape_phase() const{return shape_phase;}


void              Player::reset_shape_counter(){shape_counter.value = 0;}
const Counter&  Player::advance_shape_counter(int  v){  shape_counter.value += v;  return shape_counter;}
const Counter&      Player::get_shape_counter() const{return shape_counter;}


void  Player::change_interval_time(uint32_t  v){interval_time = v;}
uint32_t  Player::get_interval_time() const{return interval_time;}


void  Player::change_play(Play  cb){play = cb;}
void  Player::change_shapeshift(ShapeShift  cb){shapeshift = cb;}


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
push_action(std::initializer_list<Action>  ls)
{
    for(auto  action: ls)
    {
      action_q.push(action);
    }
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
      Context  ctx(*this,action_counter);

        while(now >= next_time)
        {
          next_time += interval_time;

            if(preaction)
            {
              preaction(ctx);
            }


            if(action_q.size())
            {
              action_counter = action_q.front()(ctx);

                if(!action_counter)
                {
                  action_q.pop();
                }
            }


            if(postaction)
            {
              postaction(ctx);
            }
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


Square*
Player::
get_previous_square() const
{
  return previous_square;
}


Square*
Player::
get_current_square() const
{
  return current_square;
}


Square*
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


Sprite&
Player::
get_sprite()
{
  return sprite;
}


}}





