#include"gmbb_textmanager.hpp"
#include"gmbb_environment.hpp"
#include<cctype>




namespace gmbb{


TextManager::
TextManager(int  column_number, int  row_number):
text(column_number,row_number),
fast_flag(0),
scroll_count(0),
scroll_key(0),
finished_flag(1),
character_iterator(character_buffer),
character_end(character_buffer),
last_update_time(0)
{
  rectangle.reset(0,0,font::base_size*column_number,
                      font::tall_size*row_number);
}




namespace{
char16_t*
copy(const char16_t*  src, char16_t*  dst, const char16_t*  const dst_end)
{
    if(dst == dst_end)
    {
      return dst;
    }


    while(dst < dst_end)
    {
      auto  c = *src++;

        if(!c)
        {
          break;
        }


      *dst++ = c;
    }


  *dst = 0;

  return dst;
}


int
sscan_id(const char16_t*  s, char16_t*  buf, size_t  n)
{
  int  r = 0;

    if(!n)
    {
      return 0;
    }


    if(n == 1)
    {
      *buf = 0;

      return 0;
    }


  auto  c = *s++;

    if(isalpha(c) || (c == '_'))
    {
      *buf++ = c;

      --n;
      ++r;

        for(;;)
        {
            if(n == 1)
            {
              break;
            }


          c = *s++;

            if(isalnum(c) || (c == '_'))
            {
              *buf++ = c;

              --n;
              ++r;
            }

          else
            {
              break;
            }
        }
    }


  *buf = 0;

  return r;
}
}




void
TextManager::
clear()
{
  text.clear();

  scroll_count  = 0;
  scroll_key    = 0;
  fast_flag     = 0;
  finished_flag = 1;

  character_iterator = character_buffer;
  character_end      = character_buffer;
}


bool
TextManager::
is_finished() const
{
  return finished_flag;
}


void
TextManager::
push(const char16_t*  src)
{
    if(finished_flag)
    {
      clear();

      finished_flag = 0;
    }


    while(character_end < std::end(character_buffer))
    {
      auto  c = *src++;

        if(c == '$')
        {
          char16_t  tmpbuf[256];

          auto  n = sscan_id(src,tmpbuf,256);

            if(!n)
            {
              printf("環境変数をを指す識別子が不正です\n");

              throw;
            }


          src += n;

          character_end = copy(env::get_value(tmpbuf).data(),character_end,std::end(character_buffer));
        }

      else
        if(!c)
        {
          break;
        }

      else
        {
          *character_end++ = c;
        }
    }


  *character_end = 0;
}


void
TextManager::
push(std::initializer_list<const char16_t*>  ls)
{
    for(auto  s: ls)
    {
        if((character_end > std::begin(character_buffer)) &&
           (character_end < std::end(  character_buffer)))
        {
          *character_end++ = '\n';
        }


      push(s);
    }
}


void
TextManager::
controll(const Controller&  ctrl)
{
    if(ctrl.test_pressed(p_flag))
    {
        if((character_iterator == character_end) && !scroll_count)
        {
          finished_flag = 1;

          return;
        }
    }


    if(ctrl.test_pressing(p_flag))
    {
      fast_flag = 1;

        if((character_iterator != character_end))
        {
            if(scroll_key)
            {
              scroll_count = rectangle.h/2;

              scroll_key = 0;
            }
        }
    }

  else
    {
      fast_flag = 0;
    }
}


void
TextManager::
update()
{
    if(character_iterator == character_end)
    {
      return;
    }


  constexpr uint32_t  interval_time_base = 80;

  auto  now = env::get_time();

  auto  interval_time = interval_time_base;

    if(fast_flag)
    {
      interval_time /= 3;
    }


    if(now > (last_update_time+interval_time))
    {
      last_update_time = now;

        if(!text.is_full())
        {
          text.push(*character_iterator++);
        }

      else
        if(scroll_count)
        {
          text.rotate();

          scroll_count -= 1;
        }

      else
        {
          scroll_key = 1;
        }
    }
}


void
TextManager::
render(Image&  dst)
{
  text.render(dst,rectangle.x,rectangle.y);
}




}




