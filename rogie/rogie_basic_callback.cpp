#include"rogie_basic_callback.hpp"




namespace basic_callback{




void
move_to_direction(Context&  ctx, Piece&  p)
{
  auto&          phase = ctx.memory[0];
  auto&        counter = ctx.memory[1];
  auto&  sleep_counter = ctx.memory[2];

  auto&  x = p.rendering_dst_offset.x;
  auto&  y = p.rendering_dst_offset.y;

  auto&  src_x = p.rendering_src_offset.x;

       if(counter > 20){src_x = 24;}
  else if(counter > 16){src_x =  0;}
  else if(counter > 12){src_x = 48;}
  else if(counter >  8){src_x =  0;}
  else if(counter >  4){src_x = 24;}
  else if(counter >  0){src_x =  0;}

    switch(phase)
    {
  case(0): {
      auto  ln = (*p.current_square)[p.direction];

        if(!ln || ln->current_piece)
        {
          p.pop_context();
        }


      ln->current_piece = &p;

      p.current_square->current_piece = nullptr;

      p.current_square = ln;


      p.rendering_dst_offset.x = 0;
      p.rendering_dst_offset.y = 0;

      p.set_shape_by_direction();
      p.add_offset_by_direction(-24);

      p.rendering_src_offset.x = 0;
      p.rendering_src_offset.y = 0;

      counter = 24;

      ++phase;
      }break;
  case(1):
        if(sleep_counter)
        {
          --sleep_counter;
        }

      else
        if(counter--)
        {
               if(x < 0){++x;}
          else if(x > 0){--x;}


               if(y < 0){++y;}
          else if(y > 0){--y;}

          sleep_counter = 2;
        }

      else
        {
          p.pop_context();
        }
      break;
    }
}




void
move_to_opposite_direction(Context&  ctx, Piece&  p)
{
  auto&          phase = ctx.memory[0];
  auto&        counter = ctx.memory[1];
  auto&  sleep_counter = ctx.memory[2];

  auto&  x = p.rendering_dst_offset.x;
  auto&  y = p.rendering_dst_offset.y;

  auto&  src_x = p.rendering_src_offset.x;

       if(counter > 20){src_x = 24;}
  else if(counter > 16){src_x =  0;}
  else if(counter > 12){src_x = 48;}
  else if(counter >  8){src_x =  0;}
  else if(counter >  4){src_x = 24;}
  else if(counter >  0){src_x =  0;}

    switch(phase)
    {
  case(0):
      p.rendering_dst_offset.x = 0;
      p.rendering_dst_offset.y = 0;

      p.set_shape_by_direction();
      p.add_offset_by_direction(24);

      p.rendering_src_offset.x = 0;
      p.rendering_src_offset.y = 0;

      counter = 24;

      ++phase;
      break;
  case(1):
        if(sleep_counter)
        {
          --sleep_counter;
        }

      else
        if(counter--)
        {
               if(x < 0){++x;}
          else if(x > 0){--x;}


               if(y < 0){++y;}
          else if(y > 0){--y;}

          sleep_counter = 2;
        }

      else
        {
          p.pop_context();
        }
      break;
    }
}




void
turn_left(Context&  ctx, Piece&  p)
{
  p.change_direction(get_left(p.direction));

  p.pop_context();
}


void
turn_right(Context&  ctx, Piece&  p)
{
  p.change_direction(get_right(p.direction));

  p.pop_context();
}




void
punch(Context&  ctx, Piece&  p)
{
  auto&          phase = ctx.memory[0];
  auto&        counter = ctx.memory[1];
  auto&  sleep_counter = ctx.memory[2];

  auto&  x = p.rendering_dst_offset.x;
  auto&  y = p.rendering_dst_offset.y;

    switch(phase)
    {
  case(0):
      p.rendering_dst_offset.x = 0;
      p.rendering_dst_offset.y = 0;

      p.rendering_src_offset.x = 24*3;

      p.set_shape_by_direction();

      counter = 12;

      ++phase;
      break;
  case(1):
        if(counter--)
        {
          p.add_offset_by_direction(1);
        }

      else
        {
          auto  sq = (*p.current_square)[p.direction];

            if(sq && sq->current_piece)
            {
              sq->current_piece->push_action(damage,0);
            }


          counter = 12;

          ++phase;
        }
      break;
  case(2):
        if(counter--)
        {
          p.rendering_src_offset.x = 0;

          p.add_offset_by_direction(-1);
        }

      else
        {
          p.rendering_src_offset.x = 0;

          p.pop_context();
        }
      break;
    }
}




void
damage(Context&  ctx, Piece&  p)
{
  auto&          phase = ctx.memory[0];
  auto&        counter = ctx.memory[1];
  auto&  sleep_counter = ctx.memory[2];

  auto&  x = p.rendering_dst_offset.x;
  auto&  y = p.rendering_dst_offset.y;

    switch(phase)
    {
  case(0):
      p.rendering_dst_offset.x = 0;
      p.rendering_dst_offset.y = 0;

      p.rendering_src_offset.x = 24*4;

      p.set_shape_by_direction();

      counter = 12;

      ++phase;
      break;
  case(1):
        if(counter--)
        {
        }

      else
        {
          p.rendering_src_offset.x = 0;

          p.pop_context();
        }
      break;
    }
}




}




