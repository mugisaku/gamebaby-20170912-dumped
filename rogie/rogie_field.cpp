#include"rogie_field.hpp"
#include<limits>




Field::
Field():
master(nullptr)
{
  push_task_to_last(process_input);
  push_task_to_last(manage_pieces);
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

          master->set_flag(Piece::master_flag);
        }
    }
}


void
Field::
put(Item&&  itm, int  x, int  y)
{
  auto&  sq = table[x][y];

  sq.placed_item = std::move(itm);
}


void
Field::
prepare()
{
    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x <  width;  ++x){
      auto&  target = table[y][x];

      target.clear();

      target.field = this;

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

  update_image();
}


void
Field::
update_image()
{
    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x <  width;  ++x){
      update_image(x,y);
    }}
}


void
Field::
update_image(int  x, int  y)
{
  auto  xx = 24*x;
  auto  yy = 24*y;

  image.fill_rectangle(3|8,xx,yy,24,24);
  image.rectangle(     4|8,xx,yy,24,24);

  auto&  sq = table[y][x];

    switch(sq.placed_item.kind)
    {
  case(ItemKind::firearm):
        switch(sq.placed_item.data.firearm.kind)
        {
      case(FirearmKind::handgun):
          Piece::sprite_image.transfer(48,24*10,24,24,image,xx,yy);
          break;
      case(FirearmKind::submachinegun):
          Piece::sprite_image.transfer(48,24*11,24,24,image,xx,yy);
          break;
        }
      break;
    }
}


void
Field::
prepare_to_search()
{
    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x <  width;  ++x){
      auto&  sq = table[y][x];

      sq.distance = std::numeric_limits<int>::max();
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


  dst.print_tall(master->test_flag(Piece::use_gun_flag)? "ハンドガン":"パンチ",4|8,180,0);
}


void
Field::
print() const
{
  printf("{\n");

    for(int  y = 0;  y < height;  ++y)
    {
        for(int  x = 0;  x <  width;  ++x)
        {
          auto&  sq = table[y][x];

          printf("%6d,",sq.current_piece? 1:0);
        }


      printf("\n");
    }


  printf("}\n\n");
}




