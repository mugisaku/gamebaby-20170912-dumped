#include"gmbb_subimage.hpp"
#include"gmbb_image.hpp"
#include<cstring>



namespace gmbb{




SubImage::
SubImage():
width(0),
height(0)
{
}


SubImage::
SubImage(int  w, int  h)
{
  resize(w,h);
}




void
SubImage::
resize(int  w, int  h)
{
  width  = w;
  height = h;

  table.resize(w*h);
}


int  SubImage::get_width() const{return width;}
int  SubImage::get_height() const{return height;}


Palette::index_t
SubImage::
get_data(int  x, int  y) const
{
  return table[(width*y)+x];
}


void
SubImage::
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
              auto  v = palette[get_data(x--,src_y+yy)];

              dst.dot(v,dst_x+xx,dst_y+yy);
            }
        }

      else
        {
            for(int  xx = 0;  xx < src_w;  xx += 1)
            {
              auto  v = palette[get_data(src_x+xx,src_y+yy)];

              dst.dot(v,dst_x+xx,dst_y+yy);
            }
        }
    }
}




}





