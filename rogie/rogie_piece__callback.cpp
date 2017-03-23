#include"rogie_piece.hpp"
#include"rogie_field.hpp"




namespace{
Piece&
get(void*  ptr)
{
  return *static_cast<Piece*>(ptr);
}
}


void
Piece::
move_to_direction(Task&  tsk, void*  caller)
{
  auto&          phase = tsk.memory[0];
  auto&        counter = tsk.memory[1];
  auto&  sleep_counter = tsk.memory[2];

  auto&  piece = get(caller);

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
          tsk.callback = nullptr;

          return;
        }


      piece.action_currency -= piece.moving_cost;



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
                    if(piece.append_item(itm))
                    {
                      itm = nullptr;

                      auto&  pt = piece.current_square->point;

                      piece.current_square->field->update_image(pt.x,pt.y);
                    }
                }
            }


          tsk.callback = nullptr;
        }
      break;
    }
}




void
Piece::
turn_left(Task&  tsk, void*  caller)
{
  auto&  piece = get(caller);

  piece.action_currency -= piece.moving_cost/3;

  piece.change_direction(get_left(piece.direction));

  tsk.callback = nullptr;
}


void
Piece::
turn_right(Task&  tsk, void*  caller)
{
  auto&  piece = get(caller);

  piece.action_currency -= piece.moving_cost/3;

  piece.change_direction(get_right(piece.direction));

  tsk.callback = nullptr;
}




void
Piece::
change_weapon(Task&  tsk, void*  caller)
{
  auto&  piece = get(caller);

  auto&  fa = piece.current_firearm;

    if(fa)
    {
      fa = fa->next;
    }

  else
    {
      fa = piece.first_firearm;
    }


  piece.weapon_spec = &get_weapon_spec(fa? fa->weapon_kind:WeaponKind::punch);

  tsk.callback = nullptr;
}


void
Piece::
use_weapon(Task&  tsk, void*  caller)
{
  auto&  piece = get(caller);

    if(piece.current_firearm)
    {
      piece.own_task = Task(fire);
    }

  else
    {
      piece.own_task = Task(punch);
    }
}


void
Piece::
fire(Task&  tsk, void*  caller)
{
  auto&  piece = get(caller);

    if(piece.current_firearm->bullet)
    {
      piece.action_currency -= piece.weapon_spec->fire_cost;

      --piece.current_firearm->bullet;

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
          attack(piece,*target);
        }
    }

  else
    {
        if(!piece.current_firearm->ammo)
        {
          piece.current_firearm->find_ammo(piece.first_ammo);
        }


      piece.action_currency -= piece.current_firearm->fulfill();
    }


  tsk.callback = nullptr;
}


void
Piece::
punch(Task&  tsk, void*  caller)
{
  auto&  piece = get(caller);

  auto&    phase = tsk.memory[0];
  auto&  counter = tsk.memory[1];
  auto&     last = tsk.memory[2];

  auto&  x = piece.rendering_src_base.x;

    switch(phase)
    {
  case(0):
      piece.action_currency -= (piece.moving_cost/(piece.test_flag(master_flag)? 3:1));


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
              sq->current_piece->push_task(damage);

              attack(piece,*sq->current_piece);
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

          tsk.callback = nullptr;
        }
      break;
    }
}




void
Piece::
damage(Task&  tsk, void*  caller)
{
  auto&  piece = get(caller);

  auto&    phase = tsk.memory[0];
  auto&  counter = tsk.memory[1];
  auto&     last = tsk.memory[2];

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

          tsk.callback = nullptr;
        }
      break;
    }
}



void
Piece::
disappear(Task&  tsk, void*  caller)
{
  auto&  piece = get(caller);

  auto&         phase = tsk.memory[0];
  auto&       counter = tsk.memory[1];
  auto&  last_counter = tsk.memory[2];

  auto&  c = piece.current_field->rendering_count;

  auto&  x = piece.rendering_src_base.x;

    switch(phase)
    {
  case(0):
      last_counter = c;
      counter = 16;

      ++phase;
      break;
  case(1):
        if(c > last_counter)
        {
          last_counter = c;

            if(counter--)
            {
                if(piece.test_flag(invisible_flag)){piece.unset_flag(invisible_flag);}
              else                                 {piece.set_flag(  invisible_flag);}
            }

          else
            {
              piece.set_flag(died_flag);

              tsk.callback = nullptr;
            }
        }
      break;
    }
}




