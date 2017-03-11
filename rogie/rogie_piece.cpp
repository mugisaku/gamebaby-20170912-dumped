#include"rogie_piece.hpp"
#include"rogie_basic_callback.hpp"




gmbb::Image
Piece::
sprite_image;




Piece::
Piece():
direction(Direction::front),
shield_remaining(100),
action_currency(0),
moving_cost_base(10)
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


void
Piece::
move_advance()
{
  auto  ln = (*current_square)[direction];

    if(ln)
    {
         if(!ln->current_piece)
         {
           ln->current_piece = this;

           current_square->current_piece = nullptr;

           current_square = ln;

           push_context(basic_callback::move_to_direction);

           action_currency -= moving_cost_base;
         }
    }
}


void
Piece::
move_back()
{
  auto  dir = get_opposite(direction);

  auto  ln = (*current_square)[dir];

    if(ln)
    {
         if(!ln->current_piece)
         {
           ln->current_piece = this;

           current_square->current_piece = nullptr;

           current_square = ln;

           push_context(basic_callback::move_to_opposite_direction);

           action_currency -= moving_cost_base;
         }
    }
}


void
Piece::
turn_left()
{
    switch(direction)
    {
  case(Direction::back_left  ): direction = Direction::left       ;break;
  case(Direction::back       ): direction = Direction::back_left  ;break;
  case(Direction::back_right ): direction = Direction::back       ;break;
  case(Direction::left       ): direction = Direction::front_left ;break;
  case(Direction::right      ): direction = Direction::back_right ;break;
  case(Direction::front_left ): direction = Direction::front      ;break;
  case(Direction::front      ): direction = Direction::front_right;break;
  case(Direction::front_right): direction = Direction::right      ;break;
    }


  action_currency -= moving_cost_base/3;

  set_shape_by_direction();
}


void
Piece::
turn_right()
{
    switch(direction)
    {
  case(Direction::back_left  ): direction = Direction::back       ;break;
  case(Direction::back       ): direction = Direction::back_right ;break;
  case(Direction::back_right ): direction = Direction::right      ;break;
  case(Direction::left       ): direction = Direction::back_left  ;break;
  case(Direction::right      ): direction = Direction::front_right;break;
  case(Direction::front_left ): direction = Direction::left       ;break;
  case(Direction::front      ): direction = Direction::front_left ;break;
  case(Direction::front_right): direction = Direction::front      ;break;
    }


  action_currency -= moving_cost_base/3;

  set_shape_by_direction();
}


void
Piece::
use_weapon()
{
  action_currency -= moving_cost_base;

  push_context(basic_callback::punch);
}




int
Piece::
get_moving_cost(Direction  dir) const
{
  return (moving_cost_base/3)*get_distance(direction,dir)+(moving_cost_base);
}




void
Piece::
push_context(Callback  cb)
{
    if(cb)
    {
      context_stack.emplace_back(cb);

      cb(context_stack.back(),*this);
    }
}


void
Piece::
pop_context()
{
    if(context_stack.size())
    {
      context_stack.pop_back();
    }
}


void
Piece::
step()
{
    if(context_stack.size())
    {
      auto&  bk = context_stack.back();

      bk.callback(bk,*this);
    }
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




