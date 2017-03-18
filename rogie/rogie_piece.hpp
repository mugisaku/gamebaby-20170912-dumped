#ifndef ROGIE_PIECE_HPP_INCLUDED
#define ROGIE_PIECE_HPP_INCLUDED


#include"rogie_square.hpp"
#include"rogie_taskmanager.hpp"
#include"rogie_item.hpp"
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
  static constexpr int  master_flag = 1;
  static constexpr int  have_gun_flag = 2;
  static constexpr int  use_gun_flag = 4;
  static constexpr int  readied_flag = 8;


  static gmbb::Image  sprite_image;

  TaskManager  taskman;

  uint32_t  flags;

  Square*  current_square;

  gmbb::Point  rendering_dst_offset;
  gmbb::Point  rendering_src_base;
  gmbb::Point  rendering_src_offset;

  bool  shape_reversing;

  Direction  direction;

  int  shield_remaining;

  int  action_currency;

  int  moving_cost_base;

  std::array<Item,8>  belongings_table;

public:
  Piece(std::initializer_list<TaskCallback>  tskcb={}, uint32_t  flags_=0);

  void  change_direction(Direction  d);

  int  get_moving_cost(Direction  dir) const;

  bool  consume_currency(int  v);

  void  add_offset_by_direction(int  n=1);
  void  set_offset_by_direction();
  void  set_shape_by_direction();

  bool  append_item(Item&&  new_item);

  void    set_flag(uint32_t  v);
  void  unset_flag(uint32_t  v);
  bool   test_flag(uint32_t  v) const;

  TaskManager&  get_task_manager();

  bool  step();


  void  render(gmbb::Image&  dst, int  x, int  y) const;

  static bool  compare(Piece*  a, Piece*  b);


  static void  move_to_direction(Context&  ctx);

  static void  turn_left( Context&  ctx);
  static void  turn_right(Context&  ctx);

  static void  use_weapon(Context&  ctx);
  static void  change_weapon(Context&  ctx);
  static void  ready_to_fire(Context&  ctx);
  static void  cancel_ready(Context&  ctx);
  static void  punch(Context&  ctx);
  static void  fire(Context&  ctx);
  static void  damage(Context&  ctx);

  static void  chase_hero(Task&  tsk);
  static void  runaway_from_hero(Task&  tsk);
  static void  attack_hero(Task&  tsk);
  static void  wait(Task&  tsk);

};




#endif




