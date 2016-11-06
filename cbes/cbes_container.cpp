#include"cbes_container.hpp"


namespace cbes{




void
Container::
join(Object*  obj, int  x, int  y)
{
    if(obj)
    {
      object_list.emplace_back(obj);

      obj->change_parent(this,x,y);
    }
}


void
Container::
update()
{
    for(auto  obj: object_list)
    {
      obj->update();
    }
}


void
Container::
process(Controller&  ctrl)
{
    for(auto  obj: object_list)
    {
      obj->process(ctrl);
    }
}


void
Container::
render(CharacterTable&  dst)
{
    for(auto  obj: object_list)
    {
      obj->render(dst);
    }
}




}




