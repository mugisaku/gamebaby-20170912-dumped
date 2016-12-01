#ifndef GMBB_IMAGE_HPP
#define GMBB_IMAGE_HPP


#include<cstdint>
#include<vector>
#include<string>
#include"gmbb_font.hpp"
#include"gmbb_printpoint.hpp"


namespace gmbb{


constexpr int  font_color = 7|8;


class
Image
{
  int  width;
  int  height;

  std::vector<uint8_t>  pixels;

public:
  Image();
  Image(int  w, int  h);


  void  resize(int  w, int  h);

  void  load(const uint8_t*  src, int  w, int  h, int  pitch);

  int  get_width() const;
  int  get_height() const;

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

  void  compose(const Image&  rhs);

  void  transfer(int  src_x, int  src_y, int  src_w, int  src_h, Image&  dst, int  x, int  y) const;

};


}




#endif




