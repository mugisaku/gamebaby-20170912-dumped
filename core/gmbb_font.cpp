#include"gmbb_font.hpp"
#include"gmbb_unicode.hpp"




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
          UTF8Chunk  chk(c.unicode);

          const char*  s = chk.codes;

            switch(chk.codes[0])
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
          UTF8Chunk  chk(c.unicode);

          fprintf(f,"{u\'%s\',",chk.codes);
        }


      fprintf(f,"0x%04X,0x%04X},\n",c.upper,c.lower);
    }
}




}}




