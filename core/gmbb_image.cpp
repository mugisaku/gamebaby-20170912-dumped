#include"gmbb_image.hpp"
#include<cstring>




namespace gmbb{




Image::
Image():
width(0),
height(0)
{
}


Image::
Image(int  w, int  h)
{
  resize(w,h);
}




void
Image::
resize(int  w, int  h)
{
  width  = w;
  height = h;

  pixels.resize(w*h);
}


void
Image::
dot(uint8_t  v, int  x, int  y)
{
  pixels[(width*y)+x] = v;
}


void
Image::
vline(uint8_t  v, int  x, int  y, int  l)
{
    while(l--)
    {
      dot(v,x,y++);
    }
}


void
Image::
hline(uint8_t  v, int  x, int  y, int  l)
{
    while(l--)
    {
      dot(v,x++,y);
    }
}


void
Image::
compose(const Image&  rhs)
{
  auto  dst =           &pixel(0,0);
  auto  src = &rhs.const_pixel(0,0);

  int  n = width*height;

    while(n--)
    {
      auto  v = *src++;

        if(v&8)
        {
          *dst = v;
        }


      ++dst;
    }
}


void
Image::
load(const uint8_t*  src, int  w, int  h, int  pitch)
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
transfer(int  src_x, int  src_y, int  src_w, int  src_h, Image&  dst, int  x, int  y) const
{
  const int  dst_w = dst.get_width();
  const int  dst_h = dst.get_height();

    if(!src_w){src_w =  width;}
    if(!src_h){src_h = height;}

    if(src_w > dst_w){src_w = dst_w;}
    if(src_h > dst_h){src_h = dst_h;}

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





