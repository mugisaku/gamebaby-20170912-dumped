#include"gmbb_message.hpp"
#include"gmbb_environment.hpp"
#include"gmbb_window.hpp"
#include<cctype>




namespace gmbb{


Message::
Message(int  w, int  h):
page(w,h),
fast_flag(0),
scroll_count(0),
scroll_key(0),
finished_flag(1),
character_iterator(character_buffer),
character_end(character_buffer),
last_update_time(0)
{
  change_width( gmbb::font::base_size*w);
  change_height(gmbb::font::tall_size*h);
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
Message::
clear()
{
  page.clear();

  scroll_count  = 0;
  scroll_key    = 0;
  fast_flag     = 0;
  finished_flag = 1;

  character_iterator = character_buffer;
  character_end      = character_buffer;
}


bool
Message::
is_finished() const
{
  return finished_flag;
}


void
Message::
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
Message::
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
Message::
process(Controller&  ctrl)
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
              scroll_count = height/2;

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
Message::
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

        if(!page.is_full())
        {
          page.push(*character_iterator++);
        }

      else
        if(scroll_count)
        {
          page.rotate();

          scroll_count -= 1;
        }

      else
        {
          scroll_key = 1;
        }
    }
}


void
Message::
render(Image&  dst)
{
  auto  pt = get_absolute_point();

  page.render(dst,pt.x,pt.y);
}




}




