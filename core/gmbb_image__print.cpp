#include"gmbb_image.hpp"
#include"gmbb_font.hpp"
#include"gmbb_unicode.hpp"




namespace gmbb{




void
Image::
print(char16_t  c, uint8_t  color, int  x, int  y)
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
                  *dst = color;
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
print(const char*  s, uint8_t  color, int  x, int  y)
{
    while(*s)
    {
      auto  byte_number = utf8_byte_number(*s);

      auto  c = to_char32(s,byte_number);

      s += byte_number;

      print(static_cast<char16_t>(c),color,x,y);

      x += font::base_size;
    }
}




void
Image::
print(const char16_t*  s, uint8_t  color, int  x, int  y)
{
    while(*s)
    {
      print(*s++,color,x,y);

      x += font::base_size;
    }
}




void
Image::
print_tall(char16_t  c, uint8_t  color, int  x, int  y)
{
  auto  g = font::get_combined(c);

    if(g)
    {
      print(g->upper,color,x,y                );
      print(g->lower,color,x,y+font::base_size);
    }
}




void
Image::
print_tall(const char*  s, uint8_t  color, int  x, int  y)
{
    while(*s)
    {
      auto  byte_number = utf8_byte_number(*s);

      auto  c = to_char32(s,byte_number);

      s += byte_number;

      print_tall(static_cast<char16_t>(c),color,x,y);

      x += font::base_size;
    }
}




void
Image::
print_tall(const char16_t*  s, uint8_t  color, int  x, int  y)
{
    while(*s)
    {
      print_tall(*s++,color,x,y);

      x += font::base_size;
    }
}




void
Image::
print_large(char16_t  c, uint8_t  color, int  x, int  y)
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
                  *dst = color;
                }


               dst  += 1;
              code <<= 1;
            }
        }
    }
}


void
Image::
print_large(const char*  s, uint8_t  color, int  x, int  y)
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

      print_large(static_cast<char16_t>(c),color,x,y);

      x += 16;
    }
}


void
Image::
print_large(const char16_t*  s, uint8_t  color, int  x, int  y)
{
    while(*s)
    {
        if((x+16) >= width)
        {
          break;
        }


      print_large(*s++,color,x,y);

      x += 16;
    }
}


}





