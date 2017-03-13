#ifndef ROGIE_DIRECTION_HPP_INCLUDED
#define ROGIE_DIRECTION_HPP_INCLUDED




enum class
Direction
{
  front,
  front_left,
  left,
  back_left,
  back,
  back_right,
  right,
  front_right,

  END,

};


constexpr int  number_of_directions = static_cast<int>(Direction::END);


constexpr int
get_distance(Direction  a_dir, Direction  b_dir)
{
  auto  a = static_cast<int>(a_dir);
  auto  b = static_cast<int>(b_dir);

  constexpr int  table[] = {0,1,2,3,4,3,2,1};

  return table[(a < b)? b-a:a-b];
}


constexpr const char*
get_name(Direction  d)
{
    switch(d)
    {
  case(Direction::back_left  ): return "front_right";
  case(Direction::back       ): return "front"      ;
  case(Direction::back_right ): return "front_left" ;
  case(Direction::left       ): return "right"      ;
  case(Direction::right      ): return "left"       ;
  case(Direction::front_left ): return "back_right" ;
  case(Direction::front      ): return "back"       ;
  case(Direction::front_right): return "back_left"  ;
    }


  return "";
}


constexpr Direction
get_opposite(Direction  d)
{
    switch(d)
    {
  case(Direction::back_left  ): return Direction::front_right;
  case(Direction::back       ): return Direction::front      ;
  case(Direction::back_right ): return Direction::front_left ;
  case(Direction::left       ): return Direction::right      ;
  case(Direction::right      ): return Direction::left       ;
  case(Direction::front_left ): return Direction::back_right ;
  case(Direction::front      ): return Direction::back       ;
  case(Direction::front_right): return Direction::back_left  ;
    }


  return Direction::front;
}


constexpr Direction
get_left(Direction  d)
{
    switch(d)
    {
  case(Direction::back_left  ): return Direction::left       ;
  case(Direction::back       ): return Direction::back_left  ;
  case(Direction::back_right ): return Direction::back       ;
  case(Direction::left       ): return Direction::front_left ;
  case(Direction::right      ): return Direction::back_right ;
  case(Direction::front_left ): return Direction::front      ;
  case(Direction::front      ): return Direction::front_right;
  case(Direction::front_right): return Direction::right      ;
    }


  return Direction::front;
}


constexpr Direction
get_right(Direction  d)
{
    switch(d)
    {
  case(Direction::back_left  ): return Direction::back       ;
  case(Direction::back       ): return Direction::back_right ;
  case(Direction::back_right ): return Direction::right      ;
  case(Direction::left       ): return Direction::back_left  ;
  case(Direction::right      ): return Direction::front_right;
  case(Direction::front_left ): return Direction::left       ;
  case(Direction::front      ): return Direction::front_left ;
  case(Direction::front_right): return Direction::front      ;
    }


  return Direction::front;
}




constexpr bool
is_diagonal(Direction  d)
{
  return((d == Direction::back_left  ) ||
         (d == Direction::back_right ) ||
         (d == Direction::front_left ) ||
         (d == Direction::front_right));
}




#endif




