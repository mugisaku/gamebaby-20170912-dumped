#ifndef TRPT_SQUARE_HPP
#define TRPT_SQUARE_HPP


#include<string>
#include"gmbb.hpp"


namespace gmbb{
namespace trpt{


enum class
SquareKind
{
  null,

  plain,
  waste,
  mud,
  sand,
  snow,
  ice,
  grass,
  river,
  forest,
  mountain,
  see,

};


const char16_t*  get_name(SquareKind  k);
int  get_resistance(SquareKind  k);


struct Facility;


struct
Square
{
  Point  index;

  SquareKind  kind;

  Point  image_point;

  Facility*  facility;

  Square();

};


}}


#endif




