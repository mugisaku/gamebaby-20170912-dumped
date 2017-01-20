#ifndef TRPT_FACILITY_HPP
#define TRPT_FACILITY_HPP


#include<string>
#include<list>
#include"gmbb.hpp"


namespace gmbb{
namespace trpt{


enum class
FacilityKind
{
  null,

  village,
  town,

};


struct Town;


struct
Facility
{
  const char16_t*  name;

  FacilityKind  kind;

  Town*  town;

  void  draw_comment(Image&  dst, int  x, int  y) const;

};


}}


#endif




