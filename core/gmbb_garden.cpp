#include"gmbb_garden.hpp"
#include"gmbb_sprite.hpp"
#include"gmbb_environment.hpp"
#include<cstring>




namespace gmbb{




Garden::
Garden():
number(0),
first(nullptr),
last(nullptr)
{
}




void
Garden::
join(Sprite&  spr)
{
  spr.change_garden(this);

    if(last)
    {
      last->change_next(&spr);
      spr.change_previous(last);
    }

  else
    {
      first = &spr;
    }


  last = &spr;

  number += 1;
}


void
Garden::
unjoin(Sprite&  spr)
{
  auto  garden   = spr.get_garden();
  auto  previous = spr.get_previous();
  auto  next     = spr.get_next();

    if(garden != this)
    {
      printf("属していないスプライトを外そうとしました\n");

      throw;
    }


  spr.change_garden(nullptr);

    if(next)
    {
      next->previous = previous;
    }


    if(previous)
    {
      previous->next = next;
    }


    if(first == &spr)
    {
      first = next;
    }

  else
    if(last == &spr)
    {
      last = previous;
    }


  number -= 1;

    if(!number)
    {
      first = nullptr;
       last = nullptr;
    }
}


int
Garden::
get_number() const
{
  return number;
}


void
Garden::
render(Plain&  dst)
{
  auto  next = first;

    while(next)
    {
      next->render(dst);

      next = next->get_next();
    }
}


}





