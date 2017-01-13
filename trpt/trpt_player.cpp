#include"trpt_player.hpp"




namespace gmbb{
namespace trpt{


void
Player::
set_current_point(int  x, int  y)
{
  progressive_point.x = x<<Vector::shift_amount;
  progressive_point.y = y<<Vector::shift_amount;
}


void
Player::
set_destination_point(int  x, int  y)
{
  destination_point.x = x<<Vector::shift_amount;
  destination_point.y = y<<Vector::shift_amount;
}


Distance
Player::
update_willing_vector()
{
  auto  x0 = progressive_point.x>>Vector::shift_amount;
  auto  y0 = progressive_point.y>>Vector::shift_amount;
  auto  x1 = destination_point.x>>Vector::shift_amount;
  auto  y1 = destination_point.y>>Vector::shift_amount;

  auto  x_min = std::min(x0,x1);
  auto  x_max = std::max(x0,x1);
  auto  y_min = std::min(y0,y1);
  auto  y_max = std::max(y0,y1);

  Distance  x_distance(x_max-x_min);
  Distance  y_distance(y_max-y_min);

  int  distance_value;  

    if(x_distance.value < y_distance.value)
    {
      distance_value = y_distance.value;

      willing_vector.x = (x_distance.value<<Vector::shift_amount)/y_distance.value;
      willing_vector.y = (               1<<Vector::shift_amount)                 ;
    }

  else
    if(x_distance.value > y_distance.value)
    {
      distance_value = x_distance.value;

      willing_vector.x = (               1<<Vector::shift_amount)                 ;
      willing_vector.y = (y_distance.value<<Vector::shift_amount)/x_distance.value;
    }

  else
    {
      distance_value = x_distance.value;

      willing_vector.x = (1<<Vector::shift_amount);
      willing_vector.y = (1<<Vector::shift_amount);
    }


    if(progressive_point.x > destination_point.x){willing_vector.x = -willing_vector.x;}
    if(progressive_point.y > destination_point.y){willing_vector.y = -willing_vector.y;}


  return Distance(distance_value);
}


Point
Player::
get_current_point() const
{
  return Point(progressive_point.x>>Vector::shift_amount,
               progressive_point.y>>Vector::shift_amount);
}


template<typename  T>
T
clamp(T  v, T  max, T  min)
{
  return((v <= min)? min:
         (v >= max)? max: v);
}


void
Player::
step()
{
    if(!pausing)
    {
      update_willing_vector();

      auto  final_vector = forced_vector+inertial_vector;

      constexpr int  u = 2;

        if(willing_vector.x < 0)
        {
            if(final_vector.x > willing_vector.x)
            {
              final_vector.x += willing_vector.x/u;
            }
        }

      else
        if(willing_vector.x > 0)
        {
            if(final_vector.x < willing_vector.x)
            {
              final_vector.x += willing_vector.x/u;
            }
        }


        if(willing_vector.y < 0)
        {
            if(final_vector.y > willing_vector.y)
            {
              final_vector.y += willing_vector.y/u;
            }
        }

      else
        if(willing_vector.y > 0)
        {
            if(final_vector.y < willing_vector.y)
            {
              final_vector.y += willing_vector.y/u;
            }
        }


      progressive_point.x += final_vector.x;
      progressive_point.y += final_vector.y;

//      inertial_vector = final_vector;
    }
}


void
Player::
render(const Image&  src, Image&  dst) const
{
}


}}




