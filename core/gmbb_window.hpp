#ifndef GMBB_WINDOW_HPP
#define GMBB_WINDOW_HPP


#include"gmbb_rectangle.hpp"
#include"gmbb_image.hpp"


namespace gmbb{


enum class
WindowState
{
  hidden,

  full_opened,

  open_to_down,
  open_to_right,
  close_to_up,
  close_to_left,

};


struct Window;


using WindowCallback = void(*)(Window&  win, Image&  dst);


class
Window
{
  WindowState  state;

  Rectangle  rectangle;

  int   width_max;
  int  height_max;

  WindowCallback  callback;

  void*  userdata;

public:
  Window();
  Window(Rectangle&&  rect, WindowCallback cb, void*  data=nullptr);

  bool  operator==(WindowState  st) const;
  bool  operator!=(WindowState  st) const;

  void*     get_userdata(           ) const;
  void   change_userdata(void*  data)      ;

  WindowState  get_state() const;
  void  set_state(WindowState  st);

  void  update();

  void  render(Image&  dst);

};


}




#endif




