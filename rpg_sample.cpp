#include"gmbb.hpp"
#include"rpg/rpg_core.hpp"
#include"rpg/rpg_player.hpp"
#include<SDL.h>
#include<cstdlib>




#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif


using namespace gmbb;


SDL_Window*    window;
SDL_Surface*  surface;


uint32_t
color_table[16];


Image
final_image(rpg::screen::width,rpg::screen::height);


Controller
ctrl;


template<typename  T>
void
write(uint8_t*&  ptr, int  pitch, uint32_t  v)
{
  auto  dst = reinterpret_cast<T*>(ptr);

  *dst++ = v;
  *dst   = v;


  dst = reinterpret_cast<T*>(ptr+pitch);

  *dst++ = v;
  *dst   = v;

  ptr += sizeof(T)*2;
}


void
transfer()
{
  auto  base_ptr = static_cast<uint8_t*>(surface->pixels);

  const uint8_t*  src = &final_image.const_pixel(0,0);

  const int  pitch = surface->pitch;
  const int  bps   = surface->format->BytesPerPixel;

  SDL_LockSurface(surface);

    for(int  y = 0;  y < rpg::screen::height;  y += 1)
    {
      auto  ptr = base_ptr           ;
                  base_ptr += pitch*2;

        for(int  x = 0;  x < rpg::screen::width;  x += 1)
        {
          auto  pixel = color_table[(*src++)&15];

            switch(bps)
            {
          case(1):
              write<uint8_t>(ptr,pitch,pixel);
              break;
          case(2):
              write<uint16_t>(ptr,pitch,pixel);
              break;
          case(4):
              write<uint32_t>(ptr,pitch,pixel);
              break;
          default:
              return;
            }
        }
    }


  SDL_UnlockSurface(surface);

  SDL_UpdateWindowSurface(window);
}




void
quit()
{
  SDL_DestroyWindow(window);

  SDL_Quit();

  std::exit(0);
}


void
load(char*  s)
{
  SDL_free(s);
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
            case(SDLK_UP   ): ctrl.press(up_flag   );break;
            case(SDLK_LEFT ): ctrl.press(left_flag );break;
            case(SDLK_RIGHT): ctrl.press(right_flag);break;
            case(SDLK_DOWN ): ctrl.press(down_flag );break;

            case(SDLK_RETURN):
            case(SDLK_z):
                ctrl.press(p_flag);
                break;
            case(SDLK_RCTRL):
            case(SDLK_LCTRL):
            case(SDLK_x    ):
                ctrl.press(n_flag);
                break;
            case(SDLK_F1): env::fn_keystate |= env::fn1_flag;break;
            case(SDLK_F2): env::fn_keystate |= env::fn2_flag;break;
            case(SDLK_F3): env::fn_keystate |= env::fn3_flag;break;
            case(SDLK_F4): env::fn_keystate |= env::fn4_flag;break;
            case(SDLK_F5): env::fn_keystate |= env::fn5_flag;break;
            case(SDLK_F6): env::fn_keystate |= env::fn6_flag;break;
            case(SDLK_F7): env::fn_keystate |= env::fn7_flag;break;
            case(SDLK_F8): env::fn_keystate |= env::fn8_flag;break;
                break;
              }
          }
          break;
      case(SDL_KEYUP):
          if(!evt.key.repeat)
          {
              switch(evt.key.keysym.sym)
              {
            case(SDLK_UP   ): ctrl.unpress(up_flag   );break;
            case(SDLK_LEFT ): ctrl.unpress(left_flag );break;
            case(SDLK_RIGHT): ctrl.unpress(right_flag);break;
            case(SDLK_DOWN ): ctrl.unpress(down_flag );break;

            case(SDLK_RETURN):
            case(SDLK_z     ):
                ctrl.unpress(p_flag);
                break;
            case(SDLK_RCTRL):
            case(SDLK_LCTRL):
            case(SDLK_x    ):
                ctrl.unpress(n_flag);
                break;
            case(SDLK_F1): env::fn_keystate &= ~env::fn1_flag;break;
            case(SDLK_F2): env::fn_keystate &= ~env::fn2_flag;break;
            case(SDLK_F3): env::fn_keystate &= ~env::fn3_flag;break;
            case(SDLK_F4): env::fn_keystate &= ~env::fn4_flag;break;
            case(SDLK_F5): env::fn_keystate &= ~env::fn5_flag;break;
            case(SDLK_F6): env::fn_keystate &= ~env::fn6_flag;break;
            case(SDLK_F7): env::fn_keystate &= ~env::fn7_flag;break;
            case(SDLK_F8): env::fn_keystate &= ~env::fn8_flag;break;
                break;
              }
          }
          break;
      case(SDL_WINDOWEVENT):
             switch(evt.window.event)
             {
           case(SDL_WINDOWEVENT_EXPOSED):
//               need_to_refresh();
               break;
             }
           break;
      case(SDL_DROPFILE):
           load(evt.drop.file);
           break;
      case(SDL_QUIT):
           quit();
           break;
        }
    }


  env::change_time(SDL_GetTicks());

  rpg::core::step(ctrl);

  static uint32_t  next_time;

  auto  now = SDL_GetTicks();

    if(now >= next_time)
    {
      constexpr uint32_t  interval_time = 40;

      rpg::core::render(final_image);

      transfer();

      next_time = now+interval_time;
    }


  ctrl.clean();
}




int
main(int  argc, char**  argv)
{
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("GAME BABY - " __DATE__,SDL_WINDOWPOS_CENTERED,
                                                    SDL_WINDOWPOS_CENTERED,
                                                    rpg::screen::width*2,
                                                    rpg::screen::height*2,0);

  surface = SDL_GetWindowSurface(window);

    for(int  i = 0;  i < 8;  i += 1)
    {
      uint8_t  l = (i<<5)|0x1F;

      color_table[  i] = SDL_MapRGB(surface->format,l,l,l);
      color_table[8+i] = SDL_MapRGB(surface->format,l,l,l);
    }


  rpg::core::reset();

#ifdef EMSCRIPTEN
  emscripten_set_main_loop(main_loop,-1,false);
#else
  SDL_Delay(40);

    for(;;)
    {
      main_loop();

      SDL_Delay(10);
    }
#endif


  return 0;
}




