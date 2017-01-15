#include"trpt_board.hpp"




namespace gmbb{
namespace trpt{


Image  Board::sprite_image;
Image      Board::bg_image;



Board::
Board(int  w, int  h):
width(w),
height(h),
current_cursor(&first_cursor)
{
  player.board = this;

  player.set_current_point(0,0);

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

      sq.feature = nullptr;
    }}


  player.board = this;
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

              sq.kind = static_cast<SquareKind>(r.get()&0x7F);

              sq.image_point.x = 24*r.get();
              sq.image_point.y = 24*r.get();
              r.get();
              r.get();

              sq.feature = nullptr;
            }}
        }
    }
}




void
Board::
process(Controller&  ctrl)
{
    if(ctrl.test_pressing(   up_flag)){--current_cursor->y;}
    if(ctrl.test_pressing( left_flag)){--current_cursor->x;}
    if(ctrl.test_pressing(right_flag)){++current_cursor->x;}
    if(ctrl.test_pressing( down_flag)){++current_cursor->y;}


    if(ctrl.test_pressed(p_flag))
    {
      auto&  curcur = *current_cursor;

      auto  pt = player.get_current_point();

        if(current_cursor == &first_cursor)
        {
            if((pt.x >= (curcur.x-12)) &&
               (pt.x <  (curcur.x+12)) &&
               (pt.y >= (curcur.y-12)) &&
               (pt.y <  (curcur.y+12)))
            {
              current_cursor = &second_cursor;

              player.pausing = true;

              second_cursor.show = true;

              first_cursor.x = pt.x;
              first_cursor.y = pt.y;
              second_cursor.x = first_cursor.x;
              second_cursor.y = first_cursor.y;
            }
        }

      else
        {
          current_cursor = &first_cursor;

          first_cursor.x = second_cursor.x;
          first_cursor.y = second_cursor.y;

          player.set_destination_point(second_cursor.x,second_cursor.y);

          player.pausing = false;

          second_cursor.show = false;
        }
    }
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


  player.render(sprite_image,dst);

  sprite_image.transfer(24*3,0,24,32,dst,first_cursor.x,first_cursor.y);

    if(second_cursor.show)
    {
      sprite_image.transfer(24*4,0,24,32,dst,second_cursor.x,second_cursor.y);
    }


  auto  x = current_cursor->x+16;
  auto  y = current_cursor->y- 8;

  sprite_image.transfer(24*5,0,24,32,dst,x,y);
}




}}




