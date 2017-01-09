#ifndef TRPT_MOVECONTEXT_HPP
#define TRPT_MOVECONTEXT_HPP


#include<cstdint>


using point_t = int;


class
MoveContext
{
  static constexpr int  shift_amount = 16;

  point_t  x_point=0;
  point_t  y_point=0;

  point_t  x_hot_point=0;
  point_t  y_hot_point=0;

  point_t  x_dst_point=0;
  point_t  y_dst_point=0;

  point_t  x_add_amount=0;
  point_t  y_add_amount=0;

  int  distance;

public:
  MoveContext(point_t  x=0, point_t  y=0);

  operator bool() const;

  void  set_start(      point_t  x, point_t  y);
  void  set_destination(point_t  x, point_t  y);

  point_t  get_x() const;
  point_t  get_y() const;

  void  step();

  void  finish();

};


#endif




