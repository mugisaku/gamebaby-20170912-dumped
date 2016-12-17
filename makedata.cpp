#include"gmbb.hpp"




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

      media.append(FilePath(path));

      printf("append %s\n",path);
    }


  media.save("data.bin");

  return 0;
}




