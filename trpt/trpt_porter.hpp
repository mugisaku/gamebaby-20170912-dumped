#ifndef TRPT_PORTER_HPP
#define TRPT_PORTER_HPP


#include<string>


namespace gmbb{
namespace trpt{


struct
Porter
{
  int  offense;
  int  defense;
  int  physical;
  int  mental;
  int  fame;
  int  charm;
  int  luck;

  const char16_t*  name;
  const char16_t*  hobby;
  const char16_t*  wish;

  int  weight=40;
  int  power_max=300;
  int  power_consumed=0;
  int  foods=100;
  int  nutrient=100;

  Porter(const char16_t*  name_);

};


}}


#endif




