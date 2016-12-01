#include"gmbb_window.hpp"
#include<cstdlib>




namespace gmbb{




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

      obj->change_parent(*this,x,y);
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


  need_to_refresh();
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
          need_to_refresh();

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
          need_to_refresh();

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
          need_to_refresh();

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
          need_to_refresh();

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
render(Image&  dst)
{
    if(state != WindowState::hidden)
    {
      dst.frame(point.x,point.y,width,height);

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




