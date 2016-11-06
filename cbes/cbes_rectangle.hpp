#ifndef CBES_RECTANGLE_HPP
#define CBES_RECTANGLE_HPP


#include<cstdint>
#include<cstdio>


#ifndef report
#define report  printf("[report] %s %s %4d\n",__FILE__,__func__,__LINE__);
#endif


namespace cbes{


struct
Point
{
  int  x;
  int  y;

  constexpr Point(int  x_=0, int  y_=0): x(x_), y(y_){}

};


struct
Rectangle
{
  Point  point;

  int  width;
  int  height;

  constexpr Rectangle(int  w_=0, int  h_=0): width(w_), height(h_){}
  constexpr Rectangle(int  x_, int  y_, int  w_, int  h_): point(x_,y_), width(w_), height(h_){}

};


}




#endif




