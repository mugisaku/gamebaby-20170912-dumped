#include"rpg_core__private.hpp"




namespace gmbb{
namespace rpg{


namespace core{


Image         bg_image;
Image  character_image;


Media  media("data.bin");


SquareMap
map;


Player  player;


Garden  gard0;
Garden  gard1;
Garden  gard2;


Message  message(30,6);


File*
load_file(const char*  path)
{
#ifdef EMSCRIPTEN
  return media.find(path);
#else
  static File  f;

  f = File(std::string(),File::get_content_from(path));

  return &f;
#endif
}


}}}




