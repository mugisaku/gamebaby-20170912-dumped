#include"game_tagtable.hpp"
#include"gmbb.hpp"
#include"cbes_screen.hpp"




Tag*
TagTable::
get_tag() const
{
  return tag_table[(tag_x*5)+tag_y];
}


int
TagTable::
refresh_by_destinations()
{
  int  n = 0;

  tag_x = 0;
  tag_y = 0;

    for(auto&  ptr: tag_table)
    {
      ptr = nullptr;
    }


  Tag**  dst = tag_table;

    for(auto  src: get_current_place()->linked_place_list)
    {
        if(!src->get_flags().test(hiding_flag))
        {
          *dst++ = src;

          ++n;
        }
    }


  return n;
}


int
TagTable::
refresh_by_items()
{
  int  n = 0;

  tag_x = 0;
  tag_y = 0;

    for(auto&  ptr: tag_table)
    {
      ptr = nullptr;
    }


  Tag**  dst = tag_table;

    for(auto  src: get_current_place()->item_list)
    {
        if(!src->get_flags().test(hiding_flag))
        {
          *dst++ = src;

          ++n;
        }
    }


  return n;
}


int
TagTable::
refresh_by_belongings()
{
  int  n = 0;

  tag_x = 0;
  tag_y = 0;

    for(auto&  ptr: tag_table)
    {
      ptr = nullptr;
    }


  Tag**  dst = tag_table;

    for(auto  src: belongings_list)
    {
      *dst++ = src;

        if(src)
        {
          ++n;
        }
    }


  return n;
}




void
TagTable::
process(Controller&  ctrl)
{
    if(ctrl.test_pressed(keyflag::up) && tag_y)
    {
      tag_y -= 1;

      cbes::screen.need_to_refresh();
    }

  else
    if(ctrl.test_pressed(keyflag::down) && (tag_y < 4))
    {
      tag_y += 1;

      cbes::screen.need_to_refresh();
    }

  else
    if(ctrl.test_pressed(keyflag::left) && tag_x)
    {
      tag_x -= 1;

      cbes::screen.need_to_refresh();
    }

  else
    if(ctrl.test_pressed(keyflag::right) && (tag_x < 2))
    {
      tag_x += 1;

      cbes::screen.need_to_refresh();
    }

  else
    if(ctrl.test_pressed(keyflag::p))
    {
      change_direct(Direct::advance);
    }

  else
    if(ctrl.test_pressed(keyflag::n))
    {
      change_direct(Direct::back);
    }
}


void
TagTable::
render(cbes::CharacterTable&  dst)
{
  int  x = point.x;
  int  y = point.y;

    if(get_current_object() == this)
    {
      dst.printf_tall(x+(8*tag_x),y+(2*tag_y),"○");
    }


  int  row = 0;

    for(auto  tag: tag_table)
    {
        if(tag)
        {
          dst.print_tall(tag->name,x+1,y);
        }


      y += 2;

        if(++row >= 5)
        {
          row = 0;

          x += 8;
          y  = 0;
        }
    }
}





