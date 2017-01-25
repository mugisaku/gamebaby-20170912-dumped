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
change_width(int  v)
{
  rectangle.w = std::min(v,24*board.get_width());

  offset_max.x = (24*board.get_width())-rectangle.w;
}


void
Master::
change_height(int  v)
{
  rectangle.h = std::min(v,24*board.get_height());

  offset_max.y = (24*board.get_height())-rectangle.h;
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
  int  sqx = (current_cursor->x-rectangle.x+12)/24;
  int  sqy = (current_cursor->y-rectangle.y+12)/24;

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
  current_piece = pm.get_piece(current_cursor->x-rectangle.x,current_cursor->y-rectangle.y);
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

      const int  x_center = rectangle.w/2;
      const int  y_center = rectangle.h/2;

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
  auto  p = pm.step();

    if(p)
    {
      auto&  f = *p->current_square->facility;

      f.town->porter_list.emplace_back(p->porter);

      pm.pullback_previous_piece();
    }
}


void
Master::
render(Image&  dst) const
{
  board_image.transfer(rectangle.x,
                       rectangle.y,
                       rectangle.w,
                       rectangle.h,dst,0,0);

  pm.render(rectangle,dst);


    switch(state)
    {
  case(MasterState::choose_porter):
      draw_entrybook(dst);
      break;
  default:
      auto&  cur1 = get_first_cursor();
      auto&  cur2 = get_second_cursor();

      PieceManager::sprite_image.transfer(24*3,0,24,32,dst,cur1.x-rectangle.x,cur1.y-rectangle.y);

        if(cur2.show)
        {
          PieceManager::sprite_image.transfer(24*4,0,24,32,dst,cur2.x-rectangle.x,cur2.y-rectangle.y);
        }


      auto  x = cursor_point.x+16;
      auto  y = cursor_point.y- 8;

      PieceManager::sprite_image.transfer(24*5,0,24,32,dst,x,y);

      draw_windows(dst);
    }
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

  board.get( 2, 2).facility = &facility_table[0];
  board.get( 9, 2).facility = &facility_table[1];
  board.get( 2, 6).facility = &facility_table[2];
  board.get( 8, 9).facility = &facility_table[3];

  auto   fa = &facility_table[0];
  auto&  ls = fa->town->porter_list;

  ls.emplace_back(new Porter(u"わにまる",fa));
  ls.emplace_back(new Porter(u"あるまじろう",fa));
  ls.emplace_back(new Porter(u"いぬりん",fa));
  ls.emplace_back(new Porter(u"こねこ",fa));
  ls.emplace_back(new Porter(u"たぬぽん",fa));
  ls.emplace_back(new Porter(u"もうすけ",fa));
  ls.emplace_back(new Porter(u"うまお",fa));
  ls.emplace_back(new Porter(u"こけこ",fa));
}


}}




