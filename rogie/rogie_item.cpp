#include"rogie_item.hpp"
#include<new>




Item::Item(             ):kind(ItemKind::null){}
Item::Item(Firearm&&  fa):kind(ItemKind::firearm){new(&data) Firearm(std::move(fa));}


Item::Item(      Item&&  rhs) noexcept: kind(ItemKind::null){*this = std::move(rhs);}
Item::Item(const Item&   rhs) noexcept: kind(ItemKind::null){*this =          (rhs);}




Item&
Item::
operator=(Item&&  rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(ItemKind::firearm):
      new(&data) Firearm(std::move(rhs.data.firearm));
      break;
    }


  return *this;
}


Item&
Item::
operator=(const Item&   rhs) noexcept
{
  clear();

  kind = rhs.kind;

    switch(kind)
    {
  case(ItemKind::firearm):
      new(&data) Firearm(rhs.data.firearm);
      break;
    }


  return *this;
}




void
Item::
clear()
{
    switch(kind)
    {
  case(ItemKind::firearm):
      break;
    }


  kind = ItemKind::null;
}




