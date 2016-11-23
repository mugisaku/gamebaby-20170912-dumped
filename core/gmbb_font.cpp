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


Glyph
glyph_table[] =
{
#include"characters.txt"
};


Combined
combined_table[] =
{
#include"combineds.txt"
};


const Glyph*        glyph_pointer_table[0x10000];
const Combined*  combined_pointer_table[0x10000];


struct
Initializer{Initializer()
{
    for(auto&  g:    glyph_table){   glyph_pointer_table[g.unicode] = &g;}
    for(auto&  c: combined_table){combined_pointer_table[c.unicode] = &c;}
}};


Initializer
init;


}




const Glyph*
get_glyph(char16_t  c)
{
	  return glyph_pointer_table[c];
}


const Combined*
get_combined(char16_t  c)
{
	  return combined_pointer_table[c];
}


void
print_glyphs_all(FILE*  f)
{
  fprintf(f,"//characters\n");

    for(auto  ptr: glyph_pointer_table)
    {
        if(!ptr)
        {
          continue;
        }


      auto&  c = *ptr;

        if(is_private_use_area(c.unicode))
        {
          fprintf(f,"{0x%04X,{",c.unicode);
        }

      else
        {
          char  buf[4];

          encode(c.unicode,buf);

          const char*  s = buf;

            switch(buf[0])
            {
          case('\\'): s = "\\\\";break;
          case('\''): s = "\\\'";break;
          case('\"'): s = "\\\"";break;
            }


          fprintf(f,"{u\'%s\',{",s);
        }


        for(int  i = 0;  i < base_size;  ++i)
        {
          fprintf(f,"0x%02X,",c.data[i]);
        }


      fprintf(f,"}},\n");
    }
}




void
print_combineds_all(FILE*  f)
{
  fprintf(f,"//combineds\n");

    for(auto  ptr: combined_pointer_table)
    {
        if(!ptr)
        {
          continue;
        }


      auto&  c = *ptr;

        if(is_private_use_area(c.unicode))
        {
          fprintf(f,"{0x%04X,",c.unicode);
        }

      else
        {
          char  buf[4];

          encode(c.unicode,buf);

          fprintf(f,"{u\'%s\',",buf);
        }


      fprintf(f,"0x%04X,0x%04X},\n",c.upper,c.lower);
    }
}




void
encode(char16_t  c, char*  buf)
{
    if(c <= 0x7F)
    {
      buf[0] = c;

      buf[1] = 0;
    }

  else
    if((c >= 0x0080) &&
       (c <= 0x07FF))
    {
      buf[0] = (0b11000000|(c>>6));
      buf[1] = (0b10000000|(c&0b111111));

      buf[2] = 0;
    }

  else
    if((c >= 0x0800) &&
       (c <= 0xFFFF))
    {
      buf[0] = (0b11100000|(c>>12));
      buf[1] = (0b10000000|((c>>6)&0b111111));
      buf[2] = (0b10000000|((c   )&0b111111));

      buf[3] = 0;
    }
}




}}




