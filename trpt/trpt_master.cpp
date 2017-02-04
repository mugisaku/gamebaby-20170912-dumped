#include"trpt_master.hpp"
#include"trpt_board.hpp"
#include"trpt_porter.hpp"
#include"trpt_town.hpp"
#include"trpt_facility.hpp"




namespace gmbb{
namespace trpt{


Master::
Master():
pm(board),
state(MasterState::watch),
current_cursor(&first_cursor),
current_piece(nullptr),
current_square(nullptr)
{
   first_cursor.show =  true;
  second_cursor.show = false;
}


Master::
~Master()
{
}




void
Master::
change_size(int  w, int  h)
{
  view.w = std::min(w,24*board.get_width());
  view.h = std::min(h,24*board.get_height());

  current_cursor->reset(view.x+(view.w/2),view.y+(view.h/2));
}


void
Master::
load(const File*  f)
{
  board.load(f);

  board_image.resize(24*board.get_width(),24*board.get_height());

  board.render(board_image);
}




const Cursor&   Master::get_first_cursor() const{return first_cursor;}
const Cursor&  Master::get_second_cursor() const{return second_cursor;}
const Cursor*  Master::get_current_cursor() const{return current_cursor;}


void
Master::
update_current_square()
{
  int  sqx = (current_cursor->x/24);
  int  sqy = (current_cursor->y/24);

  current_square = &board.get(sqx,sqy);
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
  current_piece = pm.get_piece(current_cursor->x,current_cursor->y);
}


Piece*
Master::
get_current_piece() const
{
  return current_piece;
}




void
Master::
update_entrybook(Town&  t)
{
  entrybook.clear();

  porter_list = &t.porter_list;

  auto   it = t.porter_list.begin();
  auto  end = t.porter_list.end();

    for(int  x = 0;  x < entrybook.get_page_number();  ++x){
    for(int  y = 0;  y < entrybook.get_line_number();  ++y){
        if(it == end)
        {
          return;
        }


      auto&  item = entrybook.pages[x].items[y];

      item.valid = true;
      item.data  = it++;
    }}
}




void
Master::
move_window_point()
{
    if(current_cursor)
    {
      auto  cx = current_cursor->x;
      auto  cy = current_cursor->y;

      const int  x_center = view.w/2;
      const int  y_center = view.h/2;

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
Master::
step()
{
  int  n = haste_flag? 4:1;

    while(n--)
    {
      auto  p = pm.step();

        if(p)
        {
          auto&  f = *p->current_square->facility;

          f.town->porter_list.emplace_back(p->porter);

          pm.pullback_previous_piece();

            if(current_cursor->linked_piece == p)
            {
              current_cursor->unlink();
            }
        }
    }
}


void
Master::
render(Image&  dst) const
{
  board_image.transfer(view.x,
                       view.y,
                       view.w,
                       view.h,dst,0,0);

  pm.render(view,dst);


    switch(state)
    {
  case(MasterState::choose_porter):
      draw_entrybook(dst);
      break;
  default:
      auto&  cur1 = get_first_cursor();
      auto&  cur2 = get_second_cursor();

      PieceManager::sprite_image.transfer(24*3,0,16,16,dst,cur1.x-view.x-8,cur1.y-view.y-8);

        if(cur2.show)
        {
          PieceManager::sprite_image.transfer(24*4,0,16,16,dst,cur2.x-view.x-8,cur2.y-view.y-8);
        }


      auto  x = (current_cursor->x-view.x)+ 8;
      auto  y = (current_cursor->y-view.y)-16;

      PieceManager::sprite_image.transfer(24*5,40-15,21,15,dst,x,y);

      draw_windows(dst);
    }
//printf("curcur %4d %4d\n",current_cursor->x,current_cursor->y);
//printf("view   %4d %4d\n",           view.x,           view.y);
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

  board.get( 2, 2).facility = &facility_table[0];
  board.get( 7, 2).facility = &facility_table[1];
  board.get( 2, 6).facility = &facility_table[2];

  auto   fa = &facility_table[0];
  auto&  ls = fa->town->porter_list;

  auto  a = new Porter(u"わにまる",fa);
  auto  b = new Porter(u"あるまじろう",fa);

  a->moving_capacity = 200;
  b->moving_capacity = 120;
  a->energy.change_consumption(800);
  b->energy.change_consumption(220);

  ls.emplace_back(a);
  ls.emplace_back(b);
}


}}




