#ifndef RPG_ROUTINE_HPP_INCLUDED
#define RPG_ROUTINE_HPP_INCLUDED


#include"rpg_player.hpp"
#include"core/gmbb_image.hpp"
#include<vector>




namespace gmbb{
namespace rpg{


Counter  move_to_front(Context&  ctx);
Counter   move_to_left(Context&  ctx);
Counter  move_to_right(Context&  ctx);
Counter   move_to_back(Context&  ctx);

Counter  walk_to_front(Context&  ctx);
Counter   walk_to_left(Context&  ctx);
Counter  walk_to_right(Context&  ctx);
Counter   walk_to_back(Context&  ctx);

Counter  turn_to_front(Context&  ctx);
Counter   turn_to_left(Context&  ctx);
Counter  turn_to_right(Context&  ctx);
Counter   turn_to_back(Context&  ctx);


Counter    set_quiet(Context&  ctx);
Counter  unset_quiet(Context&  ctx);

Counter    set_facefixed(Context&  ctx);
Counter  unset_facefixed(Context&  ctx);

Counter   rest(Context&  ctx);

void  basic_play(Player&  pl, const Controller&  ctrl);


void  basic_shapeshift(const Player&  ply, Sprite&  spr);
void  bathtime_shapeshift(const Player&  ply, Sprite&  spr);


}}


#endif




