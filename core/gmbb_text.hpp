#ifndef GMBB_TEXT_HPP_INCLUDED
#define GMBB_TEXT_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>
#include<queue>
#include"gmbb_rectangle.hpp"
#include"gmbb_controller.hpp"
#include"gmbb_image.hpp"




namespace gmbb{


class
Text
{
  struct Line;

  int  column_number;
  int     row_number;

  Line*    first;
  Line*  current;
  Line*     last;

  char16_t  last_char;

public:
  Text(int  col_n, int  row_n);

  void  clear();

  void  rotate();

  void  push(char16_t  c);

  bool  is_full() const;

  void  render(Image&  dst, int  x, int  y) const;

};


}




#endif




