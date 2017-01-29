#include"gmbb.hpp"
#include"trpt/trpt.hpp"
#include<SDL.h>
#include<cstdlib>




#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif


using namespace gmbb;
using namespace trpt;


namespace screen{
constexpr int   width = 320;
constexpr int  height = 280;
}


SDL_Window*    window;
SDL_Surface*  surface;


uint32_t
color_table[16];


Controller
ctrl;


Master  m;


Image
final_image(screen::width,screen::height);


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

  const int  w     = screen::width;
  const int  h     = screen::height;
  const int  pitch = surface->pitch;
  const int  bps   = surface->format->BytesPerPixel;

  SDL_LockSurface(surface);

    for(int  y = 0;  y < h;  y += 1)
    {
      auto  ptr = base_ptr           ;
                  base_ptr += pitch*2;

        for(int  x = 0;  x < w;  x += 1)
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
              }
          }
          break;
      case(SDL_WINDOWEVENT):
             switch(evt.window.event)
             {
           case(SDL_WINDOWEVENT_EXPOSED):
               break;
             }
           break;
      case(SDL_QUIT):
           quit();
           break;
        }
    }


  env::change_time(SDL_GetTicks());

  m.process(ctrl);

  static uint32_t  next_time;

  auto  now = SDL_GetTicks();

    if(now >= next_time)
    {
      constexpr uint32_t  interval_time = 40;

      m.step();

      m.move_window_point();

      m.render(final_image);

      transfer();

      next_time = now+interval_time;
    }


  ctrl.clean();
}




int
main(int  argc, char**  argv)
{
  Media  media("data.bin");

  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("GAME BABY - " __DATE__,SDL_WINDOWPOS_CENTERED,
                                                    SDL_WINDOWPOS_CENTERED,
                                                    screen::width*2,
                                                    screen::height*2,0);

  surface = SDL_GetWindowSurface(window);

    for(int  i = 0;  i < 8;  i += 1)
    {
      uint8_t  l = (i<<5)|0x1F;

      color_table[  i] = SDL_MapRGB(surface->format,l,l,l);
      color_table[8+i] = SDL_MapRGB(surface->format,l,l,l);
    }


  auto  r = media.find("data/man.mgf")->reader();

  PieceManager::sprite_image.load_mgf(r);

  r = media.find("data/map.mgf")->reader();

  Board::bg_image.load_mgf(r);


  m.load(media.find("data/map.qbf"));

  m.change_width( screen::width );
  m.change_height(screen::height);

  m.set_stage();

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




