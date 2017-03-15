#ifndef ROGIE_PIECE_HPP_INCLUDED
#define ROGIE_PIECE_HPP_INCLUDED


#include"rogie_square.hpp"
#include"rogie_object.hpp"
#include"rogie_item.hpp"
#include<array>
#include<list>
#include<queue>
#include<stack>




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
Piece: public Object
{
  static gmbb::Image  sprite_image;


  Square*  current_square;

  gmbb::Point  rendering_dst_offset;
  gmbb::Point  rendering_src_base;
  gmbb::Point  rendering_src_offset;

  bool  shape_reversing;

  Direction  direction;

  int  shield_remaining;

  int  moving_cost_base;

  std::array<Item,8>  belongings_table;

public:
  Piece(uint32_t  flags_=0);

  void  move_advance();

  void  turn_left();
  void  turn_right();
  void  change_direction(Direction  d);
  void  use_weapon();

  int  get_moving_cost(Direction  dir) const;

  void  add_offset_by_direction(int  n=1);
  void  set_offset_by_direction();
  void  set_shape_by_direction();


  void  render(gmbb::Image&  dst, int  x, int  y) const;

  static bool  compare(Piece*  a, Piece*  b);

};




#endif




