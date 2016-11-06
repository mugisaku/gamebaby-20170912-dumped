#ifndef FCFONT_HPP_INCLUDED
#define FCFONT_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>


namespace fcfont{


struct
Character
{
  static constexpr int  size = 8;

  char16_t  unicode;

  uint16_t  data[size];

  static Character*  embedded_table;

  static int  embedded_number;

  static Character*  pointer_table[0x10000];

  static void  reset_table();
  static void  print_table(FILE*  f=stdout);
  static void  print_table2(FILE*  f=stdout);

};


struct
Combined
{
  char16_t  unicode;

  char16_t  upper;
  char16_t  lower;


  static Combined*  embedded_table;

  static int  embedded_number;

  static Combined*  pointer_table[0x10000];

  static void  reset_table();
  static void  print_table(FILE*  f=stdout);

};


void  encode(char16_t  c, char*  buf);


}


#endif




