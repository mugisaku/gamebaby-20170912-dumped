#ifndef RPG_CORE_HPP_INCLUDED
#define RPG_CORE_HPP_INCLUDED


#include"rpg_point.hpp"
#include"gmbb.hpp"
#include<vector>




namespace gmbb{
namespace rpg{


struct
Square
{
  int  attribute=0;

  Point  lower;
  Point  upper;

};


struct
SquareMap
{
  int  width;
  int  height;

  std::vector<Square>  table;

  Square&  get(int  x, int  y){return table[(width*y)+x];}
  const Square&  get(int  x, int  y) const{return table[(width*y)+x];}

};


namespace core{


const SquareMap&  get_squaremap();

void   load_bg_image(const char*  path);
void   load_bg_map(const char*  path);

void  step(Controller&  ctrl);

void  render(Image&  dst);


}}}


#endif




