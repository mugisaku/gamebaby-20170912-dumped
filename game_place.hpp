#ifndef GAME_PLACE_HPP_INCLUDED
#define GAME_PLACE_HPP_INCLUDED


#include<vector>
#include"game_item.hpp"




struct
Place: public Tag
{
  std::vector<Place*>  linked_place_list;
  std::vector<Item*>           item_list;

  Place(const char16_t*  name_, Reaction  r,
        std::initializer_list<Place*>  plc_ls,
        std::initializer_list< Item*>  itm_ls);

};



struct
HidingPlace: public Place
{
  HidingPlace(const char16_t*  name_, Reaction  r,
        std::initializer_list<Place*>  plc_ls,
        std::initializer_list< Item*>  itm_ls);

};



#endif




