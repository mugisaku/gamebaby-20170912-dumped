#include"gmbb_sprite.hpp"
#include"gmbb_core.hpp"
#include<cstring>




namespace gmbb{




Sprite::
Sprite(const Image*  src, int  x, int  y, int  w, int  h):
garden(nullptr),
previous(nullptr),
next(nullptr)
{
  reset(src,x,y,w,h);
}




void
Sprite::
reset(const Image*  src, int  x, int  y, int  w, int  h)
{
  source = src;

  source_point.x = x;
  source_point.y = y;

  width  = w;
  height = h;
}


void
Sprite::
change_garden(Garden*  gar)
{
    if(gar && garden)
    {
      printf("すでにガーデンに属しています\n");

      throw;
    }


  garden = gar;
}


void
Sprite::
change_previous(Sprite*  spr)
{
  previous = spr;
}


void
Sprite::
change_next(Sprite*  spr)
{
  next = spr;
}


Garden*    Sprite::get_garden() const{return garden;}
Sprite*  Sprite::get_previous() const{return previous;}
Sprite*      Sprite::get_next() const{return next;}




void
Sprite::
render(Plain&  dst)
{
    if(source)
    {
      source->transfer(source_point.x,source_point.y,width,height,dst,point.x,point.y);
    }
}




}





