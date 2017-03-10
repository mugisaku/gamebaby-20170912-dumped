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
  case(0):
      p.set_shape_by_direction();
      p.set_offset_by_direction();

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
      p.set_shape_by_direction();

      p.rendering_src_offset.x = 24*3;

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




