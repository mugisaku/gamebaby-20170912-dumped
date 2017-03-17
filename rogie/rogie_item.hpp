#ifndef ROGIE_ITEM_HPP_INCLUDED
#define ROGIE_ITEM_HPP_INCLUDED


#include"rogie_firearm.hpp"




enum class
ItemKind
{
  null,
  firearm,

};


union
ItemData
{
  Firearm  firearm;

   ItemData(){}
  ~ItemData(){}

};


struct
Item
{
  ItemKind  kind;
  ItemData  data;

public:
  Item();
  Item(Firearm&&  fa);
  Item(      Item&&  rhs) noexcept;
  Item(const Item&   rhs) noexcept;

  Item&  operator=(      Item&&  rhs) noexcept;
  Item&  operator=(const Item&   rhs) noexcept;

  operator bool() const;

  void  clear();

};




#endif




