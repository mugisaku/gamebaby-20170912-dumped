#ifndef GMBB_RANDOM_NUMBER_HPP_INCLUDED
#define GMBB_RANDOM_NUMBER_HPP_INCLUDED


#include<cstdint>


namespace gmbb{
namespace random_number{


class
Seed
{
  uint32_t  x;
  uint32_t  y;
  uint32_t  z;
  uint32_t  w;

public:
  Seed(                                                      );
  Seed(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_);

  void  reset(                                                      );
  void  reset(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_);

  uint32_t  generate();

};


}}


#endif




