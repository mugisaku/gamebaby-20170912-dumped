#include"trpt_facility.hpp"




namespace gmbb{
namespace trpt{


void
Facility::
draw_comment(Image&  dst, int  x, int  y) const
{
    switch(kind)
    {
  case(FacilityKind::village):
      break;
  case(FacilityKind::town):
      dst.print_tall(u"",font_color,x+font::base_size,
                                    y+font::base_size);
      break;
    }
}


}}




