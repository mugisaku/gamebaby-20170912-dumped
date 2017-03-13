#ifndef ROGIE_PIECE_HPP_INCLUDED
#define ROGIE_PIECE_HPP_INCLUDED


#include"rogie_square.hpp"
#include"rogie_context.hpp"
#include<list>
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
  static constexpr uint32_t  voluntary_flag   = 1;
  static constexpr uint32_t  taskseeking_flag = 2;

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

  uint32_t  flags;

  int  action_currency;
  int  moving_cost_base;

  std::queue<Action>    action_queue;
  std::stack<Context>  context_stack;

  std::list<Context>  task_list;

public:
  Piece(uint32_t  flags_=0);

  void  move_advance();

  void  turn_left();
  void  turn_right();
  void  change_direction(Direction  d);
  void  use_weapon();

  void  push_task_front(Callback  cb);
  void  push_task_back(Callback  cb);
  void  push_action(Callback  cb, int  consum);
  void  push_context(Callback  cb);
  void  pop_context();
  void  step();

  void    set_flag(uint32_t  v);
  void  unset_flag(uint32_t  v);
  bool   test_flag(uint32_t  v) const;

  int  get_moving_cost(Direction  dir) const;

  void  add_offset_by_direction(int  n=1);
  void  set_offset_by_direction();
  void  set_shape_by_direction();


  void  render(gmbb::Image&  dst, int  x, int  y) const;

  static bool  compare(Piece*  a, Piece*  b);

};




#endif




