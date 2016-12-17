#ifndef GMBB_MEDIA_HPP
#define GMBB_MEDIA_HPP


#include"gmbb_file.hpp"
#include"gmbb_filewriter.hpp"
#include<vector>


namespace gmbb{


class
Media
{
  std::vector<File>  file_table;

public:
  Media();
  Media(const char*  path);


  const std::vector<File>*  operator->() const;

  void  append(File&&  f);

  const File*  find(const char*  filename) const;

  void  load(const char*  path);
  void  save(const char*  path) const;

};


}




#endif




