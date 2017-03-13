#include"gmbb_random_number.hpp"
#include<random>




namespace gmbb{
namespace random_number{


static
std::random_device
randev;


Seed::
Seed()
{
  reset();
}


Seed::
Seed(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_)
{
  reset(x_,y_,z_,w_);
}




void
Seed::
reset()
{
  x = randev();
  y = randev();
  z = randev();
  w = randev();
}


void
Seed::
reset(uint32_t  x_, uint32_t  y_, uint32_t  z_, uint32_t  w_)
{
  x = x_;
  y = y_;
  z = z_;
  w = w_;
}


uint32_t
Seed::
generate()
{
  uint32_t  t = x ^ (x << 11);

  x = y;
  y = z;
  z = w;

  return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8)); 
}




}}




