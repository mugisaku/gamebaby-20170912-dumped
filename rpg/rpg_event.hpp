#ifndef RPG_EVENT_HPP_INCLUDED
#define RPG_EVENT_HPP_INCLUDED


#include"gmbb.hpp"




namespace gmbb{
namespace rpg{


struct Square;


enum class
Trigger
{
  begin_to_enter,
    end_to_enter,
  begin_to_leave,
    end_to_leave,

  press,

};


struct
Event
{
  const char*  name;

  using Process = void  (*)(Square&  sq, Trigger  trig);

  Process  process;

  Event(const char*  name_, Process  proc):
  name(name_),
  process(proc){}

  void  operator()(Square&  sq, Trigger  trig) const{if(process){process(sq,trig);}}

};


}}


#endif




