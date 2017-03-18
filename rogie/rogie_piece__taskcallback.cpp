#include"rogie_piece.hpp"
#include"rogie_field.hpp"




namespace{
Piece&
get(Task&  tsk)
{
  return *static_cast<Piece*>(tsk.get_manager()->get_owner());
}
}


void
Piece::
chase_hero(Task&  tsk)
{
  auto&  piece = get(tsk);

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
          piece.get_task_manager().push(move_to_direction);
        }

      else
        {
          auto  l = get_left( piece.direction);
          auto  r = get_right(piece.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){piece.get_task_manager().push(turn_left);}
          else                 {piece.get_task_manager().push(turn_right);}
        }


      piece.get_task_manager().need_to_break_scanning();
    }
}




void
Piece::
runaway_from_hero(Task&  tsk)
{
  auto&  piece = get(tsk);

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
          piece.get_task_manager().push(move_to_direction);
        }

      else
        {
          auto  l = get_left( piece.direction);
          auto  r = get_right(piece.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){piece.get_task_manager().push(turn_left);}
          else                 {piece.get_task_manager().push(turn_right);}
        }


      piece.get_task_manager().need_to_break_scanning();
    }
}




void
Piece::
attack_hero(Task&  tsk)
{
  auto&  piece = get(tsk);

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
          piece.get_task_manager().push(use_weapon);
        }

      else
        {
          auto  l = get_left( piece.direction);
          auto  r = get_right(piece.direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){piece.get_task_manager().push(turn_left );}
          else                 {piece.get_task_manager().push(turn_right);}
        }


      piece.get_task_manager().need_to_break_scanning();
    }
}




void
Piece::
wait(Task&  tsk)
{
  auto&  piece = get(tsk);

  piece.action_currency = 0;
}




