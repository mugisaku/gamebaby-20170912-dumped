#ifndef RPG_CORE_PRIVATE_HPP_INCLUDED
#define RPG_CORE_PRIVATE_HPP_INCLUDED


#include"rpg_core.hpp"
#include"rpg_routine.hpp"




namespace gmbb{
namespace rpg{


namespace core{


extern Image         bg_image;
extern Image  character_image;


extern SquareMap  map;


extern Player  player;


extern Garden  gard0;
extern Garden  gard1;
extern Garden  gard2;


extern const Event      living_event_table[];
extern const Event        main_event_table[];
extern const Event  bathtoilet_event_table[];


}}}


#endif




