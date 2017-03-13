#ifndef ROGIE_BASIC_CALLBACK_HPP_INCLUDED
#define ROGIE_BASIC_CALLBACK_HPP_INCLUDED


#include<rogie_piece.hpp>


namespace basic_callback{


void  move_to_direction(Context&  ctx, Piece&  p);

void  turn_left( Context&  ctx, Piece&  p);
void  turn_right(Context&  ctx, Piece&  p);

void  punch(Context&  ctx, Piece&  p);
void  damage(Context&  ctx, Piece&  p);


void  chase_hero(Context&  ctx, Piece&  p);
void  runaway_from_hero(Context&  ctx, Piece&  p);
void  attack_hero(Context&  ctx, Piece&  p);


}



#endif




