#ifndef TRPT_PORTER_HPP
#define TRPT_PORTER_HPP


#include<string>
#include"trpt_energy.hpp"


namespace gmbb{
namespace trpt{


struct Facility;


enum class
ActionKind
{
  move,

};


struct
Porter
{
  int  physical_fitness=8;
  int    mental_fitness=8;
  int  ardor=8;
  int  charm=8;
  int  luck=8;

  const char16_t*  name;

  int  foods_amount;
  int  moving_capacity;

  Energy energy;

  Facility*  facility;

  Porter(const char16_t*  name_, Facility*  fa=nullptr);

  bool  operator()(ActionKind  k);

};


}}


#endif




