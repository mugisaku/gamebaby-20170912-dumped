#include"gmbb_image.hpp"
#include"gmbb_font.hpp"




namespace gmbb{




namespace{
size_t
get_utf8_byte_number(const char*  s)
{
  const int  c = *(const unsigned char*)s;

       if(!(c>>7)          ){return 1;}
  else if( (c>>4) == 0b1110){return 3;}
  else if( (c>>5) == 0b110 ){return 2;}
  else if( (c>>6) == 0b10  ){return 1;}


  return 0;
}


char16_t
to_char16(const char*  s, size_t  byte_number)
{
    switch(byte_number)
    {
      case(1): return((s[0]             )                                    );break;
      case(2): return((s[0]&0b11111)<< 6)|((s[1]&0b111111)                   );break;
      case(3): return((s[0]&0b01111)<<12)|((s[1]&0b111111)<<6)|(s[2]&0b111111);break;
    }


  return 0;
}
}




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
                  *dst = 15;
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
      auto  byte_number = get_utf8_byte_number(s);

      auto  c = to_char16(s,byte_number);

      s += byte_number;

      print(c,color,x,y);

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
      auto  byte_number = get_utf8_byte_number(s);

      auto  c = to_char16(s,byte_number);

      s += byte_number;

      print_tall(c,color,x,y);

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




}





