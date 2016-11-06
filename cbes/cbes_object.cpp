#include"cbes_object.hpp"




namespace cbes{




Object::
Object():
parent(nullptr)
{
}


Object::
~Object()
{
}




const Rectangle&
Object::
get_rectangle() const
{
  return *this;
}


void
Object::
change_width(int  v)
{
  Rectangle::width = v;
}


void
Object::
change_height(int  v)
{
  Rectangle::height = v;
}


void
Object::
change_parent(Object*  obj, int  x, int  y)
{
  parent = obj;

  change_point(x,y);
}


void
Object::
change_point(int  x, int  y)
{
  relative_point.x = x;
  relative_point.y = y;

  point = relative_point;

    if(parent)
    {
      point.x += parent->point.x;
      point.y += parent->point.y;
    }
}


void
Object::
update()
{
}


void
Object::
process(Controller&  ctrl)
{
}


void
Object::
render(CharacterTable&  dst)
{
}




}




