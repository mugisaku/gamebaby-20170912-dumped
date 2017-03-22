#include"rogie_firearm.hpp"
#include"rogie_piece.hpp"




const WeaponSpec&
get_weapon_spec(WeaponKind  k)
{
  static const WeaponSpec  specs[] = {
    {
      u"パンチ",//名前
      40,//威力
      10,//リロードコスト
      20,//発射コスト
       1,//最大装填数
    },
    {
      u"ハンドガン",
      80,
      40,
      24,
       8,
    },
    {
      u"サブマシンガン",
      60,
      60,
       4,
      24,
    },
    {0},
    {0},
    {0},
    {0},
    {0},
    {0},
  };



  return specs[static_cast<int>(k)];
}




Firearm::
Firearm(WeaponKind  k):
weapon_kind(k)
{
  fulfill();
}




int
Firearm::
fulfill()
{
  auto&  spec = get_weapon_spec(weapon_kind);

  bullet = spec.bullet_max;

  return spec.reloading_cost;
}


void
Firearm::
render(gmbb::Image&  dst, int  x, int  y) const
{
    switch(weapon_kind)
    {
  case(WeaponKind::handgun):
      Piece::sprite_image.transfer(48,24*10,24,24,dst,x,y);
      break;
  case(WeaponKind::submachinegun):
      Piece::sprite_image.transfer(48,24*11,24,24,dst,x,y);
      break;
    }
}


void
Firearm::
render_with_data(gmbb::Image&  dst, int  x, int  y) const
{
  auto&  spec = get_weapon_spec(weapon_kind);

  render(dst,x+32,y);

  bool  flag = false;

  int  n = 0;

    switch(weapon_kind)
    {
  case(WeaponKind::handgun):
        for(;  n <= spec.bullet_max;  ++n)
        {
          flag = (n < bullet);

          Piece::sprite_image.transfer(26+(flag? 0:5),265,3,5,dst,x,y+16);

          x += 4;
        }
      break;
  case(WeaponKind::submachinegun):
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




