#include"game_place.hpp"
#include"gmbb.hpp"




Place::
Place(const char16_t*  name_, Reaction  r,
      std::initializer_list<Place*>  plc_ls,
      std::initializer_list< Item*>  itm_ls):
Tag(name_,r),
linked_place_list(plc_ls),
item_list(itm_ls)
{
}


HidingPlace::
HidingPlace(const char16_t*  name_, Reaction  r,
      std::initializer_list<Place*>  plc_ls,
      std::initializer_list< Item*>  itm_ls):
Place(name_,r,plc_ls,itm_ls)
{
  flags.set(hiding_flag);
}





