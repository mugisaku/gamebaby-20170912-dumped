#include"trpt_master.hpp"
#include"trpt_board.hpp"
#include"trpt_porter.hpp"
#include"trpt_town.hpp"
#include"trpt_facility.hpp"




namespace gmbb{
namespace trpt{


namespace{
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
}


void
Master::
draw_porter(int  x, int  y, Image&  dst) const
{
  constexpr int  w = font::base_size*12;
  constexpr int  h = font::tall_size*4;

  auto  p = current_piece;

    if(p && p->porter)
    {
      auto&  po = *p->porter;

      dst.frame(x,y,w,h);

      x += font::base_size;
      y += font::base_size;

      dst.print_tall(po.name,font_color,x,y);

      y += font::tall_size;

      Formatted  fmt;

      dst.print(fmt("しょくりょう %2d",po.foods_amount),font_color,x,y);

      y += font::base_size;

      dst.print_tall(fmt("エネルギー %2d",po.energy.value),font_color,x,y);
    }
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


  draw_porter(window_point.x,window_point.y+square_h,dst);
}


void
Master::
draw_entrybook(Image&  dst) const
{
  int  left_x = font::base_size*2;
  int  left_y = font::base_size*4;
  int  left_w = font::base_size*12;

  int  right_x = left_x+left_w;
  int  right_y = left_y;
  int  right_w = font::base_size*14;

  dst.frame( left_x, left_y, left_w,font::tall_size*(1+entrybook.get_line_number()));
  dst.frame(right_x,right_y,right_w,font::tall_size*(1+entrybook.get_line_number()));

  int  x = left_x+(font::base_size*2);
  int  y = left_y+(font::base_size  );

  auto&  page = entrybook.pages[book_index.x];

  dst.print_tall(u'→',font_color,left_x+font::base_size,y+(font::tall_size*book_index.y));

    for(int  i = 0;  i < entrybook.get_line_number();  ++i)
    {
      auto&  item = page.items[i];

        if(item.valid)
        {
          dst.print_tall((*item.data)->name,font_color,x,y);
        }


      y += font::tall_size;
    }


  x = right_x+(font::base_size*2);
  y = right_y+(font::base_size  );

  auto&  i = entrybook[book_index];

    if(i)
    {
      auto&  p = *i;

      Formatted  fmt;

      dst.print_tall(fmt("たいりょく　　　%2d",(*p)->physical_fitness),font_color,x,y);
      dst.print_tall(fmt("せいしんりょく　%2d",(*p)->mental_fitness  ),font_color,x,y+font::tall_size*1);
      dst.print_tall(fmt("じょうねつ　　　%2d",(*p)->ardor           ),font_color,x,y+font::tall_size*2);
      dst.print_tall(fmt("みりょく　　　　%2d",(*p)->charm           ),font_color,x,y+font::tall_size*3);
      dst.print_tall(fmt("うん　　　　　　%2d",(*p)->luck            ),font_color,x,y+font::tall_size*4);
    }
}


}}




