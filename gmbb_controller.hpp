#ifndef GMBB_CONTROLLER_HPP
#define GMBB_CONTROLLER_HPP


#include<cstdint>


namespace keyflag
{
  static constexpr int  up    = 0x01;
  static constexpr int  left  = 0x02;
  static constexpr int  right = 0x04;
  static constexpr int  down  = 0x08;
  static constexpr int  p     = 0x10;
  static constexpr int  n     = 0x20;

}


class
Controller
{
  uint8_t   pressing_key_state=0;
  uint8_t    pressed_key_state=0;
  uint8_t  unpressed_key_state=0;

public:
  void    press(int  flag);
  void  unpress(int  flag);

  void  clean();

  bool  test_pressing(int  flag) const;
  bool  test_pressed(int  flag) const;
  bool  test_unpressed(int  flag) const;

};




#endif




