#ifndef TRPT_TOWN_HPP
#define TRPT_TOWN_HPP


#include<string>
#include<list>


namespace gmbb{
namespace trpt{


struct Porter;


struct
Town
{
  std::list<Porter*>  porter_list;

};


}}


#endif




