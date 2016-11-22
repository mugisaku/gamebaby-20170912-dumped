#ifndef GMBB_SPRITE_HPP
#define GMBB_SPRITE_HPP


#include"gmbb_image.hpp"
#include"gmbb_object.hpp"


namespace gmbb{


struct Garden;


struct
Sprite
{
  Point         point;
  Point  source_point;

  int  width;
  int  height;

  const Image*  source;

  Garden*  garden;

  Sprite*  previous;
  Sprite*      next;

public:
  Sprite(const Image*  src=nullptr, int  x=0, int  y=0, int  w=0, int  h=0);


  void  reset(const Image*  src=nullptr, int  x=0, int  y=0, int  w=0, int  h=0);

  void  change_garden(Garden*  gar);
  void  change_previous(Sprite*  spr);
  void  change_next(Sprite*  spr);

  Garden*    get_garden() const;
  Sprite*  get_previous() const;
  Sprite*      get_next() const;

  void  render(Plain&  dst);

};


}




#endif




