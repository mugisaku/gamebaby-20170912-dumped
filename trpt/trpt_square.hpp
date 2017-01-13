#ifndef TRPT_SQUARE_HPP
#define TRPT_SQUARE_HPP


#include"trpt_player.hpp"
#include<string>


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


struct
Feature
{
  const char16_t*  name;

};


struct
Square
{
  SquareKind  kind;

  Point  image_point;

  const Feature*  feature;

  Square();

};


}}


#endif




