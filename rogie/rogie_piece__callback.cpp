#include"rogie_piece.hpp"
#include"rogie_field.hpp"




void
Piece::
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

        if(!ln || ln->current_piece || piece.test_flag(readied_flag))
        {
          ctx.callback = nullptr;

          return;
        }


        if(!piece.consume_currency(piece.moving_cost_base))
        {
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
            if(piece.test_flag(master_flag))
            {
              auto&  itm = piece.current_square->placed_item;

                if(itm)
                {
                    if(piece.append_item(std::move(itm)))
                    {
                      auto&  pt = piece.current_square->point;

                      piece.current_square->field->update_image(pt.x,pt.y);
                    }
                }
            }


          ctx.callback = nullptr;
        }
      break;
    }
}




void
Piece::
turn_left(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

    if(piece.consume_currency(piece.moving_cost_base/3))
    {
      piece.change_direction(get_left(piece.direction));

      ctx.callback = nullptr;
    }
}


void
Piece::
turn_right(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

    if(piece.consume_currency(piece.moving_cost_base/3))
    {
      piece.change_direction(get_right(piece.direction));

      ctx.callback = nullptr;
    }
}




void
Piece::
change_weapon(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

    if(piece.test_flag(use_gun_flag) && !piece.test_flag(readied_flag))
    {
      piece.unset_flag(use_gun_flag);
    }

  else
    if(piece.test_flag(have_gun_flag))
    {
      piece.set_flag(use_gun_flag);
    }


  ctx.callback = nullptr;
}


void
Piece::
use_weapon(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

    if(piece.test_flag(use_gun_flag))
    {
        if(piece.test_flag(readied_flag))
        {
          piece.push_action(fire);
        }

      else
        {
          piece.push_action(ready_to_fire);
        }
    }

  else
    {
      piece.push_action(punch);
    }


  ctx.callback = nullptr;
}


void
Piece::
ready_to_fire(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

    if(piece.consume_currency(piece.moving_cost_base))
    {
      piece.set_flag(readied_flag);

      piece.rendering_src_base.x   = 24*3;
      piece.rendering_src_offset.x =    0;


      ctx.callback = nullptr;
    }
}


void
Piece::
cancel_ready(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

    if(piece.consume_currency(piece.moving_cost_base))
    {
      piece.unset_flag(readied_flag);

      piece.rendering_src_base.x   = 0;
      piece.rendering_src_offset.x = 0;


      ctx.callback = nullptr;
    }
}


void
Piece::
fire(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

    if(piece.consume_currency(piece.moving_cost_base))
    {
      auto  sq = (*piece.current_square)[piece.direction];

      Piece*  target = nullptr;

        while(sq)
        {
          target = sq->current_piece;

            if(target)
            {
              break;
            }


          sq = (*sq)[piece.direction];
        }


        if(target)
        {
          target->push_work(damage);
        }

      ctx.callback = nullptr;
    }
}


void
Piece::
punch(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

  auto&    phase = ctx.memory[0];
  auto&  counter = ctx.memory[1];
  auto&     last = ctx.memory[2];

  auto&  x = piece.rendering_src_base.x;

    switch(phase)
    {
  case(0):
        if(!piece.consume_currency(piece.moving_cost_base/3))
        {
          return;
        }


      last = x       ;
             x = 24*3;

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
          piece.add_offset_by_direction(-1);
        }

      else
        {
          x = last;

          ctx.callback = nullptr;
        }
      break;
    }
}




void
Piece::
damage(Context&  ctx)
{
  auto&  piece = *static_cast<Piece*>(ctx.caller);

  auto&    phase = ctx.memory[0];
  auto&  counter = ctx.memory[1];
  auto&     last = ctx.memory[2];

  auto&  x = piece.rendering_src_base.x;

    switch(phase)
    {
  case(0):
      last = x       ;
             x = 24*4;

      counter = 12;

      ++phase;
      break;
  case(1):
        if(counter--)
        {
        }

      else
        {
          x = last;

          ctx.callback = nullptr;
        }
      break;
    }
}




void
Piece::
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
          piece.push_action(move_to_direction);
        }

      else
        {
          auto  l = get_left( piece.direction);
          auto  r = get_right(piece.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){piece.push_action(turn_left);}
          else                 {piece.push_action(turn_right);}
        }


      piece.need_to_break_scanning();
    }
}




void
Piece::
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
          piece.push_action(move_to_direction);
        }

      else
        {
          auto  l = get_left( piece.direction);
          auto  r = get_right(piece.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){piece.push_action(turn_left);}
          else                 {piece.push_action(turn_right);}
        }


      piece.need_to_break_scanning();
    }
}




void
Piece::
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
          piece.push_action(use_weapon);
        }

      else
        {
          auto  l = get_left( piece.direction);
          auto  r = get_right(piece.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){piece.push_action(turn_left );}
          else                 {piece.push_action(turn_right);}
        }


      piece.need_to_break_scanning();
    }
}




