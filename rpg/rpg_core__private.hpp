#ifndef RPG_CORE_PRIVATE_HPP_INCLUDED
#define RPG_CORE_PRIVATE_HPP_INCLUDED


#include"rpg_core.hpp"
#include"rpg_routine.hpp"




namespace gmbb{
namespace rpg{


namespace core{


extern Image         bg_image;
extern Image  character_image;

extern Media media;


extern SquareMap  map;


extern Player  player;


extern Garden  gard0;
extern Garden  gard1;
extern Garden  gard2;


extern const Scene      living_scene;
extern const Scene        main_scene;
extern const Scene  bathtoilet_scene;


extern Message  message;


const File*  load_file(const char*  path);


}}}


#endif




