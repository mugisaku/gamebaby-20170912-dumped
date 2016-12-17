#include"gmbb_media.hpp"
#include<cstdio>




namespace gmbb{




Media::
Media()
{
}


Media::
Media(const char*  path)
{
  load(path);
}




void
Media::
append(File&&  f)
{
  file_table.emplace_back(std::move(f));
}


const File*
Media::
find(const char*  filename) const
{
    for(auto&  f: file_table)
    {
        if(f.get_name() == filename)
        {
          return &f;
        }
    }


  return nullptr;
}




void
Media::
load(const char*  path)
{
  file_table.clear();

  File  container(std::string(),File::get_content_from(path));

    if(container->size())
    {
      auto  r = container.reader();

      auto  n = r.get_be32();

        while(n--)
        {
          file_table.emplace_back(r);

          auto&  bk = file_table.back();

          printf("\"%s\" %d bytes\n",bk.get_name().data(),bk->size());
        }
    }
}


void
Media::
save(const char*  path) const
{
  FileWriter  w;

  w.put_be32(file_table.size());

    for(auto&  f: file_table)
    {
      w.put_file(f);
    }


  File::put_content_to(path,w.get_content());
}


}




