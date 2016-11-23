#ifndef TEXTADV_ITEM_HPP_INCLUDED
#define TEXTADV_ITEM_HPP_INCLUDED


#include<cstdint>
#include<initializer_list>
#include"ta_routine.hpp"




constexpr uint32_t  hiding_flag = 1;


class
FlagSet
{
  uint32_t  data;

public:
  constexpr FlagSet(uint32_t  v=0): data(v){}

  void    set(uint32_t  flag){data |=  flag;}
  void  unset(uint32_t  flag){data &= ~flag;}
  void  clear(){data = 0;}

  FlagSet&  operator&=(const FlagSet&  rhs){  data &= rhs.data;  return *this;}

  uint32_t  test(uint32_t  flag) const{return data&flag;}

};


using Reaction = int  (*)();


struct
Tag
{
  const char16_t*  name;

  Reaction  reaction;

  FlagSet  flags;

public:
  constexpr Tag(const char16_t*  name_, Reaction  r):
  name(name_),
  reaction(r){} 

  int  react() const{  if(reaction){return reaction();}  return 0;};

  FlagSet&  get_flags(){return flags;}

};


struct
Item: public Tag
{
  Item(const char16_t*  name_, Reaction  react_):
  Tag(name_,react_){}

};


struct
HidingItem: public Item
{
  HidingItem(const char16_t*  name_, Reaction  react_):
  Item(name_,react_){flags.set(hiding_flag);}

};




#endif




