#ifndef ROGIE_PIECE_HPP_INCLUDED
#define ROGIE_PIECE_HPP_INCLUDED


#include"rogie_square.hpp"
#include"rogie_task.hpp"
#include"rogie_item.hpp"
#include<stack>
#include<array>




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
  static constexpr int  locked_flag = 16;


  static gmbb::Image  sprite_image;

  uint32_t  flags;

  Field*    current_field;
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

  Task  own_task;

  std::stack<Task>  task_stack;

public:
  Piece(uint32_t  flags_=0);

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

  void  push_task(Callback  cb);

  const Task&  get_own_task() const;
  const std::stack<Task>&  get_task_stack() const;

  void  step();


  void  render(gmbb::Image&  dst, int  x, int  y) const;

  static bool  compare(Piece*  a, Piece*  b);


  static void  move_to_direction(Task&  tsk, void*  caller);

  static void  turn_left( Task&  tsk, void*  caller);
  static void  turn_right(Task&  tsk, void*  caller);

  static void  use_weapon(Task&  tsk, void*  caller);
  static void  change_weapon(Task&  tsk, void*  caller);
  static void  ready_to_fire(Task&  tsk, void*  caller);
  static void  cancel_ready(Task&  tsk, void*  caller);
  static void  punch(Task&  tsk, void*  caller);
  static void  fire(Task&  tsk, void*  caller);
  static void  damage(Task&  tsk, void*  caller);


  void  play();

  void  autoplay();

  void  chase_hero();
  void  runaway_from_hero();
  void  attack_hero();
  void  wait();

};




#endif




