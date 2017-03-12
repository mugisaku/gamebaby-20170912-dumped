#include"rogie_piece.hpp"
#include"rogie_field.hpp"
#include"rogie_basic_callback.hpp"




gmbb::Image
Piece::
sprite_image;




Piece::
Piece(bool  voluntary):
direction(Direction::front),
shield_remaining(100),
action_currency(0),
moving_cost_base(10),
task_kind(TaskKind::chase_hero),
voluntary_flag(voluntary)
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

           push_action(basic_callback::move_to_opposite_direction,moving_cost_base);
         }
    }
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
    if(voluntary_flag)
    {
        switch(task_kind)
        {
      case(TaskKind::chase_hero):
          chase_hero();
          break;
      case(TaskKind::runaway_from_hero):
          break;
        }
    }
}


void
Piece::
chase_hero()
{
  current_square->field->prepare_to_search();
  current_square->search_reaching_cost(this);
  current_square->search_distance(current_square->field->master);

  Direction  d;

  Square*  candidate = nullptr;

    for(int  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = current_square->link[i];

        if(ln)
        {
            if(!candidate ||
               ((ln->distance      < candidate->distance     ) ||
                (ln->reaching_cost < candidate->reaching_cost)))
            {
              candidate = ln;

              d = static_cast<Direction>(i);
            }
        }
    }


    if(candidate)
    {
        if(d == direction)
        {
          move_advance();
        }

      else
        {
          auto  l = get_left( direction);
          auto  r = get_right(direction);

          auto  l_dist = get_distance(direction,l);
          auto  r_dist = get_distance(direction,r);

            if(l_dist < r_dist){turn_left();}
          else                 {turn_right();}
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




