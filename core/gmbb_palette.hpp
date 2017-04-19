#ifndef GMBB_PALETTE_HPP
#define GMBB_PALETTE_HPP


#include<cstdint>
#include"gmbb_color_table.hpp"


namespace gmbb{


struct
Palette
{
  static constexpr int  size = 256;

  color_table::Index  data[size];

  using index_t = uint8_t;

  Palette(){}

  color_table::Index  operator[](int  i) const
  {
    return data[i];
  }

};


}


#endif




