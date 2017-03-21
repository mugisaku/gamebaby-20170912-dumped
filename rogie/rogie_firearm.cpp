#include"rogie_firearm.hpp"
#include"rogie_piece.hpp"




constexpr
FirearmSpec
get_spec(FirearmKind  k)
{
  FirearmSpec  spec = {0};

    switch(k)
    {
  case(FirearmKind::handgun):
      spec.name           = u"ハンドガン";
      spec.power          = 32;
      spec.bullet_max     = 8;
      spec.fire_cost      = 10;
      spec.reloading_cost = 10;
      break;
  case(FirearmKind::submachinegun):
      spec.name           = u"サブマシンガン";
      spec.power          = 32;
      spec.bullet_max     = 24;
      spec.fire_cost      =  1;
      spec.reloading_cost = 10;
      break;
      break;
    }


  return spec;
}




Firearm::
Firearm(FirearmKind  k):
kind(k),
spec(get_spec(k))
{
  bullet = spec.bullet_max;
}




int
Firearm::
fulfill()
{
  bullet = spec.bullet_max;

  return spec.reloading_cost;
}


void
Firearm::
render(gmbb::Image&  dst, int  x, int  y) const
{
    switch(kind)
    {
  case(FirearmKind::handgun):
      Piece::sprite_image.transfer(48,24*10,24,24,dst,x,y);
      break;
  case(FirearmKind::submachinegun):
      Piece::sprite_image.transfer(48,24*11,24,24,dst,x,y);
      break;
    }
}


void
Firearm::
render_with_data(gmbb::Image&  dst, int  x, int  y) const
{
  render(dst,x+32,y);

  bool  flag = false;

  int  n = 0;

    switch(kind)
    {
  case(FirearmKind::handgun):
        for(;  n <= spec.bullet_max;  ++n)
        {
          flag = (n < bullet);

          Piece::sprite_image.transfer(26+(flag? 0:5),265,3,5,dst,x,y+16);

          x += 4;
        }
      break;
  case(FirearmKind::submachinegun):
      constexpr int  w = 6;

        for(int  yy = 0;  yy < spec.bullet_max/w;  ++yy)
        {
          Piece::sprite_image.transfer(26+((n < bullet)? 0:5),265,3,5,dst,x,y);

            for(int  xx = 0;  xx < w;  ++xx)
            {
              flag = (n++ < bullet);

              Piece::sprite_image.transfer(26+(flag? 0:5),265,3,5,dst,x+(4*xx),y);
            }


          y += 5;
        }
      break;
    }
}




