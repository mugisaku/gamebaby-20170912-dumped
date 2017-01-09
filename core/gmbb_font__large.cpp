#include"gmbb_font.hpp"




namespace gmbb{
namespace font{




namespace{


constexpr bool
is_private_use_area(char16_t  c)
{
  return((c >= 0xE000) &&
         (c <= 0xF8FF));
}


LargeGlyph*
glyph_table[0x10000];


}




const LargeGlyph*
get_large_glyph(char16_t  c)
{
	  return glyph_table[c];
}


void
load_large_font(FileReader&  r)
{
  auto  n = r.get_be16();

    while(n--)
    {
      auto  unicode = r.get_be16();

      auto&  dst = glyph_table[unicode];

        if(!dst)
        {
          dst = new LargeGlyph;
        }


      dst->unicode = unicode;

        for(int  y = 0;  y < 14;  ++y)
        {
          dst->data[y] = r.get_be16();
        }
    }
}


}}




