#include"rogie_basic_callback.hpp"
#include"rogie_field.hpp"




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
          ctx.callback = nullptr;

          return;
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
          ctx.callback = nullptr;
        }
      break;
    }
}




void
turn_left(Context&  ctx, Piece&  p)
{
  p.change_direction(get_left(p.direction));

  ctx.callback = nullptr;
}


void
turn_right(Context&  ctx, Piece&  p)
{
  p.change_direction(get_right(p.direction));

  ctx.callback = nullptr;
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
              sq->current_piece->push_context(damage);
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

          ctx.callback = nullptr;
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

          ctx.callback = nullptr;
        }
      break;
    }
}




void
chase_hero(Context&  ctx, Piece&  p)
{
  auto  hero = p.current_square->field->master;

  p.current_square->field->prepare_to_search();
  hero->current_square->search(&p);

  Direction  d;

  Square*  candidate = nullptr;

    for(int  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = p.current_square->link[i];

        if(ln)
        {
            if(!candidate || (ln->distance < candidate->distance))
            {
              candidate = ln;

              d = static_cast<Direction>(i);
            }
        }
    }


    if(candidate)
    {
        if(d == p.direction)
        {
          p.move_advance();
        }

      else
        {
          auto  l = get_left( p.direction);
          auto  r = get_right(p.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){p.turn_left();}
          else                 {p.turn_right();}
        }
    }
}




void
runaway_from_hero(Context&  ctx, Piece&  p)
{
  auto  hero = p.current_square->field->master;

  p.current_square->field->prepare_to_search();
  hero->current_square->search(&p);

  Direction  d;

  Square*  candidate = nullptr;

    for(int  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = p.current_square->link[i];

        if(ln)
        {
            if(!candidate || (ln->distance > candidate->distance))
            {
              candidate = ln;

              d = static_cast<Direction>(i);
            }
        }
    }


    if(candidate)
    {
        if(d == p.direction)
        {
          p.move_advance();
        }

      else
        {
          auto  l = get_left( p.direction);
          auto  r = get_right(p.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){p.turn_left();}
          else                 {p.turn_right();}
        }
    }
}




}




