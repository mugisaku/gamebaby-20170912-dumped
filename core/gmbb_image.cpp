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
rectangle(uint8_t  v, int  x, int  y, int  w, int  h)
{
  hline(v,x,y    ,w);
  hline(v,x,y+h-1,w);

  vline(v,x    ,y+1,h-2);
  vline(v,x+w-1,y+1,h-2);
}


void
Image::
fill_rectangle(uint8_t  v, int  x, int  y, int  w, int  h)
{
    while(h--)
    {
      hline(v,x,y++,w);
    }
}


void
Image::
compose(const Image&  rhs)
{
  const int  w = std::min(width,rhs.get_width());
  const int  h = std::min(height,rhs.get_height());

    for(int  y = 0;  y < h;  y += 1){
    for(int  x = 0;  x < w;  x += 1){
      auto  v = rhs.const_pixel(x,y);

        if(v&8)
        {
          pixel(x,y) = v;
        }
    }}
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
transfer(int  src_x, int  src_y, int  src_w, int  src_h, Image&  dst, int  dst_x, int  dst_y) const
{
  bool  reverse_flag = false;

    if(src_w < 0)
    {
      reverse_flag = true;

      src_w = -src_w;
    }


  const int  dst_w = dst.get_width();
  const int  dst_h = dst.get_height();

    if(!src_w){src_w =  width;}
    if(!src_h){src_h = height;}

    if(src_w > dst_w){src_w = dst_w;}
    if(src_h > dst_h){src_h = dst_h;}

    if(dst_x < 0)
    {
      const int  diff = -dst_x    ;
                         dst_x = 0;

        if(diff < src_w)
        {
          src_x += diff;
          src_w -= diff;
        }

      else
        {
          return;
        }
    }



    if(dst_y < 0)
    {
      const int  diff = -dst_y    ;
                         dst_y = 0;

        if(diff < src_h)
        {
          src_y += diff;
          src_h -= diff;
        }

      else
        {
          return;
        }
    }


    if((dst_x+src_w) >= dst_w)
    {
      const int  diff = (dst_x+src_w)-dst_w;

        if(diff < src_w)
        {
          src_w -= diff;
        }

      else
        {
          return;
        }
    }


    if((dst_y+src_h) >= dst_h)
    {
      const int  diff = (dst_y+src_h)-dst_h;

        if(diff < src_h)
        {
          src_h -= diff;
        }

      else
        {
          return;
        }
    }


    for(int  yy = 0;  yy < src_h;  yy += 1)
    {
        if(reverse_flag)
        {
          int  x = src_x+src_w-1;

            for(int  xx = 0;  xx < src_w;  xx += 1)
            {
              auto  v = const_pixel(x--,src_y+yy);

                if(v&8)
                {
                  dst.dot(v,dst_x+xx,dst_y+yy);
                }
            }
        }

      else
        {
            for(int  xx = 0;  xx < src_w;  xx += 1)
            {
              auto  v = const_pixel(src_x+xx,src_y+yy);

                if(v&8)
                {
                  dst.dot(v,dst_x+xx,dst_y+yy);
                }
            }
        }
    }
}




}





