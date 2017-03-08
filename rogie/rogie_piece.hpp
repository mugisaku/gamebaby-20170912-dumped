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
  static gmbb::Image  sprite_image;


  Square*  current_square;

  Direction  direction;

  int  shield_remaining;

  uint32_t  weapon_flags;

  Weapon  current_weapon;

public:
  Piece();

  void  move_advance();
  void  move_back();
  void  turn_left();
  void  turn_right();

  void  render(gmbb::Image&  dst, int  x, int  y) const;

  static bool  compare(Piece*  a, Piece*  b);

};




#endif




