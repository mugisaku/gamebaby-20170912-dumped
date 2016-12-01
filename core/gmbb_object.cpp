#include"gmbb_object.hpp"




namespace gmbb{




Object::
Object():
parent(nullptr),
width(0),
height(0)
{
}


Object::
~Object()
{
}




void
Object::
change_width(int  v)
{
  width = v;
}


void
Object::
change_height(int  v)
{
  height = v;
}


void
Object::
change_parent(Object&  new_parent, int  x, int  y)
{
  parent = &new_parent;

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
render(Image&  dst)
{
}




}




