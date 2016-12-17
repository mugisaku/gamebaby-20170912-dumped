#include"rpg_core__private.hpp"




namespace gmbb{
namespace rpg{


namespace core{


namespace{


const Scene*  current_scene;


uint32_t  flags;

bool  message_display_flag;

Window  message_window(8*30,16*6);


}




bool
set_flag(Section  section, uint32_t  v)
{
    if(!test_flag(section,v))
    {
      flags |=  v;

      return true;
    }


  return false;
}


void  unset_flag(Section  section, uint32_t  v){flags &= ~v;}
bool   test_flag(Section  section, uint32_t  v){return flags&v;}


const SquareMap&  get_squaremap(){return map;}
const Event&  get_event(int  i){return current_scene->event_table[i];}


Counter
display_message(Context&  ctx)
{
  message_display_flag = 1;

  return 0;
}


void
change_scene(const Scene&  scn)
{
  current_scene = &scn;

  flags = 0;
}


void
reset()
{
  message_window.change_point(8*3,8*2);

  message_window.change_content(&message);


  load_character_image(load_file("data/chr.png"));
  load_bg_image(load_file("data/bg.png"));

  map.load(load_file("data/living.qbf"));

  map.change_source(bg_image);

  player.get_sprite().reset(&character_image,0,0,24,32);

  player.change_play(basic_play);
  player.change_shapeshift(basic_shapeshift);

  player.standby(map,Direction::front,Direction::front,7,7);

  current_scene = &living_scene;

  player.change_interval_time(40);

  gard1.join(player.get_sprite());
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

    if(message_display_flag)
    {
      message_window.process(ctrl);
      message_window.update();

        if(message.is_finished())
        {
          message_display_flag = 0;
        }
    }

  else
    {
      player(ctrl);
    }

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

          auto  attr = map.get(pt.x,pt.y).attribute;

          dst.print(fmt("attrib: %sent %2d",attr&noentry_flag? "no":"",attr&0x7F),0|8,0,8);
          dst.print(fmt("X:%2d",pt.x),0|8,0,16);
          dst.print(fmt("Y:%2d",pt.y),0|8,0,24);
        }
    }


    if(active_keystate&env::fn7_flag)
    {
      dst.print(u"DEBUG",0|8,0,0);
    }


    if(message_display_flag)
    {
      message_window.render(dst);
    }
}




void
load_character_image(const File*  f)
{
    if(f)
    {
      auto  r = f->reader();
 
      character_image.load(r);
    }
}


void
load_bg_image(const File*  f)
{
    if(f)
    {
      auto  r = f->reader();

      bg_image.load(r);
    }
}


}}}




