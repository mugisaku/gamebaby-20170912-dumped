#include"gmbb_core.hpp"




namespace gmbb{


Plain  plains[depth];

Plain  final_plain;



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




