#ifndef ROGIE_BASIC_CALLBACK_HPP_INCLUDED
#define ROGIE_BASIC_CALLBACK_HPP_INCLUDED


#include<rogie_piece.hpp>


namespace basic_callback{


void  move_to_direction(Context&  ctx);

void  turn_left( Context&  ctx);
void  turn_right(Context&  ctx);

void  punch(Context&  ctx);
void  damage(Context&  ctx);


void  chase_hero(Context&  ctx);
void  runaway_from_hero(Context&  ctx);
void  attack_hero(Context&  ctx);


}



#endif




