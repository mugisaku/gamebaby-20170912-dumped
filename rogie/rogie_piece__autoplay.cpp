#include"rogie_piece.hpp"
#include"rogie_field.hpp"




void
Piece::
autoplay()
{
    if(!own_task.callback && !test_flag(master_flag))
    {
        if(!own_task.callback){attack_hero();}
        if(!own_task.callback){chase_hero();}
        if(!own_task.callback){wait();}
    }
}


void
Piece::
chase_hero()
{
  auto  hero = current_field->master;

  current_field->prepare_to_search();
  hero->current_square->search(this);

  Direction  d;

  Square*  candidate = nullptr;

    for(int  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = current_square->link[i];

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
        if(d == direction)
        {
          own_task = Task{move_to_direction};
        }

      else
        {
          auto  l = get_left( direction);
          auto  r = get_right(direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){own_task = Task{turn_left };}
          else                 {own_task = Task{turn_right};}
        }
    }
}




void
Piece::
runaway_from_hero()
{
  auto  hero = current_field->master;

  current_field->prepare_to_search();
  hero->current_square->search(this);

  Direction  d;

  Square*  candidate = nullptr;

    for(int  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = current_square->link[i];

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
        if(d == direction)
        {
          own_task = Task{move_to_direction};
        }

      else
        {
          auto  l = get_left( direction);
          auto  r = get_right(direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){own_task = Task{turn_left };}
          else                 {own_task = Task{turn_right};}
        }
    }
}




void
Piece::
attack_hero()
{
  auto  hero = current_field->master;

  Direction  d;

  Square*  sq = nullptr;

    for(int  i = 0;  i < number_of_directions;  ++i)
    {
      auto  ln = current_square->link[i];

        if(ln && (ln->current_piece == hero))
        {
          sq = ln;

          d = static_cast<Direction>(i);

          break;
        }
    }


    if(sq)
    {
        if(d == direction)
        {
          own_task = Task{use_weapon};
        }

      else
        {
          auto  l = get_left( direction);
          auto  r = get_right(direction);

          auto  l_dist = get_distance(d,l);
          auto  r_dist = get_distance(d,r);

            if(l_dist < r_dist){own_task = Task{turn_left };}
          else                 {own_task = Task{turn_right};}
        }
    }
}




void
Piece::
wait()
{
  action_currency = 0;
}




