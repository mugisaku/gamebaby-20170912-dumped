#ifndef GMBB_PLAIN_HPP
#define GMBB_PLAIN_HPP


#include<cstdint>
#include<string>
#include"gmbb_font.hpp"
#include"gmbb_printpoint.hpp"


namespace gmbb{


constexpr int  font_color = 7|8;


struct
Plain
{
  static constexpr int   width = 320;
  static constexpr int  height = 256;

  uint8_t  data[height][width];

        uint8_t&        pixel(int  x, int  y)      ;
  const uint8_t&  const_pixel(int  x, int  y) const;

  void  fill(uint8_t  v=0);

  void  dot(uint8_t  v, int  x, int  y);
  void  vline(uint8_t  v, int  x, int  y, int  l);
  void  hline(uint8_t  v, int  x, int  y, int  l);

  void  frame_top(   int  x, int  y, int  w);
  void  frame_body(  int  x, int  y, int  w, int  h);
  void  frame_bottom(int  x, int  y, int  w);
  void  frame(       int  x, int  y, int  w, int  h);

  void  print(      char16_t   c, uint8_t  color, int  x, int  y);
  void  print(const char*      s, uint8_t  color, int  x, int  y);
  void  print(const char16_t*  s, uint8_t  color, int  x, int  y);

  void  print_tall(      char16_t   c, uint8_t  color, int  x, int  y);
  void  print_tall(const char*      s, uint8_t  color, int  x, int  y);
  void  print_tall(const char16_t*  s, uint8_t  color, int  x, int  y);

  void  compose(const Plain&  rhs);

};


}




#endif




