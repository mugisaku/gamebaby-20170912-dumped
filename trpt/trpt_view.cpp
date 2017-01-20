#include"trpt_view.hpp"
#include"trpt_board.hpp"
#include"trpt_facility.hpp"




namespace gmbb{
namespace trpt{


Image  View::sprite_image;


View::
View(Board*  brd):
board(nullptr),
width(0),
height(0)
{
    if(brd)
    {
      change_board(*brd);
    }
}




void
View::
change_width(int  v)
{
  width = std::min(v,24*board->get_width());

  offset_max.x = (24*board->get_width())-width;
}


void
View::
change_height(int  v)
{
  height = std::min(v,24*board->get_height());

  offset_max.y = (24*board->get_height())-height;
}


void
View::
change_board(Board&  brd)
{
  board = &brd;

  board_image.resize(24*brd.get_width(),24*brd.get_height());

  brd.render(board_image);
}


void
View::
process(Controller&  ctrl)
{
    if(ctrl.test_pressing(   up_flag) && cursor_point.y){--cursor_point.y;}
    if(ctrl.test_pressing( left_flag) && cursor_point.x){--cursor_point.x;}
    if(ctrl.test_pressing(right_flag) && (cursor_point.x <  width-1)){++cursor_point.x;}
    if(ctrl.test_pressing( down_flag) && (cursor_point.y < height-1)){++cursor_point.y;}

  board->process(ctrl,offset.x+cursor_point.x,
                      offset.y+cursor_point.y);
}


void
View::
move_window_point()
{
  auto  c = board->get_current_cursor();

    if(c)
    {
      auto  cx = c->x;
      auto  cy = c->y;

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
View::
draw_windows(Image&  dst) const
{
  constexpr int  square_w = font::base_size*10;
  constexpr int  square_h = font::tall_size*3;

  auto  sq = board->get_current_square();

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

          constexpr int  w = font::base_size*8;
          constexpr int  h = font::tall_size*2;

          dst.frame(x,y,w,h);

          f->draw_comment(dst,x+font::base_size,
                              y+font::base_size);
        }
    }
}


void
View::
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

  auto&  cur1 = board->get_first_cursor();
  auto&  cur2 = board->get_second_cursor();

  sprite_image.transfer(24*3,0,24,32,dst,cur1.x,cur1.y);

    if(cur2.show)
    {
      sprite_image.transfer(24*4,0,24,32,dst,cur2.x,cur2.y);
    }


  auto  x = cursor_point.x+16;
  auto  y = cursor_point.y- 8;

  sprite_image.transfer(24*5,0,24,32,dst,x,y);
}




}}




