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
step()
{
}




int  Board::get_width() const{return width;}
int  Board::get_height() const{return height;}


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




