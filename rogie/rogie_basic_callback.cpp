#include"rogie_basic_callback.hpp"
#include"rogie_field.hpp"




namespace basic_callback{




void
move_to_direction(Context&  ctx)
{
  auto&          phase = ctx.memory[0];
  auto&        counter = ctx.memory[1];
  auto&  sleep_counter = ctx.memory[2];

  auto&  piece = *static_cast<Piece*>(ctx.caller);

  auto&  x = piece.rendering_dst_offset.x;
  auto&  y = piece.rendering_dst_offset.y;

  auto&  src_x = piece.rendering_src_offset.x;

       if(counter > 20){src_x = 24;}
  else if(counter > 16){src_x =  0;}
  else if(counter > 12){src_x = 48;}
  else if(counter >  8){src_x =  0;}
  else if(counter >  4){src_x = 24;}
  else if(counter >  0){src_x =  0;}

    switch(phase)
    {
  case(0): {
      auto  ln = (*piece.current_square)[piece.direction];

        if(!ln || ln->current_piece)
        {
          ctx.callback = nullptr;

          return;
        }


      ln->current_piece = &piece;

      piece.current_square->current_piece = nullptr;

      piece.current_square = ln;


      piece.rendering_dst_offset.x = 0;
      piece.rendering_dst_offset.y = 0;

      piece.set_shape_by_direction();
      piece.add_offset_by_direction(-24);

      piece.rendering_src_offset.x = 0;
      piece.rendering_src_offset.y = 0;

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
turn_left(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

  piece.change_direction(get_left(piece.direction));

  ctx.callback = nullptr;
}


void
turn_right(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

  piece.change_direction(get_right(piece.direction));

  ctx.callback = nullptr;
}




void
punch(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

  auto&          phase = ctx.memory[0];
  auto&        counter = ctx.memory[1];
  auto&  sleep_counter = ctx.memory[2];

  auto&  x = piece.rendering_dst_offset.x;
  auto&  y = piece.rendering_dst_offset.y;

    switch(phase)
    {
  case(0):
      piece.rendering_dst_offset.x = 0;
      piece.rendering_dst_offset.y = 0;

      piece.rendering_src_offset.x = 24*3;

      piece.set_shape_by_direction();

      counter = 12;

      ++phase;
      break;
  case(1):
        if(counter--)
        {
          piece.add_offset_by_direction(1);
        }

      else
        {
          auto  sq = (*piece.current_square)[piece.direction];

            if(sq && sq->current_piece)
            {
              sq->current_piece->push_work(damage);
            }


          counter = 12;

          ++phase;
        }
      break;
  case(2):
        if(counter--)
        {
          piece.rendering_src_offset.x = 0;

          piece.add_offset_by_direction(-1);
        }

      else
        {
          piece.rendering_src_offset.x = 0;

          ctx.callback = nullptr;
        }
      break;
    }
}




void
damage(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

  auto&          phase = ctx.memory[0];
  auto&        counter = ctx.memory[1];
  auto&  sleep_counter = ctx.memory[2];

  auto&  x = piece.rendering_dst_offset.x;
  auto&  y = piece.rendering_dst_offset.y;

    switch(phase)
    {
  case(0):
      piece.rendering_dst_offset.x = 0;
      piece.rendering_dst_offset.y = 0;

      piece.rendering_src_offset.x = 24*4;

      piece.set_shape_by_direction();

      counter = 12;

      ++phase;
      break;
  case(1):
        if(counter--)
        {
        }

      else
        {
          piece.rendering_src_offset.x = 0;

          ctx.callback = nullptr;
        }
      break;
    }
}




void
chase_hero(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

  auto  hero = piece.current_square->field->master;

  piece.current_square->field->prepare_to_search();
  hero->current_square->search(&piece);

  Direction  d;

  Square*  candidate = nullptr;

    for(int  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = piece.current_square->link[i];

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
        if(d == piece.direction)
        {
          piece.move_advance();
        }

      else
        {
          auto  l = get_left( piece.direction);
          auto  r = get_right(piece.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){piece.turn_left();}
          else                 {piece.turn_right();}
        }
    }
}




void
runaway_from_hero(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

  auto  hero = piece.current_square->field->master;

  piece.current_square->field->prepare_to_search();
  hero->current_square->search(&piece);

  Direction  d;

  Square*  candidate = nullptr;

    for(int  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = piece.current_square->link[i];

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
        if(d == piece.direction)
        {
          piece.move_advance();
        }

      else
        {
          auto  l = get_left( piece.direction);
          auto  r = get_right(piece.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){piece.turn_left();}
          else                 {piece.turn_right();}
        }
    }
}




void
attack_hero(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

  auto  hero = piece.current_square->field->master;

  Direction  d;

  Square*  sq = nullptr;

    for(int  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = piece.current_square->link[i];

        if(ln && (ln->current_piece == hero))
        {
          sq = ln;

          d = static_cast<Direction>(i);

          break;
        }
    }


    if(sq)
    {
        if(d == piece.direction)
        {
          piece.use_weapon();
        }

      else
        {
          auto  l = get_left( piece.direction);
          auto  r = get_right(piece.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){piece.turn_left();}
          else                 {piece.turn_right();}
        }


      piece.unset_flag(Piece::taskseeking_flag);
    }
}




}




