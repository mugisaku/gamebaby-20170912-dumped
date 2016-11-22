#ifndef GMBB_FONT_HPP_INCLUDED
#define GMBB_FONT_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>


namespace gmbb{
namespace font{


constexpr int  base_size = 8;
constexpr int  tall_size = base_size*2;


struct
Glyph
{
  char16_t  unicode;

  uint8_t  data[base_size];

};



const Glyph*  get_glyph(char16_t  c);

void  print_glyphs_all(FILE*  f=stdout);


struct
Combined
{
  char16_t  unicode;

  char16_t  upper;
  char16_t  lower;

};


const Combined*  get_combined(char16_t  c);

void  print_combineds_all(FILE*  f=stdout);


void  encode(char16_t  c, char*  buf);


}}


#endif




