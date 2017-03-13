#include"rogie_piece.hpp"
#include"rogie_field.hpp"
#include"rogie_basic_callback.hpp"




gmbb::Image
Piece::
sprite_image;




Piece::
Piece(uint32_t  flags_):
direction(Direction::front),
shield_remaining(100),
action_currency(0),
moving_cost_base(10),
flags(flags_)
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
  push_action(basic_callback::move_to_direction,moving_cost_base);
}


void
Piece::
turn_left()
{
  push_action(basic_callback::turn_left,moving_cost_base/3);
}


void
Piece::
turn_right()
{
  push_action(basic_callback::turn_right,moving_cost_base/3);
}


void
Piece::
change_direction(Direction  d)
{
  direction = d;

  set_shape_by_direction();
}


void
Piece::
use_weapon()
{
  push_action(basic_callback::punch,moving_cost_base);
}




int
Piece::
get_moving_cost(Direction  dir) const
{
  return (moving_cost_base/3)*get_distance(direction,dir)+(moving_cost_base);
}




void    Piece::set_flag(uint32_t  v){flags |=  v;}
void  Piece::unset_flag(uint32_t  v){flags &= ~v;}
bool   Piece::test_flag(uint32_t  v) const{return(flags&v);}




void
Piece::
push_task(Callback  cb)
{
    if(cb)
    {
      task_list.emplace_front(cb);
    }
}


void
Piece::
push_action(Callback  cb, int  consum)
{
    if(cb)
    {
      action_queue.emplace(Action{cb,consum});
    }
}


void
Piece::
push_context(Callback  cb)
{
    if(cb)
    {
      context_stack.emplace(cb);
    }
}


void
Piece::
pop_context()
{
    if(context_stack.size())
    {
      context_stack.pop();
    }
}


void
Piece::
step()
{
    if(context_stack.size())
    {
      auto&  bk = context_stack.top();

      bk.callback(bk,*this);

        if(!bk.callback)
        {
          context_stack.pop();
        }
    }

  else
    if(action_queue.size())
    {
      auto&  t = action_queue.front();

        if(!t.consumption || (action_currency >= 0))
        {
          action_currency -= t.consumption;

          context_stack.emplace(t.callback);

          action_queue.pop();
        }
    }

  else
    if(flags&voluntary_flag)
    {
      set_flag(taskseeking_flag);

      auto   it = task_list.begin();
      auto  end = task_list.end();

        while(it != end)
        {
          it->callback(*it,*this);

            if(!it->callback)
            {
              it = task_list.erase(it);
            }

          else
            {
              ++it;
            }


            if(!test_flag(taskseeking_flag))
            {
              break;
            }
        }
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




