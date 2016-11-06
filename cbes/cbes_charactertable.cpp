#include"cbes_charactertable.hpp"
#include"fcfont.hpp"
#include<cstring>
#include<cstdarg>




namespace cbes{



CharacterTable::
CharacterTable():
width(0),
height(0),
data(nullptr)
{
}


CharacterTable::
CharacterTable(int  w, int  h):
data(nullptr)
{
  resize(w,h);
}


CharacterTable::
CharacterTable(const CharacterTable&  rhs):
data(nullptr)
{
  *this = rhs;
}


CharacterTable::
CharacterTable(CharacterTable&&  rhs) noexcept:
data(nullptr)
{
  *this = std::move(rhs);
}


CharacterTable::
~CharacterTable()
{
  delete[] data;
}




CharacterTable&
CharacterTable::
operator=(const CharacterTable&   rhs)
{
  resize(rhs.width,rhs.height);

  rhs.transfer(*this,0,0);

  return *this;
}


CharacterTable&
CharacterTable::
operator=(CharacterTable&&  rhs) noexcept
{
  width  = rhs.width ;
  height = rhs.height;

  delete[] data                     ;
           data = rhs.data          ;
                  rhs.data = nullptr;

  return *this;
}




void
CharacterTable::
fill()
{
  std::memset(data,0,sizeof(Character)*width*height);
}


void
CharacterTable::
fill(char16_t  c, int  x, int  y, int  w,int  h)
{
    for(auto  yy = 0;  yy < h;  ++yy){
    for(auto  xx = 0;  xx < w;  ++xx){
      get_character(x+xx,y+yy).unicode = c;
    }}
}


void
CharacterTable::
resize(int  w, int  h)
{
  delete[] data                     ;
           data = new Character[w*h];

  width  = w;
  height = h;
}


Character&
CharacterTable::
get_character(int  x, int  y) const
{
  return data[(width*y)+x];
}


int  CharacterTable::get_width()  const{return width;}
int  CharacterTable::get_height() const{return height;}


void
CharacterTable::
print_base(const char16_t*  text, int  x, int  y)
{
    while(*text)
    {
      get_character(x++,y).unicode = *text++;
    }
}


void
CharacterTable::
print_tall(const char16_t*  text, int  x, int  y)
{
    while(*text)
    {
      auto  c = fcfont::Combined::pointer_table[*text++];

        if(c)
        {
          get_character(x  ,y  ).unicode = c->upper;
          get_character(x++,y+1).unicode = c->lower;
        }
    }
}


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
CharacterTable::
printf_base(int  x, int  y, const char*  fmt, ...)
{
  char  buf[80];

  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(buf,sizeof(buf),fmt,ap);

  va_end(ap);


  const char*  p = buf;

    while(*p)
    {
      auto  n = get_utf8_byte_number(p);

      get_character(x++,y).unicode = to_char16(p,n);

      p += n;
    }
}


void
CharacterTable::
printf_tall(int  x, int  y, const char*  fmt, ...)
{
  char  buf[80];

  va_list  ap;
  va_start(ap,fmt);

  vsnprintf(buf,sizeof(buf),fmt,ap);

  va_end(ap);


  const char*  p = buf;

    while(*p)
    {
      auto  n = get_utf8_byte_number(p);

      auto  c = fcfont::Combined::pointer_table[to_char16(p,n)];

      p += n;

        if(c)
        {
          get_character(x  ,y  ).unicode = c->upper;
          get_character(x++,y+1).unicode = c->lower;
        }
    }
}


void
CharacterTable::
transfer(CharacterTable&  dst, int  x, int  y) const
{
  Rectangle  rect(0,0,width,height);

  transfer(rect,dst,x,y);
}


void
CharacterTable::
transfer(const Rectangle&  src_rect, CharacterTable&  dst, int  x, int  y) const
{
    for(int  yy = 0;  yy < src_rect.height;  ++yy){
    for(int  xx = 0;  xx < src_rect.width ;  ++xx){
      dst.get_character(x+xx,y+yy) = get_character(src_rect.point.x+xx,src_rect.point.y+yy);
    }}
}


}




