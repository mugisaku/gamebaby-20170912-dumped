#ifndef GMBB_GARDEN_HPP
#define GMBB_GARDEN_HPP


#include"gmbb_image.hpp"


namespace gmbb{


struct Sprite;


class
Garden
{
  int  number;

  Sprite*  first;
  Sprite*   last;

public:
  Garden();


  void    join(Sprite&  spr);
  void  unjoin(Sprite&  spr);

  int  get_number() const;

  void  render(Plain&  dst);

};


}




#endif




