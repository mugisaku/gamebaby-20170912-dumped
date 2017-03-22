#ifndef ROGIE_FIREARM_HPP_INCLUDED
#define ROGIE_FIREARM_HPP_INCLUDED


#include"gmbb.hpp"


enum class
WeaponKind
{
  punch,
  handgun,
  submachinegun,
  grenade_launcher,
  rocket_launcher,

};


struct
Ammo
{
  WeaponKind  kind;

  int  number;

};


struct
WeaponSpec
{
  const char16_t*  name;

  int  power;

  int  reloading_cost;
  int       fire_cost;

  int  bullet_max;

};


const WeaponSpec&  get_weapon_spec(WeaponKind  k);


struct
Firearm
{
  WeaponKind  weapon_kind;

  int  health;
  int  bullet;

public:
  Firearm(WeaponKind  k);

  int  fulfill();

  void  render(          gmbb::Image&  dst, int  x, int  y) const;
  void  render_with_data(gmbb::Image&  dst, int  x, int  y) const;

};




#endif




