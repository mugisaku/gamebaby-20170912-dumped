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
    if(first_cursor.linked_piece)
    {
        if(ctrl.test_pressed(p_flag))
        {
CHDST:
          designated_piece = first_cursor.linked_piece;

          auto  pt = designated_piece->get_current_point();

          current_cursor = &second_cursor;

          designated_piece->pausing = true;

          second_cursor.show = true;

          first_cursor.x = pt.x;
          first_cursor.y = pt.y;
          second_cursor.x = first_cursor.x;
          second_cursor.y = first_cursor.y;

          state = MasterState::change_destination;
        }
    }

  else
    {
        if(ctrl.test_pressed(p_flag))
        {
            if(current_piece)
            {
              first_cursor.link(*current_piece);

                if(current_piece->pausing)
                {
                  current_piece->sync();

                  goto CHDST;
                }
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
                  default:;
                   }
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

            if(!p)
            {
              report;
              throw;
            }


          p->porter = **item;

          designated_piece = p;

          auto&  sq = *designated_square;

          p->set_current_point(24*sq.index.x+12,24*sq.index.y+12);

          auto  pt = p->get_current_point();

          current_cursor = &second_cursor;

          designated_piece->pausing = true;

          second_cursor.show = true;

          first_cursor.x = pt.x;
          first_cursor.y = pt.y;
          second_cursor.x = first_cursor.x;
          second_cursor.y = first_cursor.y;

          state = MasterState::change_destination;
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
process_change_destination(Controller&  ctrl)
{
    if(ctrl.test_pressed(p_flag))
    {
      current_cursor = &first_cursor;

      first_cursor.x = second_cursor.x;
      first_cursor.y = second_cursor.y;

      designated_piece->set_destination_point(second_cursor.x,second_cursor.y);

      designated_piece->pausing = false;

      second_cursor.show = false;

      state = MasterState::watch;

      first_cursor.unlink();

        if(pm.get_standby_piece())
        {
          designated_piece->porter->foods_amount = 3;
          designated_piece->porter->energy.fill();
          designated_piece->resistance           = 0;

          pm.commit();

          porter_list->erase(*entrybook[book_index]);
        }


      designated_piece = nullptr;
    }

  else
    if(ctrl.test_pressed(n_flag))
    {
      current_cursor = &first_cursor;

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
  haste_flag = (ctrl.test_pressing(p_flag) && ctrl.test_pressing(n_flag));

    if(current_cursor)
    {
      auto&  x = current_cursor->x;
      auto&  y = current_cursor->y;

      bool  moved = false;

        if(ctrl.test_pressing(   up_flag) && (y                             )){  --y;  moved = true;}
        if(ctrl.test_pressing( left_flag) && (x                             )){  --x;  moved = true;}
        if(ctrl.test_pressing(right_flag) && (x < board_image.get_width() -1)){  ++x;  moved = true;}
        if(ctrl.test_pressing( down_flag) && (y < board_image.get_height()-1)){  ++y;  moved = true;}


        if(moved)
        {
          current_cursor->unlink();
        }


      update_current_square();
      update_current_piece();
    }


    switch(state)
    {
  case(MasterState::watch):
      process_watch(ctrl);
      break;
  case(MasterState::choose_porter):
      process_choose_porter(ctrl);
      break;
  case(MasterState::change_destination):
      process_change_destination(ctrl);
      break;
    }
}


}}




