#include"rpg_core.hpp"
#include<SDL_image.h>




namespace gmbb{
namespace rpg{


namespace core{


namespace{


Image  source_image;


SquareMap
map;


bool
test_qbf(SDL_RWops*  rw)
{
  constexpr uint8_t
  signature[4] =
  {
    'Q','B','F',0
  };


  auto  offset = SDL_RWtell(rw);

    for(int  i = 0;  i < 4;  i += 1)
    {
      auto  c = SDL_ReadU8(rw);

        if(c != signature[i])
        {
          return false;
        }
    }


  return true;
}


}




const SquareMap&  get_squaremap(){return map;}


Image  bg0;
Image  bg1;


void
step(Controller&  ctrl)
{
}


void
render(Image&  dst)
{
  dst.fill(1);

  dst.compose(bg0);
  dst.compose(bg1);
}




void
load_bg_image(const char*  path)
{
  auto  bmp = IMG_Load(path);

    if(bmp)
    {
      auto  p = static_cast<uint8_t*>(bmp->pixels);

      source_image.load(p,bmp->w,bmp->h,bmp->pitch);

      SDL_FreeSurface(bmp);
    }
}


void
load_bg_map(const char*  path)
{
  auto  rw = SDL_RWFromFile(path,"rb");

    if(rw)
    {
        if(test_qbf(rw))
        {
          int  w = SDL_ReadU8(rw);
          int  h = SDL_ReadU8(rw);
          int  d = SDL_ReadU8(rw);

          map.table.resize(w*h);

            for(int  y = 0;  y < h;  y += 1){
            for(int  x = 0;  x < w;  x += 1){
              auto&  sq = map.get(x,y);

              sq.attribute = SDL_ReadU8(rw);

              sq.lower.x = SDL_ReadU8(rw);
              sq.lower.y = SDL_ReadU8(rw);
              sq.upper.x = SDL_ReadU8(rw);
              sq.upper.y = SDL_ReadU8(rw);
            }}
        }


      SDL_FreeRW(rw);
    }
}


}}}




