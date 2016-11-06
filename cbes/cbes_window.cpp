#include"cbes_window.hpp"
#include"cbes_screen.hpp"
#include<cstdlib>




namespace cbes{




Window::
Window():
state(WindowState::hidden),
content(nullptr)
{
}


Window::
Window(int  w, int  h):
width_max(w),
height_max(h),
state(WindowState::full_opened),
content(nullptr)
{
  change_width(w);
  change_height(h);
}




bool  Window::operator==(WindowState  st) const{return state == st;}
bool  Window::operator!=(WindowState  st) const{return state != st;}


Object*  Window::get_content() const{return content;}


void
Window::
change_content(Object*  obj, int  x, int  y)
{
    if(obj)
    {
      content = obj;

      obj->change_parent(this,x,y);
    }
}


WindowState
Window::
get_state() const
{
  return state;
}


void
Window::
set_state(WindowState  st)
{
  state = st;

    switch(state)
    {
  case(WindowState::hidden):
      break;
  case(WindowState::open_to_down):
      change_width(width_max);
      change_height(1);
      break;
  case(WindowState::close_to_left):
  case(WindowState::close_to_up):
  case(WindowState::full_opened):
      change_width(width_max);
      change_height(height_max);
      break;
  case(WindowState::open_to_right):
      change_width(1);
      change_height(height_max);
      break;
    }


  screen.need_to_refresh();
}


void
Window::
reframe(CharacterTable&  dst)
{
  dst.get_character(point.x        ,point.y).unicode = 0xE100;
  dst.get_character(point.x+width-1,point.y).unicode = 0xE102;
  dst.get_character(point.x        ,point.y+height-1).unicode = 0xE106;
  dst.get_character(point.x+width-1,point.y+height-1).unicode = 0xE108;

    for(int  x = 1;  x < (width-1);  ++x)
    {
      dst.get_character(point.x+x,point.y         ).unicode = 0xE101;
      dst.get_character(point.x+x,point.y+height-1).unicode = 0xE107;
    }


    for(int  y = 1;  y < (height-1);  ++y)
    {
      dst.get_character(point.x        ,point.y+y).unicode = 0xE103;
      dst.get_character(point.x+width-1,point.y+y).unicode = 0xE105;
    }
}


void
Window::
fill(CharacterTable&  dst)
{
    for(int  y = 1;  y < (height-1);  ++y){
    for(int  x = 1;  x < ( width-1);  ++x){
      dst.get_character(point.x+x,point.y+y).unicode = space_code;
    }}
}


void
Window::
update()
{
    switch(state)
    {
  case(WindowState::hidden):
  case(WindowState::full_opened):
        if(content)
        {
          content->update();
        }
      break;
  case(WindowState::open_to_right):
        if(width < width_max)
        {
          screen.need_to_refresh();

          ++width;

            if(width == width_max)
            {
              state = WindowState::full_opened;
            }
        }
      break;
  case(WindowState::close_to_left):
        if(width > 1)
        {
          screen.need_to_refresh();

          --width;

            if(width == 1)
            {
              state = WindowState::hidden;
            }
        }
      break;
  case(WindowState::open_to_down):
        if(height < height_max)
        {
          screen.need_to_refresh();

          ++height;

            if(height == height_max)
            {
              state = WindowState::full_opened;
            }
        }
      break;
  case(WindowState::close_to_up):
        if(height > 1)
        {
          screen.need_to_refresh();

          --height;

            if(height == 1)
            {
              state = WindowState::hidden;
            }
        }
      break;
    }
}


void
Window::
render(CharacterTable&  dst)
{
    if(state != WindowState::hidden)
    {
      reframe(dst);
         fill(dst);

        if(state == WindowState::full_opened)
        {
            if(content)
            {
              content->render(dst);
            }
        }
    }
}


}




