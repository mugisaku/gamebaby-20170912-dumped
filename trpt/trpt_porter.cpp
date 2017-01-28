#include"trpt_porter.hpp"




namespace gmbb{
namespace trpt{


Porter::
Porter(const char16_t*  name_, Facility*  fa):
name(name_),
facility(fa)
{
}




bool
Porter::
operator()(ActionKind  k)
{
    switch(k)
    {
  case(ActionKind::move):
        if(energy.value >= energy.subtract_amount)
        {
          energy.value -= energy.subtract_amount;

          return true;
        }

      else
        if(foods_amount)
        {
          --foods_amount;

          energy.value = Energy::value_max;

          return true;
        }
      break;
    }


  return false;
}


}}




