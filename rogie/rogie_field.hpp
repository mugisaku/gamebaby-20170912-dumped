#ifndef ROGIE_FIELD_HPP_INCLUDED
#define ROGIE_FIELD_HPP_INCLUDED


#include"rogie_square.hpp"


struct
Field
{
  static constexpr int   width = 32;
  static constexpr int  height = 32;

  Square  table[height][width];

public:
  Field();

  void  prepare();

  void  render(gmbb::Image&  dst) const;

};




#endif




