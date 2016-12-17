#include"gmbb_file.hpp"
#include<cstdio>
#include<zlib.h>




namespace gmbb{




File::
File()
{
}


File::
File(std::string&&  name_, std::string&&  content_):
name(std::move(name_)),
content(std::move(content_))
{
}


File::
File(FileReader&  r)
{
  auto  len = r.get_be32();

  name.resize(len);

  auto  it = name.begin();

    while(len--)
    {
      *it++ = r.get();
    }


  len = r.get_be32();

  content.resize(len);

  it = content.begin();

    while(len--)
    {
      *it++ = r.get();
    }
}




const std::string*
File::
operator->() const
{
  return &content;
}


void
File::
change_name(std::string&&  new_name)
{
  name = std::move(new_name);
}


const std::string&  File::get_name() const{return name;}
const std::string&  File::get_content() const{return content;}


FileReader
File::
reader() const
{
  return FileReader(content.data(),content.size());
}


std::string
File::
get_content_from(const char*  path, bool  use_zlib)
{
  std::string  s;

    if(use_zlib)
    {
      auto  gz = gzopen(path,"rb");

        if(gz)
        {
            for(;;)
            {
              auto  c = gzgetc(gz);

                if(gzeof(gz))
                {
                  break;
                }


              s.push_back(c);
            }


          gzclose(gz);
        }
    }

  else
    {
      auto  f = fopen(path,"rb");

        if(f)
        {
            for(;;)
            {
              auto  c = fgetc(f);

                if(feof(f))
                {
                  break;
                }


              s.push_back(c);
            }


          fclose(f);
        }
    }


  return std::move(s);
}


void
File::
put_content_to(const char*  path, const std::string&  content, bool  use_zlib)
{
    if(use_zlib)
    {
      auto  gz = gzopen(path,"wb");

        if(gz)
        {
            for(auto  c: content)
            {
              gzputc(gz,c);
            }


          gzclose(gz);
        }
    }

  else
    {
      auto  f = fopen(path,"wb");

        if(f)
        {
            for(auto  c: content)
            {
              fputc(c,f);
            }


          fclose(f);
        }
    }
}


}




