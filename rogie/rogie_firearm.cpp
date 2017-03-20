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
      spec.handling_cost  = 10;
      spec.fire_cost      = 10;
      spec.reloading_cost = 10;
      break;
  case(FirearmKind::submachinegun):
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





