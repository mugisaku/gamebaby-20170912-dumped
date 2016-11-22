#ifndef GMBB_IMAGE_HPP
#define GMBB_IMAGE_HPP


#include<cstdint>
#include<vector>
#include"gmbb_plain.hpp"


namespace gmbb{




struct
Image
{
  int  width;
  int  height;

  std::vector<uint8_t>  pixels;

public:
  Image();


  void  load(int  w, int  h, const uint8_t*  src, int  pitch);

  int  get_width() const;
  int  get_height() const;

        uint8_t&        pixel(int  x, int  y)      ;
  const uint8_t&  const_pixel(int  x, int  y) const;

  void  fill(uint8_t  v=0);

  void  transfer(int  src_x, int  src_y, int  src_w, int  src_h, Plain&  dst, int  x, int  y) const;

};


}




#endif




