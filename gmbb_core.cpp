#include"gmbb_core.hpp"




namespace gmbb{


Plain  plains[depth];

Plain  final_plain;



uint32_t
current_time;


void
change_time(uint32_t  t)
{
  current_time = t;
}


uint32_t
get_time()
{
  return current_time;
}


void
compose_plains_all()
{
  final_plain.fill();

    for(auto&  pln: plains)
    {
      final_plain.compose(pln);
    }
}




}




