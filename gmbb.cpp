#include"gmbb.hpp"
#include"game_xx.hpp"
#include"game_routine.hpp"
#include"gmbb_controller.hpp"
#include"game_environment.hpp"
#include"cbes_screen.hpp"
#include"fcfont.hpp"
#include<SDL.h>
#include<cstdlib>




#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif




std::vector<Tag*>
belongings_list;


void
erase_belongings(const Item*  item)
{
    for(auto&  blng: belongings_list)
    {
        if(blng == item);
        {
          blng = nullptr;

          break;
        }
    }
}


CommandPillar
commandpillar;


TagTable
tagtable;


Message
message(22,5);


cbes::Window  pillar_window( 8,14);
cbes::Window  table_window( 26,12);


cbes::Container
container;


Controller
ctrl;


uint32_t
current_time;


uint32_t
get_time()
{
  return current_time;
}




void
quit()
{
  cbes::screen.close();

  SDL_Quit();

  std::exit(0);
}


void
main_loop()
{
  static SDL_Event  evt;

    while(SDL_PollEvent(&evt))
    {
        switch(evt.type)
        {
      case(SDL_KEYDOWN):
          if(!evt.key.repeat)
          {
              switch(evt.key.keysym.sym)
              {
            case(SDLK_UP   ): ctrl.press(keyflag::up   );break;
            case(SDLK_LEFT ): ctrl.press(keyflag::left );break;
            case(SDLK_RIGHT): ctrl.press(keyflag::right);break;
            case(SDLK_DOWN ): ctrl.press(keyflag::down );break;

            case(SDLK_RETURN):
            case(SDLK_z     ):
                ctrl.press(keyflag::p);
                break;
            case(SDLK_RCTRL):
            case(SDLK_LCTRL):
            case(SDLK_x    ):
                ctrl.press(keyflag::n);
                break;
              }
          }
          break;
      case(SDL_KEYUP):
          if(!evt.key.repeat)
          {
              switch(evt.key.keysym.sym)
              {
            case(SDLK_UP   ): ctrl.unpress(keyflag::up   );break;
            case(SDLK_LEFT ): ctrl.unpress(keyflag::left );break;
            case(SDLK_RIGHT): ctrl.unpress(keyflag::right);break;
            case(SDLK_DOWN ): ctrl.unpress(keyflag::down );break;

            case(SDLK_RETURN):
            case(SDLK_z     ):
                ctrl.unpress(keyflag::p);
                break;
            case(SDLK_RCTRL):
            case(SDLK_LCTRL):
            case(SDLK_x    ):
                ctrl.unpress(keyflag::n);
                break;
              }
          }
          break;
      case(SDL_WINDOWEVENT):
             switch(evt.window.event)
             {
           case(SDL_WINDOWEVENT_EXPOSED):
               cbes::screen.need_to_refresh();
               break;
             }
           break;
      case(SDL_QUIT):
           quit();
           break;
        }
    }


  current_time = SDL_GetTicks();

    if(!step())
    {
      quit();
    }


  container.update();


  auto  curobj = get_current_object();

    if(curobj)
    {
      curobj->process(ctrl);
    }


  cbes::screen.update();

  ctrl.clean();
}




int
main(int  argc, char**  argv)
{
  cbes::screen.change(&container,0,0);

  container.join(&pillar_window,19, 1);
  container.join(&table_window,  1,15);

  pillar_window.change_content(&commandpillar,1,1);

  fcfont::Character::reset_table();
  fcfont::Combined::reset_table();

  SDL_Init(SDL_INIT_VIDEO);

  cbes::screen.open(28,28);

  push_routine(newgame);


#ifdef EMSCRIPTEN
  emscripten_set_main_loop(main_loop,-1,false);
#else
    for(;;)
    {
      main_loop();

      SDL_Delay(10);
    }
#endif


  return 0;
}




