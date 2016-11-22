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
render(Plain&  dst)
{
    for(auto  obj: children)
    {
      obj->render(dst);
    }
}




}




