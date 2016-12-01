#include"gmbb_image.hpp"
#include<cstring>




namespace gmbb{


constexpr uint8_t
piece[8][8] =
{
  {0,0,4,4,4,4,4,4},
  {0,4,4,6,6,6,6,6},
  {4,4,6,6,4,4,4,4},
  {4,6,6,4,4,1,1,1},
  {4,6,4,4,1,1,1,1},
  {4,6,4,1,1,1,1,1},
  {4,6,4,1,1,1,1,1},
  {4,6,4,1,1,1,1,1},
};


void
Image::
frame_top(int  x, int  y, int  w)
{
    for(int  yy = 0;  yy < 8;  yy += 1){
    for(int  xx = 0;  xx < 8;  xx += 1){
      auto  v = piece[yy][xx];

        if(v)
        {
          dot(v|8,x+xx    ,y+yy);
          dot(v|8,x+w-1-xx,y+yy);
        }
    }}


  x +=  8;
  w -= 16;

  hline(4|8,x,y++,w);
  hline(6|8,x,y++,w);
  hline(4|8,x,y++,w);
  hline(1|8,x,y++,w);
  hline(1|8,x,y++,w);
  hline(1|8,x,y++,w);
  hline(1|8,x,y++,w);
  hline(1|8,x,y  ,w);
}


void
Image::
frame_body(int  x, int  y, int  w, int  h)
{
  vline(4|8,x+0,y,h);
  vline(6|8,x+1,y,h);
  vline(4|8,x+2,y,h);

  vline(4|8,x+w-1-0,y,h);
  vline(6|8,x+w-1-1,y,h);
  vline(4|8,x+w-1-2,y,h);


    while(h--)
    {
      hline(1|8,x+3,y++,w-6);
    }
}


void
Image::
frame_bottom(int  x, int  y, int  w)
{
    for(int  yy = 0;  yy < 8;  yy += 1){
    for(int  xx = 0;  xx < 8;  xx += 1){
      auto  v = piece[yy][xx];

        if(v)
        {
          dot(v,x+xx    ,y+8-1-yy);
          dot(v,x+w-1-xx,y+8-1-yy);
        }
    }}


  x +=  8;
  w -= 16;

  hline(1|8,x,y++,w);
  hline(1|8,x,y++,w);
  hline(1|8,x,y++,w);
  hline(1|8,x,y++,w);
  hline(1|8,x,y++,w);
  hline(4|8,x,y++,w);
  hline(6|8,x,y++,w);
  hline(4|8,x,y  ,w);
}


void
Image::
frame(int  x, int  y, int  w, int  h)
{
  frame_top(   x,y    ,w     );
  frame_body(  x,y  +8,w,h-16);
  frame_bottom(x,y+h-8,w     );
}




}





