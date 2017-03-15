#include"gmbb_window.hpp"
#include<cstdlib>




namespace gmbb{




Window::
Window():
state(WindowState::hidden),
callback(nullptr),
userdata(nullptr)
{
}


Window::
Window(Rectangle&&  rect, WindowCallback cb, void*  data):
width_max(rect.w),
height_max(rect.h),
rectangle(rect),
state(WindowState::full_opened),
callback(cb),
userdata(data)
{
}




bool  Window::operator==(WindowState  st) const{return state == st;}
bool  Window::operator!=(WindowState  st) const{return state != st;}


void*  Window::get_userdata() const{return userdata;}
void   Window::change_userdata(void*  data){userdata = data;}


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
      rectangle.w = width_max;
      rectangle.h =         1;
      break;
  case(WindowState::close_to_left):
  case(WindowState::close_to_up):
  case(WindowState::full_opened):
      rectangle.w = width_max;
      rectangle.h = height_max;
      break;
  case(WindowState::open_to_right):
      rectangle.w =          1;
      rectangle.h = height_max;
      break;
    }
}


void
Window::
update()
{
    switch(state)
    {
  case(WindowState::hidden):
  case(WindowState::full_opened):
      break;
  case(WindowState::open_to_right):
        if(rectangle.w < width_max)
        {
          ++rectangle.w;

            if(rectangle.w == width_max)
            {
              state = WindowState::full_opened;
            }
        }
      break;
  case(WindowState::close_to_left):
        if(rectangle.w > 1)
        {
          --rectangle.w;

            if(rectangle.w == 1)
            {
              state = WindowState::hidden;
            }
        }
      break;
  case(WindowState::open_to_down):
        if(rectangle.h < height_max)
        {
          ++rectangle.h;

            if(rectangle.h == height_max)
            {
              state = WindowState::full_opened;
            }
        }
      break;
  case(WindowState::close_to_up):
        if(rectangle.h > 1)
        {
          --rectangle.h;

            if(rectangle.h == 1)
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
      dst.frame(rectangle.x,rectangle.y,rectangle.w,rectangle.h);

        if(state == WindowState::full_opened)
        {
            if(callback)
            {
              callback(*this,dst);
            }
        }
    }
}


}




