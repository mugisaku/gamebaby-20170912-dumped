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
}


const Point&
Object::
get_relative_point() const
{
  return relative_point;
}


Point
Object::
get_absolute_point() const
{
    if(parent)
    {
      auto  pt = parent->get_absolute_point();

      return Point(pt.x+relative_point.x,
                   pt.y+relative_point.y);
    }


  return relative_point;
}


int  Object::get_width( ) const{return  width;}
int  Object::get_height() const{return height;}


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
process(Controller&  ctrl, int  x, int  y)
{
}


void
Object::
render(Image&  dst)
{
}




}




