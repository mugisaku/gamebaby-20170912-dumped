#ifndef GMBB_COLOR_TABLE_HPP
#define GMBB_COLOR_TABLE_HPP


#include<cstdint>


namespace gmbb{
namespace color_table{


constexpr int  size = 0x8000;


using color_t = uint32_t;


struct
Index
{
  static constexpr int        mask = 0x7FFF;
  static constexpr int  valid_flag = 0x8000;

  uint16_t  value;

  constexpr Index(int  r5, int  g5, int  b5): value(valid_flag|(r5<<10)|(g5<<5)|b5){}
  constexpr Index(                  int  l5): value(valid_flag|(l5<<10)|(l5<<5)|l5){}
  constexpr Index(                         ): value(0){}

  color_t&  operator*() const;

  void  assign(int  r5, int  g5, int  b5);
  void  assign(                  int  l5);

  constexpr bool  test() const{return value&valid_flag;}

};


void  set(color_t  color, Index  i);


}}


#endif




