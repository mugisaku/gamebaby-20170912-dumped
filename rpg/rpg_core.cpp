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

  player.point.x = 24*10;

  player.sprite.reset(&character_image,0,0,24,32);

  player.shapeshift = shapeshift;

  player.interval_time = 40;

  gard1.join(player.sprite);
}


void
step(Controller&  ctrl)
{
  player.step();

    if(player.action_q.empty())
    {
        if(ctrl.test_pressing(up_flag))
        {
          player.face = Face::back;

          player.push(move_up);
        }

      else
        if(ctrl.test_pressing(left_flag))
        {
          player.face = Face::left;

          player.push(move_left);
        }

      else
        if(ctrl.test_pressing(right_flag))
        {
          player.face = Face::right;

          player.push(move_right);
        }

      else
        if(ctrl.test_pressing(down_flag))
        {
          player.face = Face::front;

          player.push(move_down);
        }
    }
}


void
render(Image&  dst)
{
  dst.fill(1);

  gard0.render(dst);

  map.render_lower(dst);

  gard1.render(dst);

  map.render_upper(dst);

  gard2.render(dst);
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




