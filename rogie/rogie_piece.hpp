#ifndef ROGIE_PIECE_HPP_INCLUDED
#define ROGIE_PIECE_HPP_INCLUDED


#include"rogie_square.hpp"
#include"rogie_context.hpp"




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


enum class
MotionKind
{
  move_to_direction,
  move_to_opposite_direction,

};


struct
Piece
{
  static gmbb::Image  sprite_image;


  Square*  current_square;

  gmbb::Point  rendering_dst_offset;
  gmbb::Point  rendering_src_base;
  gmbb::Point  rendering_src_offset;

  bool  shape_reversing;

  Direction  direction;

  int  shield_remaining;

  uint32_t  weapon_flags;

  Weapon  current_weapon;

  int  action_currency;
  int  moving_cost_base;

  std::vector<Context>  context_stack;

public:
  Piece();

  void  move_advance();
  void  move_back();
  void  turn_left();
  void  turn_right();
  void  use_weapon();

  void  push_context(Callback  cb);
  void  pop_context();
  void  step();

  int  get_moving_cost(Direction  dir) const;

  void  add_offset_by_direction(int  n=1);
  void  set_offset_by_direction();
  void  set_shape_by_direction();


  void  render(gmbb::Image&  dst, int  x, int  y) const;

  static bool  compare(Piece*  a, Piece*  b);

};




#endif




