#ifndef GAME_TAGTABLE_HPP_INCLUDED
#define GAME_TAGTABLE_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>
#include<vector>
#include<initializer_list>
#include"cbes_window.hpp"




struct Tag;


class
TagTable: public cbes::Object
{
  Tag*  tag_table[5*3];

  int  tag_x;
  int  tag_y;

public:
  Tag*  get_tag() const;

  int  refresh_by_destinations();
  int  refresh_by_items();
  int  refresh_by_belongings();

  void  process(Controller&  ctrl) override;

  void  render(cbes::CharacterTable&  dst) override;

};




#endif




