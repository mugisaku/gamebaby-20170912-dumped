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
dot(color_table::Index  i, int  x, int  y)
{
  pixels[(width*y)+x] = i;
}


void
Image::
vline(color_table::Index  i, int  x, int  y, int  l)
{
    while(l--)
    {
      dot(i,x,y++);
    }
}


void
Image::
hline(color_table::Index  i, int  x, int  y, int  l)
{
    while(l--)
    {
      dot(i,x++,y);
    }
}


void
Image::
rectangle(color_table::Index  i, int  x, int  y, int  w, int  h)
{
  hline(i,x,y    ,w);
  hline(i,x,y+h-1,w);

  vline(i,x    ,y+1,h-2);
  vline(i,x+w-1,y+1,h-2);
}


void
Image::
fill_rectangle(color_table::Index  i, int  x, int  y, int  w, int  h)
{
    while(h--)
    {
      hline(i,x,y++,w);
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
      auto  i = rhs.const_pixel(x,y);

        if(i.test())
        {
          pixel(x,y) = i;
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


      color_table::Index&  Image::pixel(      int  x, int  y)      {return pixels[(width*y)+x];}
const color_table::Index&  Image::const_pixel(int  x, int  y) const{return pixels[(width*y)+x];}

void  Image::fill(color_table::Index  i){std::fill(pixels.begin(),pixels.end(),i);}


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
              auto  i = const_pixel(x--,src_y+yy);

                if(i.test())
                {
                  dst.dot(i,dst_x+xx,dst_y+yy);
                }
            }
        }

      else
        {
            for(int  xx = 0;  xx < src_w;  xx += 1)
            {
              auto  i = const_pixel(src_x+xx,src_y+yy);

                if(i.test())
                {
                  dst.dot(i,dst_x+xx,dst_y+yy);
                }
            }
        }
    }
}




}





