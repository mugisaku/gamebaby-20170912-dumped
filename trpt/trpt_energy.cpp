#include"trpt_energy.hpp"




namespace gmbb{
namespace trpt{


int  Energy::get_remaining() const{return remaining>>shift_amount;}
int  Energy::get_consumption() const{return consumption>>shift_amount;}


void
Energy::
fill()
{
  remaining = 99<<shift_amount;
}


void
Energy::
change_consumption(int  v)
{
  consumption = v;
}


bool
Energy::
consume()
{
    if(remaining >= consumption)
    {
      remaining -= consumption;

      return true;
    }


  return false;
}


}}




