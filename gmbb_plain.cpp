#include"gmbb_plain.hpp"
#include<cstring>




namespace gmbb{




      uint8_t&  Plain::pixel(      int  x, int  y)      {return data[y][x];}
const uint8_t&  Plain::const_pixel(int  x, int  y) const{return data[y][x];}

void  Plain::fill(uint8_t  v){std::memset(&data,v,sizeof(data));}

void  Plain::dot(uint8_t  v, int  x, int  y){data[y][x] = v;}


void
Plain::
vline(uint8_t  v, int  x, int  y, int  l)
{
    while(l--)
    {
      dot(v,x,y++);
    }
}


void
Plain::
hline(uint8_t  v, int  x, int  y, int  l)
{
    while(l--)
    {
      dot(v,x++,y);
    }
}


void
Plain::
compose(const Plain&  rhs)
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




}





