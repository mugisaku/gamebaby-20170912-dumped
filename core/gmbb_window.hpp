#ifndef GMBB_WINDOW_HPP
#define GMBB_WINDOW_HPP


#include"gmbb_object.hpp"


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


class
Window: public Object
{
protected:
  WindowState  state;

  int   width_max;
  int  height_max;

  Object*  content;

public:
  Window();
  Window(int  w, int  h);

  bool  operator==(WindowState  st) const;
  bool  operator!=(WindowState  st) const;

  Object*  get_content() const;
  void  change_content(Object*  obj, int  x=gmbb::font::base_size,
                                     int  y=gmbb::font::base_size);

  WindowState  get_state() const;
  void  set_state(WindowState  st);

  void  process(Controller&  ctrl)  override;

  void  update() override;
  void  render(Image&  dst) override;

};


}




#endif




