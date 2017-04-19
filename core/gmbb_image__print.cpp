#include"gmbb_image.hpp"
#include"gmbb_font.hpp"
#include"gmbb_unicode.hpp"




namespace gmbb{




void
Image::
print(char16_t  c, color_table::Index  i, int  x, int  y)
{
  auto  g = font::get_glyph(c);

    if(g)
    {
      auto  src = g->data;

        for(int  yy = 0;  yy < font::base_size;  yy += 1)
        {
          auto   dst = &pixel(x,y++);
          auto  code = *src++;

            for(int  xx = 0;  xx < font::base_size;  xx += 1)
            {
                if(code&0x80)
                {
                  *dst = *i;
                }


               dst  += 1;
              code <<= 1;
            }
        }
    }
}




void
Image::
Image::
print(const char*  s, color_table::Index  i, int  x, int  y)
{
    while(*s)
    {
      auto  byte_number = utf8_byte_number(*s);

      auto  c = to_char32(s,byte_number);

      s += byte_number;

      print(static_cast<char16_t>(c),i,x,y);

      x += font::base_size;
    }
}




void
Image::
print(const char16_t*  s, color_table::Index  i, int  x, int  y)
{
    while(*s)
    {
      print(*s++,i,x,y);

      x += font::base_size;
    }
}




void
Image::
print_tall(char16_t  c, color_table::Index  i, int  x, int  y)
{
  auto  g = font::get_combined(c);

    if(g)
    {
      print(g->upper,i,x,y                );
      print(g->lower,i,x,y+font::base_size);
    }
}




void
Image::
print_tall(const char*  s, color_table::Index  i, int  x, int  y)
{
    while(*s)
    {
      auto  byte_number = utf8_byte_number(*s);

      auto  c = to_char32(s,byte_number);

      s += byte_number;

      print_tall(static_cast<char16_t>(c),i,x,y);

      x += font::base_size;
    }
}




void
Image::
print_tall(const char16_t*  s, color_table::Index  i, int  x, int  y)
{
    while(*s)
    {
      print_tall(*s++,i,x,y);

      x += font::base_size;
    }
}




void
Image::
print_large(char16_t  c, color_table::Index  i, int  x, int  y)
{
  auto  g = font::get_large_glyph(c);

    if(g)
    {
      auto  src = g->data;

      x += 2;
      y += 2;

        for(int  yy = 0;  yy < 14;  yy += 1)
        {
          auto   dst = &pixel(x,y++);
          auto  code = *src++;

            for(int  xx = 0;  xx < 14;  xx += 1)
            {
                if(code&0x8000)
                {
                  *dst = *i;
                }


               dst  += 1;
              code <<= 1;
            }
        }
    }
}


void
Image::
print_large(const char*  s, color_table::Index  i, int  x, int  y)
{
    while(*s)
    {
        if((x+16) >= width)
        {
          break;
        }


      auto  byte_number = utf8_byte_number(*s);

      auto  c = to_char32(s,byte_number);

      s += byte_number;

      print_large(static_cast<char16_t>(c),i,x,y);

      x += 16;
    }
}


void
Image::
print_large(const char16_t*  s, color_table::Index  i, int  x, int  y)
{
    while(*s)
    {
        if((x+16) >= width)
        {
          break;
        }


      print_large(*s++,i,x,y);

      x += 16;
    }
}


}





