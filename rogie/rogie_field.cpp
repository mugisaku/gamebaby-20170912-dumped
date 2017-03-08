#include"rogie_field.hpp"




Field::
Field()
{
  prepare();
}




void
Field::
prepare()
{
    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x <  width;  ++x){
      auto&  target = table[y][x];

      target.clear();

      target.point.reset(x,y);

      const bool  left_is_valid = (x             );
      const bool  back_is_valid = (y             );
      const bool right_is_valid = (x < ( width-1));
      const bool front_is_valid = (y < (height-1));

        if( left_is_valid){target[Direction::left ] = &table[y  ][x-1];}
        if( back_is_valid){target[Direction::back ] = &table[y-1][x  ];}
        if(right_is_valid){target[Direction::right] = &table[y  ][x+1];}
        if(front_is_valid){target[Direction::front] = &table[y+1][x  ];}


        if( back_is_valid &&  left_is_valid){target[Direction::back_left  ] = &table[y-1][x-1];}
        if( back_is_valid && right_is_valid){target[Direction::back_right ] = &table[y-1][x+1];}
        if(front_is_valid &&  left_is_valid){target[Direction::front_left ] = &table[y+1][x-1];}
        if(front_is_valid && right_is_valid){target[Direction::front_right] = &table[y+1][x+1];}
    }}
}




void
Field::
render(gmbb::Image&  dst) const
{
    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x <  width;  ++x){

    }}
}





