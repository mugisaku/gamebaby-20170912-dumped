#include"trpt_board.hpp"
#include"trpt_porter.hpp"




namespace gmbb{
namespace trpt{


Image  Board::bg_image;



Board::
Board(int  w, int  h):
width(w),
height(h),
current_cursor(&first_cursor),
current_piece(nullptr),
current_square(nullptr)
{
   first_cursor.show =  true;
  second_cursor.show = false;

  square_table.resize(w*h);
}


void
Board::
reset()
{
    for(int  y = 0;  y < height;  ++y){
    for(int  x = 0;  x <  width;  ++x){
      auto&  sq = get(x,y);

      sq.kind = SquareKind::plain;

      sq.facility = nullptr;
    }}
}




Square&
Board::
get(int  x, int  y)
{
  return square_table[(width*y)+x];
}


const Square&
Board::
get_const(int  x, int  y) const
{
  return square_table[(width*y)+x];
}


const Cursor&   Board::get_first_cursor() const{return first_cursor;}
const Cursor&  Board::get_second_cursor() const{return second_cursor;}
const Cursor*  Board::get_current_cursor() const{return current_cursor;}


void
Board::
step()
{
}




namespace{
bool
test_qbf(FileReader&  r)
{
  constexpr uint8_t
  signature[4] =
  {
    'Q','B','F',0
  };


    for(int  i = 0;  i < 4;  i += 1)
    {
      auto  c = r.get();

        if(c != signature[i])
        {
          return false;
        }
    }


  return true;
}
}


void
Board::
load(const File*  f)
{
    if(f)
    {
      auto  r = f->reader();

        if(test_qbf(r))
        {
          int  w = r.get();
          int  h = r.get();
          int  d = r.get();

          width  = w;
          height = h;

          square_table.resize(w*h);

            for(int  y = 0;  y < h;  y += 1){
            for(int  x = 0;  x < w;  x += 1){
              auto&  sq = get(x,y);

              sq.index.x = x;
              sq.index.y = y;

              sq.kind = static_cast<SquareKind>(r.get()&0x7F);

              sq.image_point.x = 24*r.get();
              sq.image_point.y = 24*r.get();
              r.get();
              r.get();

              sq.facility = nullptr;
            }}
        }


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

      get( 2, 2).facility = &facility_table[0];
      get( 9, 2).facility = &facility_table[1];
      get( 2, 6).facility = &facility_table[2];
      get( 8, 9).facility = &facility_table[3];

      facility_table[0].town->porter_list.emplace_back(new Porter(u"わにまる"));
    }
}




int  Board::get_width() const{return width;}
int  Board::get_height() const{return height;}


Square*
Board::
get_current_square() const
{
  return current_square;
}


Piece*
Board::
get_piece(int  x, int  y)
{
  const int  x_end = (x+12);
  const int  y_end = (y+12);

  x -= 12;
  y -= 12;

    for(auto&  p: piece_list)
    {
      auto  pt = p.get_current_point();

        if((pt.x >= x    ) &&
           (pt.y >= y    ) &&
           (pt.x <  x_end) &&
           (pt.y <  y_end))
        {
          return &p;
        }
    }


  return nullptr;
}


void
Board::
get_pieces_that_are_in(int  x, int  y, int  w, int  h, std::vector<Piece*>  buf)
{
  const int  x_end = (x+w);
  const int  y_end = (y+h);

    for(auto&  p: piece_list)
    {
      auto  pt = p.get_current_point();

        if((pt.x >= x    ) &&
           (pt.y >= y    ) &&
           (pt.x <  x_end) &&
           (pt.y <  y_end))
        {
          buf.emplace_back(&p);
        }
    }
}


void
Board::
process(Controller&  ctrl, int  x, int  y)
{
    if(current_cursor == &first_cursor)
    {
      first_cursor.x = x;
      first_cursor.y = y;

        if(ctrl.test_pressed(p_flag))
        {
          auto  p = get_piece(x,y);

            if(p)
            {
              auto  pt = p->get_current_point();

              current_cursor = &second_cursor;

              p->pausing = true;

              second_cursor.show = true;

              first_cursor.x = pt.x;
              first_cursor.y = pt.y;
              second_cursor.x = first_cursor.x;
              second_cursor.y = first_cursor.y;
            }
        }
    }

  else
    {
      second_cursor.x = x;
      second_cursor.y = y;

        if(ctrl.test_pressed(p_flag))
        {
          auto  p = get_piece(x,y);

            if(p)
            {
              auto  pt = p->get_current_point();

              current_cursor = &first_cursor;

              first_cursor.x = second_cursor.x;
              first_cursor.y = second_cursor.y;

              p->set_destination_point(second_cursor.x,second_cursor.y);

              p->pausing = false;

              second_cursor.show = false;
            }
        }
    }


  int  sqx = (current_cursor->x+12)/24;
  int  sqy = (current_cursor->y+12)/24;

  current_square = &get(sqx,sqy);
}


void
Board::
render(Image&  dst) const
{
    for(int  y = 0;  y < height;  y += 1){
    for(int  x = 0;  x <  width;  x += 1){
      auto&  sq = get_const(x,y);

      bg_image.transfer(sq.image_point.x,
                        sq.image_point.y,24,24,dst,(24*x),(24*y));
    }}
}




}}




