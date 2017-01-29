#include"trpt_facility.hpp"
#include"trpt_town.hpp"




namespace gmbb{
namespace trpt{


void
Facility::
draw_comment(Image&  dst, int  x, int  y) const
{
  Formatted  fmt;

    switch(kind)
    {
  case(FacilityKind::village):
      dst.print_tall(u"しょくりょうを",font_color,x,y);
      dst.print_tall(u"わけてもらえます",font_color,x,y+font::tall_size);
      break;
  case(FacilityKind::town):
        if(town->porter_list.empty())
        {
          dst.print_tall(u"だれもいません",font_color,x,y);
        }

      else
        {
          dst.print_tall(fmt("%2dにんが",town->porter_list.size()),
                         font_color,x,y);

          dst.print_tall(u"たいざいしています",
                         font_color,x,y+font::tall_size);
        }
      break;
  default:;
    }
}


}}




