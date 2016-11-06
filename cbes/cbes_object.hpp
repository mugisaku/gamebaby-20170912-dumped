#ifndef CBES_OBJECT_HPP
#define CBES_OBJECT_HPP


#include"cbes_rectangle.hpp"
#include"cbes_charactertable.hpp"
#include"gmbb_controller.hpp"


namespace cbes{


class
Object: protected Rectangle
{
protected:
  Object*  parent;

  Point  relative_point;

public:
  Object();

  virtual ~Object();

  const Rectangle&  get_rectangle() const;

  void  change_parent(Object*  parent, int  x, int  y);

  void  change_point(int  x, int  y);

  void  change_width(int  v);
  void  change_height(int  v);

  virtual void  update();

  virtual void  process(Controller&  ctrl);

  virtual void  render(CharacterTable&  dst);

};


}




#endif




