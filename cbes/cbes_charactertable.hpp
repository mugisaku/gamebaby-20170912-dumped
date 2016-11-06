#ifndef CBES_CHARACTERTABLE_HPP
#define CBES_CHARACTERTABLE_HPP


#include<string>
#include<cstdint>
#include"cbes_rectangle.hpp"


namespace cbes{


struct
Character
{
  uint16_t  attribute;

  char16_t  unicode;

};


class
CharacterTable
{
  int  width;
  int  height;

  Character*  data;

public:
   CharacterTable();
   CharacterTable(int  w, int  h);
   CharacterTable(const CharacterTable&   rhs);
   CharacterTable(      CharacterTable&&  rhs) noexcept;
  ~CharacterTable();

  CharacterTable&  operator=(const CharacterTable&   rhs);
  CharacterTable&  operator=(      CharacterTable&&  rhs) noexcept;

  void  fill();
  void  fill(char16_t  c, int  x, int  y, int  w,int  h);

  void  resize(int  w, int  h);

  Character&  get_character(int  x, int  y) const;

  int  get_width()  const;
  int  get_height() const;

  void  print_base(const char16_t*  text, int  x, int  y);
  void  print_tall(const char16_t*  text, int  x, int  y);
  void  printf_base(int  x, int  y, const char*  fmt, ...);
  void  printf_tall(int  x, int  y, const char*  fmt, ...);

  void  transfer(                            CharacterTable&  dst, int  x, int  y) const;
  void  transfer(const Rectangle&  src_rect, CharacterTable&  dst, int  x, int  y) const;

};


}




#endif




