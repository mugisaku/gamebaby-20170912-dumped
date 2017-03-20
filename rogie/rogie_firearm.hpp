#ifndef ROGIE_FIREARM_HPP_INCLUDED
#define ROGIE_FIREARM_HPP_INCLUDED


#include"gmbb.hpp"


enum class
FirearmKind
{
  handgun,
  submachinegun,
  grenade_launcher,
  rocket_launcher,

};


struct
Ammo
{
  FirearmKind  kind;

  int  number;

};


struct
FirearmSpec
{
  const char16_t*  name;

  int  power;
  int  durability;

  int   handling_cost;
  int  reloading_cost;
  int      fire_cost;

  int  bullet_max;

};


struct
Firearm
{
  FirearmKind  kind;
  FirearmSpec  spec;

  int  health;
  int  bullet;

public:
  Firearm(FirearmKind  k);

  void  render(gmbb::Image&  dst, int  x, int  y) const;

};




#endif




