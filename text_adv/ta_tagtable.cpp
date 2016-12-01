#include"ta_tagtable.hpp"
#include"ta.hpp"




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
    if(ctrl.test_pressed(up_flag) && tag_y)
    {
      tag_y -= 1;

      need_to_refresh();
    }

  else
    if(ctrl.test_pressed(down_flag) && (tag_y < 4))
    {
      tag_y += 1;

      need_to_refresh();
    }

  else
    if(ctrl.test_pressed(left_flag) && tag_x)
    {
      tag_x -= 1;

      need_to_refresh();
    }

  else
    if(ctrl.test_pressed(right_flag) && (tag_x < 2))
    {
      tag_x += 1;

      need_to_refresh();
    }

  else
    if(ctrl.test_pressed(p_flag))
    {
      change_direct(Direct::advance);
    }

  else
    if(ctrl.test_pressed(n_flag))
    {
      change_direct(Direct::back);
    }
}


void
TagTable::
render(Image&  dst)
{
  PrintPoint  x(point.x);
  PrintPoint  y(point.y);

    if(get_current_object() == this)
    {
      dst.print_tall("○",font_color,x+(8*tag_x),y+(2*tag_y));
    }


  int  row = 0;

    for(auto  tag: tag_table)
    {
        if(tag)
        {
          dst.print_tall(tag->name,gmbb::font_color,x+1,y);
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





