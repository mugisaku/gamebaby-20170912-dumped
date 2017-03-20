#include"rogie_item.hpp"
#include<new>




Item::Item(             ):kind(ItemKind::null){}
Item::Item(Firearm&&  fa):kind(ItemKind::firearm){new(&data) Firearm(std::move(fa));}
Item::Item(Ammo&&     am):kind(ItemKind::ammo){new(&data) Ammo(std::move(am));}


Item::Item(      Item&&  rhs) noexcept: kind(ItemKind::null){*this = std::move(rhs);}
Item::Item(const Item&   rhs) noexcept: kind(ItemKind::null){*this =          (rhs);}




Item&
Item::
operator=(Item&&  rhs) noexcept
{
  clear();

  std::swap(kind,rhs.kind);

    switch(kind)
    {
  case(ItemKind::firearm):
      new(&data) Firearm(std::move(rhs.data.firearm));
      break;
  case(ItemKind::ammo):
      new(&data) Ammo(std::move(rhs.data.ammo));
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
  case(ItemKind::ammo):
      new(&data) Ammo(rhs.data.ammo);
      break;
    }


  return *this;
}




Item::
operator bool() const
{
  return(kind != ItemKind::null);
}


void
Item::
clear()
{
    switch(kind)
    {
  case(ItemKind::firearm):
      break;
  case(ItemKind::ammo):
      break;
    }


  kind = ItemKind::null;
}




