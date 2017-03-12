#ifndef ROGIE_PIECE_HPP_INCLUDED
#define ROGIE_PIECE_HPP_INCLUDED


#include"rogie_square.hpp"
#include"rogie_context.hpp"
#include<queue>
#include<stack>




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
GroupKind
{
  null,
  own,
  friends,
  enemies,
  neutrals,
  unknown,

};


enum class
TaskKind
{
  null,
  chase_hero,
  runaway_from_hero,

};


struct
Field;


struct
Action
{
  Callback  callback;

  int  consumption;

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

  TaskKind  task_kind;

  bool  voluntary_flag;

  int  action_currency;
  int  moving_cost_base;

  std::queue<Action>    action_queue;
  std::stack<Context>  context_stack;

public:
  Piece(bool  voluntary=false);

  void  move_advance();
  void  move_back();
  void  turn_left();
  void  turn_right();
  void  change_direction(Direction  d);
  void  use_weapon();

  void  push_action(Callback  cb, int  consum);
  void  pop_context();
  void  step();
  void  chase_hero();

  int  get_moving_cost(Direction  dir) const;

  void  add_offset_by_direction(int  n=1);
  void  set_offset_by_direction();
  void  set_shape_by_direction();


  void  render(gmbb::Image&  dst, int  x, int  y) const;

  static bool  compare(Piece*  a, Piece*  b);

};




#endif




