#include"trpt_master.hpp"
#include"trpt_board.hpp"
#include"trpt_porter.hpp"
#include"trpt_town.hpp"
#include"trpt_facility.hpp"




namespace gmbb{
namespace trpt{


Image  Master::sprite_image;


Master::
Master(Board*  brd):
board(nullptr),
width(0),
height(0),
state(MasterState::watch),
current_cursor(&first_cursor),
current_piece(nullptr),
current_square(nullptr)
{
   first_cursor.show =  true;
  second_cursor.show = false;

    if(brd)
    {
      change_board(*brd);
    }
}




void
Master::
change_width(int  v)
{
  width = std::min(v,24*board->get_width());

  offset_max.x = (24*board->get_width())-width;
}


void
Master::
change_height(int  v)
{
  height = std::min(v,24*board->get_height());

  offset_max.y = (24*board->get_height())-height;
}


void
Master::
change_board(Board&  brd)
{
  board = &brd;

  board_image.resize(24*brd.get_width(),24*brd.get_height());

  brd.render(board_image);
}




const Cursor&   Master::get_first_cursor() const{return first_cursor;}
const Cursor&  Master::get_second_cursor() const{return second_cursor;}
const Cursor*  Master::get_current_cursor() const{return current_cursor;}


void
Master::
update_current_square()
{
  int  sqx = (current_cursor->x-offset.x+12)/24;
  int  sqy = (current_cursor->y-offset.y+12)/24;

  current_square = &board->get(sqx,sqy);
}


Square*
Master::
get_current_square() const
{
  return current_square;
}


void
Master::
update_current_piece()
{
  current_piece = board->get_piece(current_cursor->x-offset.x,current_cursor->y-offset.y);
}


Piece*
Master::
get_current_piece() const
{
  return current_piece;
}




void
Master::
process_watch(Controller&  ctrl)
{
  first_cursor.x = cursor_point.x-offset.x;
  first_cursor.y = cursor_point.y-offset.y;

  update_current_square();
  update_current_piece();

    if(ctrl.test_pressed(p_flag))
    {
        if(current_piece)
        {
          called_piece = current_piece;

          auto  pt = called_piece->get_current_point();

          current_cursor = &second_cursor;

          called_piece->pausing = true;

          second_cursor.show = true;

          first_cursor.x = pt.x;
          first_cursor.y = pt.y;
          second_cursor.x = first_cursor.x;
          second_cursor.y = first_cursor.y;

          state = MasterState::decide_destination;
        }

      else
        {
        }
    }
}


void
Master::
process_decide_destination(Controller&  ctrl)
{
  second_cursor.x = cursor_point.x-offset.x;
  second_cursor.y = cursor_point.y-offset.y;

  update_current_square();
  update_current_piece();

    if(ctrl.test_pressed(p_flag))
    {
      current_cursor = &first_cursor;

      first_cursor.x = second_cursor.x;
      first_cursor.y = second_cursor.y;

      called_piece->set_destination_point(second_cursor.x,second_cursor.y);

      called_piece->pausing = false;

      second_cursor.show = false;

      state = MasterState::watch;
    }
}


void
Master::
process(Controller&  ctrl)
{
    if(ctrl.test_pressing(   up_flag) && cursor_point.y){--cursor_point.y;}
    if(ctrl.test_pressing( left_flag) && cursor_point.x){--cursor_point.x;}
    if(ctrl.test_pressing(right_flag) && (cursor_point.x <  width-1)){++cursor_point.x;}
    if(ctrl.test_pressing( down_flag) && (cursor_point.y < height-1)){++cursor_point.y;}

    switch(state)
    {
  case(MasterState::watch):
      process_watch(ctrl);
      break;
  case(MasterState::decide_destination):
      process_decide_destination(ctrl);
      break;
    }
}


void
Master::
move_window_point()
{
    if(current_cursor)
    {
      auto  cx = current_cursor->x;
      auto  cy = current_cursor->y;

      const int  x_center =  width/2;
      const int  y_center = height/2;

        if(cx < x_center)
        {
            if(window_point.x < x_center)
            {
              window_point.reset(x_center,window_point.y);
            }
        }

      else
        {
            if(window_point.x >= x_center)
            {
              window_point.reset(0,window_point.y);
            }
        }
    }
}


void
printxy(char16_t*  p, int  x, int  y)
{
  *p++ = 'X';

  *p++ = '0'+(x/100);

  x %= 100;

  *p++ = '0'+(x/10);

  x %= 10;

  *p++ = '0'+x;

  *p++ = 'Y';

  *p++ = '0'+(y/100);

  y %= 100;

  *p++ = '0'+(y/10);

  y %= 10;

  *p++ = '0'+y;
}


void
Master::
draw_windows(Image&  dst) const
{
  constexpr int  square_w = font::base_size*10;
  constexpr int  square_h = font::tall_size*3;

  auto  sq = current_square;

    if(sq)
    {
      auto  f = sq->facility;

      const char16_t*  s = (f? f->name:get_name(sq->kind));

      char16_t  posbuf[16] = {0};

      dst.frame(window_point.x,window_point.y,square_w,square_h);

      printxy(posbuf,sq->index.x,sq->index.y);

      dst.print_tall(posbuf,font_color,window_point.x+font::base_size,
                                       window_point.y+font::base_size);

      dst.print_tall(s,font_color,window_point.x+font::base_size,
                                  window_point.y+font::base_size+font::tall_size);

        if(f)
        {
          const int  x = window_point.x         ;
          const int  y = window_point.y+square_h;

          constexpr int  w = font::base_size*16;
          constexpr int  h = font::base_size*(2+4);

          dst.frame(x,y,w,h);

          f->draw_comment(dst,x+font::base_size,
                              y+font::base_size);
        }
    }
}


void
Master::
render(Image&  dst) const
{
  board_image.transfer(offset.x,offset.y,width,height,dst,0,0);

  static std::vector<Piece*>  plist;

  plist.clear();

  board->get_pieces_that_are_in(offset.x,offset.y,width,height,plist);

    for(auto  p: plist)
    {
      p->render(sprite_image,offset,dst);
    }


  draw_windows(dst);

  auto&  cur1 = get_first_cursor();
  auto&  cur2 = get_second_cursor();

  sprite_image.transfer(24*3,0,24,32,dst,cur1.x-offset.x,cur1.y-offset.y);

    if(cur2.show)
    {
      sprite_image.transfer(24*4,0,24,32,dst,cur2.x-offset.x,cur2.y-offset.y);
    }


  auto  x = cursor_point.x+16;
  auto  y = cursor_point.y- 8;

  sprite_image.transfer(24*5,0,24,32,dst,x,y);
}




void
Master::
set_stage()
{
  auto  fc = &facility_table[0];

  fc->name = u"A TOWN";
  fc->kind = FacilityKind::town;
  fc->town = &town_table[0];

  fc = &facility_table[1];

  fc->name = u"B TOWN";
  fc->kind = FacilityKind::town;
  fc->town = &town_table[1];

  fc = &facility_table[2];

  fc->name = u"C TOWN";
  fc->kind = FacilityKind::town;
  fc->town = &town_table[2];

  fc = &facility_table[3];

  fc->name = u"VILLAGE";
  fc->kind = FacilityKind::village;

  board->get( 2, 2).facility = &facility_table[0];
  board->get( 9, 2).facility = &facility_table[1];
  board->get( 2, 6).facility = &facility_table[2];
  board->get( 8, 9).facility = &facility_table[3];

  facility_table[0].town->porter_list.emplace_back(new Porter(u"わにまる"));
}


}}




