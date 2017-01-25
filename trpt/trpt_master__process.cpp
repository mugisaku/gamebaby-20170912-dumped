#include"trpt_master.hpp"
#include"trpt_board.hpp"
#include"trpt_porter.hpp"
#include"trpt_town.hpp"
#include"trpt_facility.hpp"




namespace gmbb{
namespace trpt{


void
Master::
process_watch(Controller&  ctrl)
{
  first_cursor.x = cursor_point.x-rectangle.x;
  first_cursor.y = cursor_point.y-rectangle.y;

  update_current_square();
  update_current_piece();

    if(ctrl.test_pressed(p_flag))
    {
        if(current_piece)
        {
          designated_piece = current_piece;

          auto  pt = designated_piece->get_current_point();

          current_cursor = &second_cursor;

          designated_piece->pausing = true;

          second_cursor.show = true;

          first_cursor.x = pt.x;
          first_cursor.y = pt.y;
          second_cursor.x = first_cursor.x;
          second_cursor.y = first_cursor.y;

          state = MasterState::decide_destination;
        }

      else
        {
          designated_square = current_square;

          auto  f = current_square->facility;

            if(f)
            {
                switch(f->kind)
                {
              case(FacilityKind::village):
                  break;
              case(FacilityKind::town):
                    if(f->town->porter_list.size())
                    {
                      designated_facility = f;

                      update_entrybook(*f->town);

                      book_index.reset();

                      state = MasterState::choose_porter;
                    }
                  break;
                }
            }
        }
    }
}


void
Master::
process_choose_porter(Controller&  ctrl)
{
    if(ctrl.test_pressed(p_flag))
    {
      auto&  item = entrybook[book_index];

        if(item)
        {
          auto  p = pm.ready();

          p->porter = **item;

          designated_piece = p;

          auto&  sq = *designated_square;

          p->set_current_point(24*sq.index.x,24*sq.index.y);

          auto  pt = p->get_current_point();

          current_cursor = &second_cursor;

          designated_piece->pausing = true;

          second_cursor.show = true;

          first_cursor.x = pt.x;
          first_cursor.y = pt.y;
          second_cursor.x = first_cursor.x;
          second_cursor.y = first_cursor.y;

          state = MasterState::decide_destination;
        }
    }

  else
    if(ctrl.test_pressed(n_flag))
    {
      state = MasterState::watch;
    }

  else
    if(ctrl.test_pressed(left_flag))
    {
        if(book_index.x)
        {
          --book_index.x;
        }
    }

  else
    if(ctrl.test_pressed(right_flag))
    {
        if(book_index.x < (entrybook.get_page_number()-1))
        {
          ++book_index.x;
        }
    }

  else
    if(ctrl.test_pressed(up_flag))
    {
        if(book_index.y)
        {
          --book_index.y;
        }
    }

  else
    if(ctrl.test_pressed(down_flag))
    {
        if(book_index.y < (entrybook.get_line_number()-1))
        {
          ++book_index.y;
        }
    }
}


void
Master::
process_change_destination(Controller&  ctrl, bool  first)
{
  second_cursor.x = cursor_point.x-rectangle.x;
  second_cursor.y = cursor_point.y-rectangle.y;

  update_current_square();
  update_current_piece();

    if(ctrl.test_pressed(p_flag))
    {
      current_cursor = &first_cursor;

      first_cursor.x = second_cursor.x;
      first_cursor.y = second_cursor.y;

      designated_piece->set_destination_point(second_cursor.x,second_cursor.y);

      designated_piece->pausing = false;

      designated_piece = nullptr;

      second_cursor.show = false;

      state = MasterState::watch;

        if(pm.get_standby_piece())
        {
          pm.commit();

          porter_list->erase(*entrybook[book_index]);
        }
    }

  else
    if(ctrl.test_pressed(n_flag) && first)
    {
      second_cursor.show = false;

      designated_piece->pausing = false;

      designated_piece = nullptr;

      state = MasterState::watch;

      pm.pullback();
    }
}


void
Master::
process(Controller&  ctrl)
{
    if(ctrl.test_pressing(   up_flag) && cursor_point.y){--cursor_point.y;}
    if(ctrl.test_pressing( left_flag) && cursor_point.x){--cursor_point.x;}
    if(ctrl.test_pressing(right_flag) && (cursor_point.x < rectangle.w-1)){++cursor_point.x;}
    if(ctrl.test_pressing( down_flag) && (cursor_point.y < rectangle.h-1)){++cursor_point.y;}

    switch(state)
    {
  case(MasterState::watch):
      process_watch(ctrl);
      break;
  case(MasterState::choose_porter):
      process_choose_porter(ctrl);
      break;
  case(MasterState::decide_destination):
      process_change_destination(ctrl,true);
      break;
  case(MasterState::change_destination):
      process_change_destination(ctrl,false);
      break;
    }
}


}}




