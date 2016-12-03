#include"rpg_core.hpp"
#include"rpg_routine.hpp"
#include<SDL_image.h>




namespace gmbb{
namespace rpg{


namespace core{


namespace{


Image         bg_image;
Image  character_image;


SquareMap
map;


}




const SquareMap&  get_squaremap(){return map;}


Player  player;


Garden  gard0;
Garden  gard1;
Garden  gard2;


void
reset()
{
  load_character_image("chr.png");
  load_bg_image("bg.png");

  map.load("living.qbf");

  map.change_source(bg_image);

  player.sprite.reset(&character_image,0,0,24,32);

  player.shapeshift = shapeshift;

  player.interval_time = 40;

  gard1.join(player.sprite);
}


uint8_t   active_keystate = 0b11111000;
uint8_t  pressed_keystate;


bool
debugging()
{
  return active_keystate&env::fn7_flag;
}


void
step(Controller&  ctrl)
{
  active_keystate ^= pressed_keystate&~env::fn_keystate;

  pressed_keystate = env::fn_keystate;

  player.step();

  walk(player,ctrl);
}


void
render(Image&  dst)
{
  dst.fill(1);

    if(active_keystate&env::fn1_flag)
    {
      gard0.render(dst);
    }


    if(active_keystate&env::fn2_flag)
    {
      map.render_lower(dst);
    }


    if(active_keystate&env::fn3_flag)
    {
      gard1.render(dst);
    }


    if(active_keystate&env::fn4_flag)
    {
      map.render_upper(dst);
    }


    if(active_keystate&env::fn5_flag)
    {
      gard2.render(dst);
    }


    if(active_keystate&env::fn6_flag)
    {
      auto  pt = player.get_square_point();

        if((pt.x >= 0) && (pt.y >= 0))
        {
          int  x = 24*pt.x;
          int  y = 24*pt.y;

          dst.rectangle(4|8,x  ,y  ,24,24);
          dst.rectangle(0|8,x+1,y+1,22,22);


          Formatted  fmt;

          dst.print(fmt("attrib"),0|8,0,8);
          dst.print(fmt("X:%2d",pt.x),0|8,0,16);
          dst.print(fmt("Y:%2d",pt.y),0|8,0,24);
        }
    }


    if(active_keystate&env::fn7_flag)
    {
      dst.print(u"DEBUG",0|8,0,0);
    }
}




void
load_character_image(const char*  path)
{
  auto  bmp = IMG_Load(path);

    if(bmp)
    {
      auto  p = static_cast<uint8_t*>(bmp->pixels);

      character_image.load(p,bmp->w,bmp->h,bmp->pitch);

      SDL_FreeSurface(bmp);
    }
}


void
load_bg_image(const char*  path)
{
  auto  bmp = IMG_Load(path);

    if(bmp)
    {
      auto  p = static_cast<uint8_t*>(bmp->pixels);

      bg_image.load(p,bmp->w,bmp->h,bmp->pitch);

      SDL_FreeSurface(bmp);
    }
}


}}}




