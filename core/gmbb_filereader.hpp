#ifndef GMBB_FILEREADER_HPP
#define GMBB_FILEREADER_HPP


#include<cstddef>


namespace gmbb{


class
FileReader
{
  const char*  const set;
  const char*  const end;
  const char*    current;

public:
  FileReader(const char*  p, size_t  length);

  void  rewind();

  void  advance(size_t  n);

  int  get();
  int  get_be16();
  int  get_be32();

  bool  eof() const;

};


}




#endif




