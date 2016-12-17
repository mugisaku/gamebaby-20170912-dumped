#include"gmbb.hpp"
#include<cstring>




using namespace gmbb;


int
main(int  argc, char**  argv)
{
  Media  media;

  argc -= 1;
  argv += 1;

    while(argc--)
    {
      auto  path = *argv++;

      File  f(path,File::get_content_from(path));

      auto  p = std::strchr(path,'.');

        if(p && (std::strncmp(p+1,"png",3) == 0))
        {
          char  buf[256];

          char*  dst = buf;

          const char*   src_it = path;
          const char*  src_end = p+1;

            while(src_it < src_end)
            {
              *dst++ = *src_it++;
            }


          *dst++ = 'm';
          *dst++ = 'g';
          *dst++ = 'f';
          *dst   = '\0';


          Image  img;

          auto  r = f.reader();

          img.load_png(r);

          FileWriter  w;

          img.save_mgf(w);

          w.change_name(buf);

          f = static_cast<File&&>(w);
        }


      media.append(std::move(f));

      auto  bk = media->back();

      printf("append %s %d bytes\n",bk.get_name().data(),bk->size());
    }


  media.save("data.bin");

  return 0;
}




