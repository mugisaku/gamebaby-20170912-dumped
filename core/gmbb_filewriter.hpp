#ifndef GMBB_FILEWRITER_HPP
#define GMBB_FILEWRITER_HPP


#include"gmbb_file.hpp"


namespace gmbb{


class
FileWriter: public File
{
  size_t  offset;

public:
  FileWriter();


  void  put(int  c);
  void  put_be16(int  c);
  void  put_be32(int  c);

  void  put_file(const File&  f);

};


}




#endif




