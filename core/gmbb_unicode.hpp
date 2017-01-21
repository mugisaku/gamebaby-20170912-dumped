#ifndef GMBB_UNICODE_HPP
#define GMBB_UNICODE_HPP


#include<string>
#include<cstdint>
#include<cstddef>


namespace gmbb{


struct not_utf8{};
struct not_utf32{};
struct invalid_utf8_byte_number{};


size_t  utf8_byte_number(unsigned char  c);


char32_t  to_char32(const char*  utf8, size_t  byte_number);


struct
UTF8Chunk
{
  char  codes[8];

  UTF8Chunk(char32_t  c=0);

  UTF8Chunk&  operator=(char32_t  c);

};


}




#endif




