#ifndef GMBB_FORMATTED_HPP
#define GMBB_FORMATTED_HPP


#include<cstddef>


namespace gmbb{


struct
Formatted
{
  static constexpr size_t  length = 80;

  char  data[length];

  const char*  operator()(const char*  fmt, ...);

};


}




#endif




