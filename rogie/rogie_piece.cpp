#include"rogie_piece.hpp"




gmbb::Image
Piece::
sprite_image;


Piece::
Piece():
direction(Direction::front)
{
}


void
Piece::
move_advance()
{
  auto  ln = (*current_square)[direction];

    if(ln)
    {
         if(!ln->current_piece)
         {
           ln->current_piece = this;

           current_square->current_piece = nullptr;

           current_square = ln;
         }
    }
}


void
Piece::
move_back()
{
  auto  ln = (*current_square)[opposite(direction)];

    if(ln)
    {
         if(!ln->current_piece)
         {
           ln->current_piece = this;

           current_square->current_piece = nullptr;

           current_square = ln;
         }
    }
}


void
Piece::
turn_left()
{
    switch(direction)
    {
  case(Direction::back_left  ): direction = Direction::left       ;break;
  case(Direction::back       ): direction = Direction::back_left  ;break;
  case(Direction::back_right ): direction = Direction::back       ;break;
  case(Direction::left       ): direction = Direction::front_left ;break;
  case(Direction::right      ): direction = Direction::back_right ;break;
  case(Direction::front_left ): direction = Direction::front      ;break;
  case(Direction::front      ): direction = Direction::front_right;break;
  case(Direction::front_right): direction = Direction::right      ;break;
    }
}


void
Piece::
turn_right()
{
    switch(direction)
    {
  case(Direction::back_left  ): direction = Direction::back       ;break;
  case(Direction::back       ): direction = Direction::back_right ;break;
  case(Direction::back_right ): direction = Direction::right      ;break;
  case(Direction::left       ): direction = Direction::back_left  ;break;
  case(Direction::right      ): direction = Direction::front_right;break;
  case(Direction::front_left ): direction = Direction::left       ;break;
  case(Direction::front      ): direction = Direction::front_left ;break;
  case(Direction::front_right): direction = Direction::front      ;break;
    }
}


void
Piece::
render(gmbb::Image&  dst, int  x, int  y) const
{
  int  src_y = 0;

  bool  rev = false;

    switch(direction)
    {
  case(Direction::back_left):
      src_y = 4;
      break;
  case(Direction::back):
      src_y = 2;
      break;
  case(Direction::back_right):
      src_y = 4;
      rev = true;
      break;
  case(Direction::left):
      src_y = 1;
      break;
  case(Direction::right):
      src_y = 1;
      rev = true;
      break;
  case(Direction::front_left):
      src_y = 3;
      break;
  case(Direction::front):
      break;
  case(Direction::front_right):
      src_y = 3;
      rev = true;
      break;
    }


  sprite_image.transfer(0,48*src_y,rev? -24:24,48,dst,24*current_square->point.x,(24*current_square->point.y)-24);
}


bool
Piece::
compare(Piece*  a, Piece*  b)
{
  return a->current_square->point.y < b->current_square->point.y;
}




