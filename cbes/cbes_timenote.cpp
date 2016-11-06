#include"cbes_timenote.hpp"
#include"cbes_screen.hpp"
#include<cstdlib>




namespace cbes{


TimeNote::
TimeNote():
hour(0),
minute(0),
second(0)
{
}




void
TimeNote::
reset(int  h, int  m, int  s)
{
  hour   = h;
  minute = m;
  second = s;
}


void
TimeNote::
update()
{
    if(second < 59)
    {
      ++second;
    }

  else
    {
      second = 0;

        if(minute < 59)
        {
          ++minute;
        }

      else
        {
          minute = 0;

            if(hour < 24)
            {
              ++hour;
            }

          else
            {
              hour = 0;
            }
        }
    }


  screen.need_to_refresh();
}


void
TimeNote::
render(CharacterTable&  dst)
{
  int  x = point.x;

  dst.printf_tall(point.x,point.y,"じかん　%02d:%02d",hour,minute);
}




}




