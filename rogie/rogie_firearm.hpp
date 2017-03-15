#ifndef ROGIE_FIREARM_HPP_INCLUDED
#define ROGIE_FIREARM_HPP_INCLUDED




enum class
FirearmKind
{
  handgun,
  submachinegun,
  grenade_launcher,
  rocket_launcher,

};


enum class
AmmoKind
{
  normal,
  grenade,
  rocket,

};


struct
FirearmSpec
{
  int  durability;

  int  handling_cost;
  int    reload_cost;
  int      fire_cost;

  AmmoKind  ammo_kind;

  int  loadable_quantity;

};


struct
Firearm
{
  FirearmKind  kind;

  int  health;

  int  ammo_quantity;

};




#endif




