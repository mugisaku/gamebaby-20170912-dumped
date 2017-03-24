#include"rogie_piece.hpp"
#include"rogie_field.hpp"
#include"rogie_firearm.hpp"




const int  Piece::shield_max = 9999;
const int  Piece::oxygen_max =  999;
const int    Piece::life_max =  200;


gmbb::Image
Piece::
sprite_image;




Piece::
Piece(const char*  name_, std::initializer_list<Callback>  cbls):
name(name_),
flags(0),
current_square(nullptr),
current_field(nullptr),
direction(Direction::front),
shield_remaining(shield_max),
life_remaining(life_max),
oxygen_remaining(oxygen_max),
moving_cost(moving_cost_base),
armor_strength(0),
action_currency(0),
first_firearm(nullptr),
last_firearm(nullptr),
current_firearm(nullptr),
first_ammo(nullptr),
last_ammo(nullptr),
weapon_spec(&get_weapon_spec(WeaponKind::punch)),
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

                if(itm->kind == ItemKind::firearm)
                {
                  append(&itm->data.firearm);
                }


              return true;
            }
        }
    }


  return false;
}


void
Piece::
append(Firearm*  fa)
{
    if(!first_firearm)
    {
      first_firearm = fa;
       last_firearm = fa;
    }

  else
    {
      last_firearm->next = fa;
      last_firearm = fa;
    }


  current_firearm = fa;

  weapon_spec = &get_weapon_spec(fa->weapon_kind);
}


void
Piece::
link_with_square(Square&  sq)
{
    if(sq.current_piece)
    {
      printf("既に駒があります\n");

      throw;
    }


  unlink_with_square();

  current_square                =  &sq;
  current_square->current_piece = this;

  current_point = sq.point;
}


void
Piece::
unlink_with_square()
{
    if(current_square)
    {
      current_square->current_piece = nullptr;
      current_square                = nullptr;
    }
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

  rendering_src_base.x   = 0;
  rendering_src_offset.x = 0;
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
    if(test_flag(invisible_flag))
    {
      return;
    }


  auto  src_x = rendering_src_base.x+rendering_src_offset.x;
  auto  src_y = rendering_src_base.y+rendering_src_offset.y;

  auto  dst_x = x+rendering_dst_offset.x+(24*current_point.x)   ;
  auto  dst_y = y+rendering_dst_offset.y+(24*current_point.y)-24;

  sprite_image.transfer(src_x,
                        src_y,shape_reversing? -24:24,48,dst,dst_x,dst_y-4);
}


void
Piece::
render_data(gmbb::Image&  dst, int  x, int  y) const
{
  constexpr int  bar_height = 64;

  sprite_image.transfer(72,240,72,3,dst,x,y);

  y += 3;

    for(int  n = 0;  n < bar_height;  ++n)
    {
      sprite_image.transfer(72,243,72,1,dst,x,y+n);
    }


  int  h = ((bar_height<<16)/life_max*life_remaining)>>16;

  dst.fill_rectangle(3|8,x+24+6,y+bar_height-h,12,h);

  sprite_image.transfer(72,275,72,13,dst,x,y+bar_height);
}


void
Piece::
print() const
{
  auto&  pt = current_square->point;

  printf("[piece %s] %3d,%3d  %d %s %d\n",name,pt.x,pt.y,action_currency,own_task.callback? "O":"X",task_stack.size());
}


bool
Piece::
compare(Piece*  a, Piece*  b)
{
  return a->current_point.y < b->current_point.y;
}


void
Piece::
attack(Piece&  a, Piece&  b)
{
  int  n = ((a.weapon_spec->power<<16)/armor_strength_max*(armor_strength_max-b.armor_strength))>>16;

  int  res = b.life_remaining-n;

    if(res < 0)
    {
      res = 0;
    }


  b.life_remaining = res;

  b.push_task(damage);

    if(!res)
    {
      b.own_task = Task(disappear);
    }
}




