#include"trpt_piece.hpp"
#include"trpt_board.hpp"
#include"trpt_square.hpp"
#include"trpt_porter.hpp"




namespace gmbb{
namespace trpt{


void
Piece::
set_current_point(int  x, int  y)
{
  progressive_point.x = x<<Vector::shift_amount;
  progressive_point.y = y<<Vector::shift_amount;

  update_current_square();
}


void
Piece::
set_destination_point(int  x, int  y)
{
  destination_point.x = x<<Vector::shift_amount;
  destination_point.y = y<<Vector::shift_amount;

  update_willing_vector();
}


void
Piece::
update_current_square()
{
  auto  pt = get_current_point();

  current_square = &board->get((pt.x+12)/24,(pt.y+16)/24);
}


void
Piece::
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

    if(x_distance.value < y_distance.value)
    {
      distance.value = y_distance.value;

      willing_vector.x = (x_distance.value<<Vector::shift_amount)/y_distance.value;
      willing_vector.y = (               1<<Vector::shift_amount)                 ;
    }

  else
    if(x_distance.value > y_distance.value)
    {
      distance.value = x_distance.value;

      willing_vector.x = (               1<<Vector::shift_amount)                 ;
      willing_vector.y = (y_distance.value<<Vector::shift_amount)/x_distance.value;
    }

  else
    {
      distance.value = x_distance.value;

      willing_vector.x = (1<<Vector::shift_amount);
      willing_vector.y = (1<<Vector::shift_amount);
    }


    if(progressive_point.x > destination_point.x){willing_vector.x = -willing_vector.x;}
    if(progressive_point.y > destination_point.y){willing_vector.y = -willing_vector.y;}
}


Point
Piece::
get_current_point() const
{
  return Point(progressive_point.x>>Vector::shift_amount,
               progressive_point.y>>Vector::shift_amount);
}


void
Piece::
step()
{
    if(!pausing)
    {
        if(++animation_timer > 4)
        {
          animation_timer = 0;

            if(++animation_phase > 3)
            {
              animation_phase = 0;
            }
        }


      auto&  remain = distance.value;

      if(!remain)
      {
        pausing = true;

        return;
      }


      if((*porter)(ActionKind::move))
      {
          if(resistance > 0)
          {
            resistance -= porter->moving_capacity;

            return;
          }


        auto  v = willing_vector+forced_vector+inertial_vector;

        resistance = get_resistance(current_square->kind);

        progressive_point.x += v.x;
        progressive_point.y += v.y;

        --remain;
      }


      sync();
    }
}


void
Piece::
sync()
{
    if(linked_cursor)
    {
      *static_cast<Point*>(linked_cursor) = get_current_point();
    }


  update_current_square();
}


void
Piece::
render(const Image&  src, const Point&  offset, Image&  dst) const
{
  auto  pt = get_current_point();

  static const int  table[] = {0,1,0,2};

  src.transfer(24*table[animation_phase],0,24,32,dst,pt.x-offset.x,pt.y-offset.y);
}


}}




