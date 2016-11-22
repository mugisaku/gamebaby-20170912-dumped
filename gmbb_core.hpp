#ifndef GMBB_CORE_HPP_INCLUDED
#define GMBB_CORE_HPP_INCLUDED


#include"gmbb_plain.hpp"


namespace gmbb{


constexpr int  depth = 4;


extern Plain  plains[depth];

extern Plain  final_plain;

void  compose_plains_all();


void      change_time(uint32_t  t);
uint32_t  get_time();


}


#endif




