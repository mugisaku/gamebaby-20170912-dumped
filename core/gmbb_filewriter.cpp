#include"gmbb_filewriter.hpp"
#include<cstdio>




namespace gmbb{




FileWriter::
FileWriter()
{
}




void
FileWriter::
put(int  c)
{
    if(offset < content.size())
    {
      content[offset++] = c;
    }
}


void
FileWriter::
put_be16(int  c)
{
  put(c>>8);
  put(c   );
}


void
FileWriter::
put_be32(int  c)
{
  put(c>>24);
  put(c>>16);
  put(c>> 8);
  put(c    );
}


void
FileWriter::
put_file(const File&  f)
{
  put_be32(f.get_name().size());

    for(auto  c: f.get_name())
    {
      put(c);
    }


  put_be32(f->size());

    for(auto  c: f.get_content())
    {
      put(c);
    }
}


}




