#ifndef GMBB_CONTROLLER_HPP
#define GMBB_CONTROLLER_HPP


#include<cstdint>


namespace gmbb{


constexpr int  up_flag    = 0x01;
constexpr int  left_flag  = 0x02;
constexpr int  right_flag = 0x04;
constexpr int  down_flag  = 0x08;
constexpr int  p_flag     = 0x10;
constexpr int  n_flag     = 0x20;


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


}


#endif




