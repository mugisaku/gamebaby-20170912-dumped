#ifndef RPG_SCENE_HPP_INCLUDED
#define RPG_SCENE_HPP_INCLUDED


#include"gmbb.hpp"
#include"rpg_event.hpp"




namespace gmbb{
namespace rpg{


struct
Scene
{
  const char*  name;

  const Event*  event_table;

};



}}


#endif




