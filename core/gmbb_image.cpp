#include"gmbb_image.hpp"
#include<cstring>




namespace gmbb{




Image::
Image()
{
}




void
Image::
load(int  w, int  h, const uint8_t*  src, int  pitch)
{
  width  = w;
  height = h;

  pixels.resize(w*h);

  auto  dst = pixels.begin();

    while(h--)
    {
      auto  p = src         ;
                src += pitch;

        for(int  x = 0;  x < w;  x += 1)
        {
          *dst++ = *p++;
        }
    }
}


int  Image::get_width() const{return width;}
int  Image::get_height() const{return height;}


      uint8_t&  Image::pixel(      int  x, int  y)      {return pixels[(width*y)+x];}
const uint8_t&  Image::const_pixel(int  x, int  y) const{return pixels[(width*y)+x];}

void  Image::fill(uint8_t  v){std::memset(pixels.data(),v,width*height);}


void
Image::
transfer(int  src_x, int  src_y, int  src_w, int  src_h, Plain&  dst, int  x, int  y) const
{
    for(int  yy = 0;  yy < src_h;  yy += 1){
    for(int  xx = 0;  xx < src_w;  xx += 1){
      auto  v = const_pixel(src_x+xx,src_y+yy);

        if(v&8)
        {
          dst.dot(v,x+xx,y+yy);
        }
    }}
}


}





