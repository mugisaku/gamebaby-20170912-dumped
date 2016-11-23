#include"gmbb.hpp"
#include"ta/ta.hpp"
#include<SDL.h>
#include<SDL_image.h>
#include<cstdlib>




#ifdef EMSCRIPTEN
#include"emscripten.h"
#endif




SDL_Window*    window;
SDL_Surface*  surface;


uint32_t
color_table[16];


gmbb::Image   bg_img;
gmbb::Image  chr_img;


gmbb::Sprite  spr;


gmbb::Garden
garden;


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

  const uint8_t*  src = &gmbb::final_plain.const_pixel(0,0);

  const int  w     = gmbb::Plain::width;
  const int  h     = gmbb::Plain::height;
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

  IMG_Quit();
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
//               cbes::core::need_to_refresh();
               break;
             }
           break;
      case(SDL_QUIT):
           quit();
           break;
        }
    }


  gmbb::change_time(SDL_GetTicks());

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


  gmbb::final_plain.fill(0);

  container.render(gmbb::final_plain);

//  gmbb::compose_plains_all();

//  spr.process(ctrl);
  garden.render(gmbb::final_plain);

  transfer();

  ctrl.clean();
}




int
main(int  argc, char**  argv)
{
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG);

  window = SDL_CreateWindow("GAME BABY - " __DATE__,SDL_WINDOWPOS_CENTERED,
                                                    SDL_WINDOWPOS_CENTERED,
                                                    gmbb::Plain::width*2,
                                                    gmbb::Plain::height*2,0);

  surface = SDL_GetWindowSurface(window);

    for(int  i = 0;  i < 8;  i += 1)
    {
      uint8_t  l = (i<<5)|0x1F;

      color_table[  i] = SDL_MapRGB(surface->format,l,l,l);
      color_table[8+i] = SDL_MapRGB(surface->format,l,l,l);
    }


  auto  bmp = IMG_Load("bg.png");

  bg_img.load(bmp->w,bmp->h,static_cast<const uint8_t*>(bmp->pixels),bmp->pitch);

  SDL_FreeSurface(bmp)                     ;
                  bmp = IMG_Load("chr.png");

  chr_img.load(bmp->w,bmp->h,static_cast<const uint8_t*>(bmp->pixels),bmp->pitch);

  SDL_FreeSurface(bmp);


  spr.reset(&chr_img,0,0,24,32);

  garden.join(spr);

  container.join(&pillar_window,gmbb::font::base_size*19,gmbb::font::base_size* 1);
  container.join(&table_window, gmbb::font::base_size* 1,gmbb::font::base_size*15);

  pillar_window.change_content(&commandpillar);

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




