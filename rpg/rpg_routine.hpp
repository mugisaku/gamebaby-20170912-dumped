#ifndef RPG_ROUTINE_HPP_INCLUDED
#define RPG_ROUTINE_HPP_INCLUDED


#include"rpg_player.hpp"
#include"core/gmbb_image.hpp"
#include<vector>




namespace gmbb{
namespace rpg{


void     move_up(Player&  pl);
void   move_left(Player&  pl);
void  move_right(Player&  pl);
void   move_down(Player&  pl);

void  walk(Player&  pl, const Controller&  ctrl);


void  shapeshift(const Player&  ply, Sprite&  spr);


}}


#endif




