#ifndef GMBB_PRINTPOINT_HPP
#define GMBB_PRINTPOINT_HPP


#include"gmbb_font.hpp"


namespace gmbb{


struct
PrintPoint
{
  int  value;

  constexpr PrintPoint(int  v=0): value(v){}

  constexpr int  operator*() const
  {
    return value;
  }

  constexpr operator int() const
  {
    return value;
  }

  constexpr int  operator+(int  n) const
  {
    return(value+(font::base_size*n));
  }

  PrintPoint  operator+=(int  n)
  {
    PrintPoint  now(value);

    value += font::base_size*n;

    return now;
  }

};




}




#endif




