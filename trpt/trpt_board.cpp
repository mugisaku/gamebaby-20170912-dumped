#include"trpt_board.hpp"
#include"trpt_porter.hpp"




namespace gmbb{
namespace trpt{


Image  Board::bg_image;



Board::
Board(int  w, int  h):
width(w),
height(h)
{
  square_table.resize(w*h);
}




int  Board::get_width() const{return width;}
int  Board::get_height() const{return height;}


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




