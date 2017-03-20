#include"rogie_piece.hpp"
#include"rogie_field.hpp"




gmbb::Image
Piece::
sprite_image;




Piece::
Piece(std::initializer_list<Callback>  cbls):
flags(0),
direction(Direction::front),
shield_remaining(shield_max),
life_remaining(life_max),
oxygen_remaining(oxygen_max),
moving_cost_base(10),
action_currency(0),
current_firearm(nullptr),
callback_list(cbls)
{
    for(auto&  itm: belongings_table)
    {
      itm = nullptr;
    }
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


bool
Piece::
append_item(Item*  new_item)
{
    if(new_item)
    {
        for(auto&  itm: belongings_table)
        {
            if(!itm)
            {
              itm = new_item;

                if((itm->kind == ItemKind::firearm) && !current_firearm)
                {
                  current_firearm = &itm->data.firearm;
                }


              return true;
            }
        }
    }


  return false;
}


void    Piece::set_flag(uint32_t  v){flags |=  v;}
void  Piece::unset_flag(uint32_t  v){flags &= ~v;}
bool   Piece::test_flag(uint32_t  v) const{return(flags&v);}


void
Piece::
change_direction(Direction  d)
{
  direction = d;

  set_shape_by_direction();

    if(test_flag(readied_flag))
    {
      rendering_src_base.x   = 24*3;
      rendering_src_offset.x =    0;
    }

  else
    {
      rendering_src_base.x   = 0;
      rendering_src_offset.x = 0;
    }
}




int
Piece::
get_moving_cost(Direction  dir) const
{
  return (moving_cost_base/3)*get_distance(direction,dir)+(moving_cost_base);
}




const Task&  Piece::get_own_task() const{return own_task;}
const std::stack<Task>&  Piece::get_task_stack() const{return task_stack;}


const Firearm*  Piece::get_current_firearm() const{return current_firearm;}


void
Piece::
push_task(TaskCallback  cb)
{
  task_stack.emplace(cb);
}




void
Piece::
step()
{
    if(task_stack.size())
    {
      auto&  tsk = task_stack.top();

      tsk.callback(tsk,this);

        if(!tsk.callback)
        {
          task_stack.pop();
        }
    }

  else
    if(own_task.callback)
    {
      own_task.callback(own_task,this);
    }

  else
    if(test_flag(master_flag))
    {
      play();
    }

  else
    {
      autoplay();
    }
}


void
Piece::
play()
{
       if(gmbb::env::ctrl.test_pressed(gmbb::p_flag    )){own_task = Task(       use_weapon);}
  else if(gmbb::env::ctrl.test_pressed(gmbb::left_flag )){own_task = Task(        turn_left);}
  else if(gmbb::env::ctrl.test_pressed(gmbb::right_flag)){own_task = Task(       turn_right);}
  else if(gmbb::env::ctrl.test_pressed(gmbb::up_flag   )){own_task = Task(move_to_direction);}
  else if(gmbb::env::ctrl.test_pressed(gmbb::down_flag )){own_task = Task(     cancel_ready);}
  else if(gmbb::env::ctrl.test_pressed(gmbb::shift_flag)){own_task = Task(    change_weapon);}


  auto&  a = action_currency;

    if(a < 0)
    {
        for(auto  p:  current_field->piece_list)
        {
            if(p != this)
            {
              p->action_currency += -a;
            }
        }


      a = 0;
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




