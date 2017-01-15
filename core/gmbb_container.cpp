#include"gmbb_container.hpp"


namespace gmbb{




void
Container::
join(Object*  obj, int  x, int  y)
{
    if(obj)
    {
      children.emplace_back(obj);

      obj->change_parent(*this,x,y);
    }
}


void
Container::
update()
{
    for(auto  obj: children)
    {
      obj->update();
    }
}


void
Container::
process(Controller&  ctrl)
{
    for(auto  obj: children)
    {
      obj->process(ctrl);
    }
}


void
Container::
process(Controller&  ctrl, int  x, int  y)
{
    for(auto  obj: children)
    {
      auto  pt = obj->get_relative_point();

         if((x >= pt.x) &&
            (y >= pt.y) &&
            (x <  (pt.x+obj->get_width( ))) &&
            (y <  (pt.y+obj->get_height())))
         {
           obj->process(ctrl,x-pt.x,y-pt.y);
         }
    }
}


void
Container::
render(Image&  dst)
{
    for(auto  obj: children)
    {
      obj->render(dst);
    }
}




}




