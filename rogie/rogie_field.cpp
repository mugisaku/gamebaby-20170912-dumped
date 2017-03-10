#include"rogie_field.hpp"




Field::
Field():
master(nullptr)
{
  prepare();
}




void
Field::
put(Piece*  p)
{
    if(p)
    {
      piece_list.emplace_back(p);


      auto&  sq = table[0][0];

      p->current_square = &sq;

      sq.current_piece = p;

        if(!master)
        {
          master = p;
        }
    }
}


void
Field::
process(const gmbb::Controller&  ctrl)
{
    if(master->context_stack.empty())
    {
        if(ctrl.test_pressed(gmbb::p_flag))
        {
          master->use_weapon();
        }

      else
        if(ctrl.test_pressed(gmbb::left_flag))
        {
          master->turn_left();
        }

      else
        if(ctrl.test_pressed(gmbb::right_flag))
        {
          master->turn_right();
        }

      else
        if(ctrl.test_pressed(gmbb::up_flag))
        {
          master->move_advance();
        }

      else
        if(ctrl.test_pressed(gmbb::down_flag))
        {
          master->move_back();
        }
    }
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
render(gmbb::Image&  dst)
{
    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x <  width;  ++x){
      dst.fill_rectangle(4|8,24*x,24*y,24,24);
    }}


  piece_list.sort(Piece::compare);

    for(auto  p: piece_list)
    {
      p->render(dst,0,0);
    }
}





