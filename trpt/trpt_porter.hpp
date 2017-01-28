#ifndef TRPT_PORTER_HPP
#define TRPT_PORTER_HPP


#include<string>


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
  const char16_t*  hobby;
  const char16_t*  wish;

  int  foods_amount;

  struct Energy{
    static constexpr int  value_max = 100;

    int  value;

    int  subtract_amount;

  } energy;

  Facility*  facility;

  Porter(const char16_t*  name_, Facility*  fa=nullptr);

  bool  operator()(ActionKind  k);

};


}}


#endif




