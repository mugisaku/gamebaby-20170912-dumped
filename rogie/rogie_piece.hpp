#ifndef ROGIE_PIECE_HPP_INCLUDED
#define ROGIE_PIECE_HPP_INCLUDED


#include"rogie_square.hpp"
#include"rogie_task.hpp"
#include"rogie_item.hpp"
#include<stack>
#include<list>
#include<array>
#include<initializer_list>




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
Piece
{
  static constexpr int  master_flag  = 1;

  static constexpr int  moving_cost_base = 64;

  static constexpr int  armor_strength_max = 16;

  static constexpr int shield_max = 9999;
  static constexpr int oxygen_max =  999;
  static constexpr int   life_max =  300;

  static gmbb::Image  sprite_image;

  using Callback = void(Piece::*)();

  const char*  name;

  uint32_t  flags;

  Field*    current_field;
  Square*  current_square;

  gmbb::Point  rendering_dst_offset;
  gmbb::Point  rendering_src_base;
  gmbb::Point  rendering_src_offset;

  bool  shape_reversing;

  Direction  direction;


  int  shield_remaining;
  int  oxygen_remaining;
  int    life_remaining;

  int  armor_strength;

  int  action_currency;

  int  moving_cost;

  Firearm*  current_firearm;

  const WeaponSpec*  weapon_spec;

  std::array<Item*,8>  belongings_table;

  Task  own_task;

  std::stack<Task>  task_stack;

  std::vector<Callback>  callback_list;

public:
  Piece(const char*  name_, std::initializer_list<Callback>  cbls={});

  void  change_direction(Direction  d);

  int  get_moving_cost(Direction  dir) const;

  void  add_offset_by_direction(int  n=1);
  void  set_offset_by_direction();
  void  set_shape_by_direction();

  bool  append_item(Item*  new_item);

  void    set_flag(uint32_t  v);
  void  unset_flag(uint32_t  v);
  bool   test_flag(uint32_t  v) const;

  void  push_task(TaskCallback  cb);

  const Task&  get_own_task() const;
  const std::stack<Task>&  get_task_stack() const;

  const Firearm*  get_current_firearm() const;

  void  step();


  void  render(gmbb::Image&  dst, int  x, int  y) const;
  void  render_data(gmbb::Image&  dst, int  x, int  y) const;

  void  print() const;


  static bool  compare(Piece*  a, Piece*  b);
  static void   attack(Piece&  a, Piece&  b);


  static void  move_to_direction(Task&  tsk, void*  caller);

  static void  turn_left( Task&  tsk, void*  caller);
  static void  turn_right(Task&  tsk, void*  caller);

  static void  use_weapon(Task&  tsk, void*  caller);
  static void  change_weapon(Task&  tsk, void*  caller);
  static void  punch(Task&  tsk, void*  caller);
  static void  fire(Task&  tsk, void*  caller);
  static void  damage(Task&  tsk, void*  caller);
  static void  disappear(Task&  tsk, void*  caller);


  void  play();

  void  autoplay();

  void  chase_hero();
  void  runaway_from_hero();
  void  attack_hero();

};




#endif




