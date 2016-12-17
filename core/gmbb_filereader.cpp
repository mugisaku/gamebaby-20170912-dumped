#include"gmbb_filereader.hpp"
#include<cstdio>




namespace gmbb{




FileReader::
FileReader(const char*  p, size_t  length):
set(p),
current(p),
end(p+length)
{
}




void
FileReader::
rewind()
{
  current = set;
}


void
FileReader::
advance(size_t  n)
{
  current += n;
}


int
FileReader::
get()
{
  unsigned char  v = *current++;

  return v;
}


int
FileReader::
get_be16()
{
  int  v = get()<<8;

  v |= get();

  return v;
}


int
FileReader::
get_be32()
{
  int  v = get()<<24;

  v |= get()<<16;
  v |= get()<< 8;
  v |= get()    ;

  return v;
}


bool
FileReader::
eof() const
{
  return(current < end);
}




}




