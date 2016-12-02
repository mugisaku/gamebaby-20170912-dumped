#ifndef RPG_CORE_HPP_INCLUDED
#define RPG_CORE_HPP_INCLUDED


#include"rpg_squaremap.hpp"
#include"gmbb.hpp"
#include<vector>




namespace gmbb{
namespace rpg{


namespace screen{
constexpr int  width  = 24*12;
constexpr int  height = 24*12;
}


namespace core{


const SquareMap&  get_squaremap();

void  load_character_image(const char*  path);
void   load_bg_image(const char*  path);

void  reset();

void  step(Controller&  ctrl);

void  render(Image&  dst);


}}}


#endif




