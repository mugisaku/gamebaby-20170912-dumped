#ifndef TRPT_PORTER_HPP
#define TRPT_PORTER_HPP


#include<string>


namespace gmbb{
namespace trpt{


struct Facility;


struct
Porter
{
  int  offense;
  int  defense;

  int  physical_fitness=8;
  int    mental_fitness=8;
  int  ardor=8;
  int  charm=8;
  int  luck=8;

  const char16_t*  name;
  const char16_t*  hobby;
  const char16_t*  wish;

  int  weight=40;
  int  power_max=300;
  int  power_consumed=0;
  int  foods=100;
  int  nutrient=100;

  Facility*  facility;

  Porter(const char16_t*  name_, Facility*  fa=nullptr);

};


}}


#endif




