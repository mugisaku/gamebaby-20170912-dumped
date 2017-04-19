#ifndef GMBB_IMAGE_HPP
#define GMBB_IMAGE_HPP


#include<cstdint>
#include<vector>
#include<string>
#include<memory>
#include"gmbb_font.hpp"
#include"gmbb_media.hpp"
#include"gmbb_color_table.hpp"
#include"gmbb_palette.hpp"
#include"gmbb_printpoint.hpp"




namespace gmbb{


constexpr int  font_color = 7|8;


class
Image
{
  int  width;
  int  height;

  std::vector<color_table::Index>  pixels;

public:
  Image();
  Image(int  w, int  h);


  void  resize(int  w, int  h);

  void  load(const uint8_t*  src, int  w, int  h, int  pitch);

  void  load_png(FileReader&  r);
  void  load_mgf(FileReader&  r);

  void  save_mgf(FileWriter&  w) const;

  int  get_width() const;
  int  get_height() const;

        color_table::Index&        pixel(int  x, int  y)      ;
  const color_table::Index&  const_pixel(int  x, int  y) const;

  void  fill(color_table::Index  i);


  void    dot(color_table::Index  i, int  x, int  y);
  void  vline(color_table::Index  i, int  x, int  y, int  l);
  void  hline(color_table::Index  i, int  x, int  y, int  l);

  void       rectangle(color_table::Index  i, int  x, int  y, int  w, int  h);
  void  fill_rectangle(color_table::Index  i, int  x, int  y, int  w, int  h);

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

  void  print_large(      char16_t   c, uint8_t  color, int  x, int  y);
  void  print_large(const char*      s, uint8_t  color, int  x, int  y);
  void  print_large(const char16_t*  s, uint8_t  color, int  x, int  y);

  void  compose(const Image&  rhs);

  void  transfer(int  src_x, int  src_y, int  src_w, int  src_h, Image&  dst, int  dst_x, int  dst_y) const;

};


}




#endif




