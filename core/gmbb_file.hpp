#ifndef GMBB_FILE_HPP
#define GMBB_FILE_HPP


#include<string>
#include"gmbb_filereader.hpp"


namespace gmbb{


class
File
{
protected:
  std::string  name;

  std::string  content;

public:
  File();
  File(std::string&&  name_, std::string&&  content_);
  File(FileReader&  r);


  const std::string*  operator->() const;

  void  change_name(std::string&&  new_name);

  const std::string&  get_name() const;
  const std::string&  get_content() const;

  FileReader  reader() const;

  static std::string  get_content_from(const char*  path);
  static void  put_content_to(const char*  path, const std::string&  content);

};


}




#endif




