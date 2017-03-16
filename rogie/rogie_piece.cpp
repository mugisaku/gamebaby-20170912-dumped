#include"rogie_piece.hpp"
#include"rogie_field.hpp"




gmbb::Image
Piece::
sprite_image;




Piece::
Piece(uint32_t  flags_):
flags(flags_),
direction(Direction::front),
shield_remaining(100),
moving_cost_base(10),
action_currency(0)
{
}




void
Piece::
set_shape_by_direction()
{
  rendering_src_base.y = 0;
  shape_reversing = false;

    switch(direction)
    {
  case(Direction::back_left):
      rendering_src_base.y = 4;
      break;
  case(Direction::back):
      rendering_src_base.y = 2;
      break;
  case(Direction::back_right):
      rendering_src_base.y = 4;
      shape_reversing = true;
      break;
  case(Direction::left):
      rendering_src_base.y = 1;
      break;
  case(Direction::right):
      rendering_src_base.y = 1;
      shape_reversing = true;
      break;
  case(Direction::front_left):
      rendering_src_base.y = 3;
      break;
  case(Direction::front):
      break;
  case(Direction::front_right):
      rendering_src_base.y = 3;
      shape_reversing = true;
      break;
    }


  rendering_src_base.y *= 48;
}


void
Piece::
add_offset_by_direction(int  n)
{
    switch(direction)
    {
  case(Direction::back_left):
      rendering_dst_offset.x += -n;
      rendering_dst_offset.y += -n;
      break;
  case(Direction::back):
      rendering_dst_offset.x +=  0;
      rendering_dst_offset.y += -n;
      break;
  case(Direction::back_right):
      rendering_dst_offset.x +=  n;
      rendering_dst_offset.y += -n;
      break;
  case(Direction::left):
      rendering_dst_offset.x += -n;
      rendering_dst_offset.y +=  0;
      break;
  case(Direction::right):
      rendering_dst_offset.x += n;
      rendering_dst_offset.y += 0;
      break;
  case(Direction::front_left):
      rendering_dst_offset.x += -n;
      rendering_dst_offset.y +=  n;
      break;
  case(Direction::front):
      rendering_dst_offset.x += 0;
      rendering_dst_offset.y += n;
      break;
  case(Direction::front_right):
      rendering_dst_offset.x += n;
      rendering_dst_offset.y += n;
      break;
    }
}




void    Piece::set_flag(uint32_t  v){flags |=  v;}
void  Piece::unset_flag(uint32_t  v){flags &= ~v;}
bool   Piece::test_flag(uint32_t  v) const{return(flags&v);}


bool
Piece::
consume_currency(int  v)
{
    if(action_currency >= 0)
    {
      action_currency -= v;

      return true;
    }


  return false;
}


void
Piece::
change_direction(Direction  d)
{
  direction = d;

  set_shape_by_direction();
}




int
Piece::
get_moving_cost(Direction  dir) const
{
  return (moving_cost_base/3)*get_distance(direction,dir)+(moving_cost_base);
}




void
Piece::
render(gmbb::Image&  dst, int  x, int  y) const
{
  auto  src_x = rendering_src_base.x+rendering_src_offset.x;
  auto  src_y = rendering_src_base.y+rendering_src_offset.y;

  auto  dst_x = x+rendering_dst_offset.x+(24*current_square->point.x)   ;
  auto  dst_y = y+rendering_dst_offset.y+(24*current_square->point.y)-24;

  sprite_image.transfer(src_x,
                        src_y,shape_reversing? -24:24,48,dst,dst_x,dst_y-4);
}


bool
Piece::
compare(Piece*  a, Piece*  b)
{
  return a->current_square->point.y < b->current_square->point.y;
}




