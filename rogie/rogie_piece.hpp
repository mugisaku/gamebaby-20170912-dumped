#ifndef ROGIE_PIECE_HPP_INCLUDED
#define ROGIE_PIECE_HPP_INCLUDED


#include"rogie_square.hpp"




enum class
WeaponKind
{
  punch,
  handgun,
  submachinegun,
  shotgun,
  grenade_launcher,
  rocket_launcher,

};


struct
Weapon
{
  WeaponKind  kind;

  int  reload_inteval;
  int    fire_inteval;

  int   ready_cost;

  int  bullete    ;
  int  bullete_max;

};


struct
Ammo
{
  WeaponKind  kind;

  int  power;

};


struct
Piece
{
  Square*  current_square;

  Direction  direction;

  int  shield_remaining;

  uint32_t  weapon_flags;

  Weapon  current_weapon;

};




#endif




