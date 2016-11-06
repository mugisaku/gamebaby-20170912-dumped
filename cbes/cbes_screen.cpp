#include"cbes_screen.hpp"
#include<cstring>
#include"fcfont.hpp"




namespace cbes{



namespace{
uint32_t
color_table[4];
}




Screen::
Screen():
window(nullptr),
surface(nullptr),
refresh_flag(true)
{
}




void
Screen::
open(int  w, int  h)
{
  window = SDL_CreateWindow("GAME BABY - " __DATE__,SDL_WINDOWPOS_CENTERED,
                                                    SDL_WINDOWPOS_CENTERED,
                                                    8*w*2,
                                                    8*h*2,0);

  table.resize(w,h);

  surface = SDL_GetWindowSurface(window);

  color_table[0] = SDL_MapRGB(surface->format,0x00,0x00,0xFF);
  color_table[1] = SDL_MapRGB(surface->format,0xFF,0xFF,0xFF);
  color_table[2] = SDL_MapRGB(surface->format,0x7F,0x7F,0x7F);
  color_table[3] = SDL_MapRGB(surface->format,0x00,0x00,0x00);
}


void
Screen::
close()
{
    if(window)
    {
      SDL_DestroyWindow(window);

      window  = nullptr;
      surface = nullptr;
    }
}


void
Screen::
change(Object*  obj, int  x, int  y)
{
  object = obj;

  obj->change_point(x,y);
}


void
Screen::
update()
{
    if(refresh_flag)
    {
      table.fill();

      object->render(table);

      transfer();

      refresh_flag = false;
    }
}


namespace{
void
draw_data(const uint16_t*  src, uint8_t*  dst, int  pitch)
{
    for(int  y = 0;  y < 8;  y += 1)
    {
      auto  p = reinterpret_cast<uint32_t*>(dst)          ;
                                            dst += pitch*2;

      auto  data = *src++;

        for(int  x = 0;  x < 8;  x += 1)
        {
          auto  v = color_table[(data>>14)&3];

          *(p        ) = v;
          *(p+1      ) = v;


          auto  p2 = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(p)+pitch);

          *(p2  ) = v;
          *(p2+1) = v;

          p     += 2;
          data <<= 2;
        }
    }
}
}


void
Screen::
transfer()
{
  std::memset(surface->pixels,0,surface->pitch*surface->h);

  auto  dst_line_ptr = static_cast<uint8_t*>(surface->pixels);

    for(int  y = 0;  y < table.get_height();  y += 1)
    {
      auto  c = &table.get_character(0,y);

      auto  dst = reinterpret_cast<uint32_t*>(dst_line_ptr)                   ;
                                              dst_line_ptr += 8*2*surface->pitch;

        for(int  x = 0;  x < table.get_width();  x += 1)
        {
          auto  g = fcfont::Character::pointer_table[c++->unicode];

            if(g)
            {
              draw_data(g->data,reinterpret_cast<uint8_t*>(dst),surface->pitch);
            }


          dst += 8*2;
        }
    }


  SDL_UpdateWindowSurface(window);
}


void
Screen::
need_to_refresh()
{
  refresh_flag = true;
}




Screen
screen;


}




