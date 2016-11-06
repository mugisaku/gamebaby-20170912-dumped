#ifndef CBES_WINDOW_HPP
#define CBES_WINDOW_HPP


#include"cbes_object.hpp"


namespace cbes{


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
  static constexpr char16_t  space_code = 0xE104;

  Window();
  Window(int  w, int  h);

  bool  operator==(WindowState  st) const;
  bool  operator!=(WindowState  st) const;

  Object*  get_content() const;
  void  change_content(Object*  obj, int  x, int  y);

  WindowState  get_state() const;
  void  set_state(WindowState  st);

  void  reframe(CharacterTable&  dst);
  void     fill(CharacterTable&  dst);

  void  update() override;
  void  render(CharacterTable&  dst) override;

};


}




#endif




