#include"rogie_field.hpp"




Field::
Field():
master(nullptr)
{
  prepare();
}




void
Field::
put(Piece*  p, int  x, int  y)
{
    if(p)
    {
      auto&  sq = table[x][y];

        if(sq.current_piece)
        {
          printf("既に駒があります\n");

          throw;
        }


      piece_list.emplace_back(p);

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
//          master->move_back();
prepare_to_search();
master->current_square->search(master);
        }


/*
      auto&  a = master->action_currency;

        if(a < 0)
        {
            for(auto  p:  piece_list)
            {
                if(p != master)
                {
                  p += -a;
                }
            }


          a = 0;
        }
*/
    }
}


void
Field::
cycle()
{
    for(auto  p: piece_list)
    {
      p->step();

/*
        if(p != master)
        {
            if(p->action_currency)
            {
              search(p->current_square);
            }
        }
*/
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


  image.resize(24*width,24*height);

  image.fill(4|8);

    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x <  width;  ++x){
      image.rectangle(3|8,24*x,24*y,24,24);
    }}

}


void
Field::
prepare_to_search()
{
    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x <  width;  ++x){
      table[y][x].reaching_cost = 9999;
    }}
}


void
Field::
render(gmbb::Image&  dst)
{
  dst.fill(0);

  image.transfer(0,0,0,0,dst,12,12);


  piece_list.sort(Piece::compare);

    for(auto  p: piece_list)
    {
      p->render(dst,12,12);
    }


  gmbb::Formatted  fmt;

  dst.print(fmt("%4d",master->current_square->reaching_cost),4|8,0,0);
}





