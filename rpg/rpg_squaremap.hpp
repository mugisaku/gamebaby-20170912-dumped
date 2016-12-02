#ifndef RPG_SQUAREMAP_HPP_INCLUDED
#define RPG_SQUAREMAP_HPP_INCLUDED


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


class
SquareMap
{
  const Image*  source_image;

  int  width;
  int  height;

  std::vector<Square>  table;

public:
        Square&  get(int  x, int  y)      ;
  const Square&  get(int  x, int  y) const;

  void  render_lower(Image&  dst) const;
  void  render_upper(Image&  dst) const;

  void  change_source(Image&  img);

  void  load(const char*  path);

};


}}


#endif




