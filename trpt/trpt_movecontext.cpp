#include"trpt_movecontext.hpp"
#include<cstdlib>
#include<algorithm>




MoveContext::
MoveContext(point_t  x, point_t  y):
x_point(x),
y_point(y),
distance(0)
{
}




MoveContext::
operator bool() const
{
  return distance;
}


void
MoveContext::
set_start(point_t  x, point_t  y)
{
  x_point = x;
  y_point = y;

  distance = 0;
}


void
MoveContext::
set_destination(point_t  x, point_t  y)
{
  x_hot_point = x_point<<shift_amount;
  y_hot_point = y_point<<shift_amount;
  x_dst_point = x      <<shift_amount;
  y_dst_point = y      <<shift_amount;


  auto  x_min = std::min(x_point,x);
  auto  x_max = std::max(x_point,x);
  auto  y_min = std::min(y_point,y);
  auto  y_max = std::max(y_point,y);

  int  x_distance = (x_max-x_min);
  int  y_distance = (y_max-y_min);

    if(x_distance < y_distance)
    {
      distance = y_distance;

      x_add_amount = (x_distance<<shift_amount)/y_distance;
      y_add_amount = (         1<<shift_amount)           ;
    }

  else
    if(x_distance > y_distance)
    {
      distance = x_distance;

      x_add_amount = (         1<<shift_amount)           ;
      y_add_amount = (y_distance<<shift_amount)/x_distance;
    }

  else
    {
      distance = x_distance;

      x_add_amount = (1<<shift_amount);
      y_add_amount = (1<<shift_amount);
    }


    if(x_hot_point > x_dst_point){x_add_amount = -x_add_amount;}
    if(y_hot_point > y_dst_point){y_add_amount = -y_add_amount;}
}


point_t  MoveContext::get_x() const{return x_point;}
point_t  MoveContext::get_y() const{return y_point;}


void
MoveContext::
step()
{
    if(distance)
    {
      --distance;

      x_hot_point += x_add_amount;
      y_hot_point += y_add_amount;

      x_point = x_hot_point>>shift_amount;
      y_point = y_hot_point>>shift_amount;
    }
}


void
MoveContext::
finish()
{
  x_point = x_dst_point>>shift_amount;
  y_point = y_dst_point>>shift_amount;

  distance = 0;
}




