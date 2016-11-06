#include"cbes_datenote.hpp"
#include"cbes_screen.hpp"
#include<cstdlib>




namespace cbes{


DateNote::
DateNote():
year(1),
month(1),
day(1)
{
}




void
DateNote::
update()
{
    if(day < 4)
    {
      ++day;
    }

  else
    {
      day = 1;

        if(month < 12)
        {
          ++month;
        }

      else
        {
          month = 1;

            if(year < 9999)
            {
              ++year;
            }

          else
            {
              year = 0;
            }
        }
    }


  screen.need_to_refresh();
}


void
DateNote::
render(CharacterTable&  dst)
{
  int  x = point.x;

  dst.printf_base(point.x,point.y,"%2d年%2d月%2d日",year,month,day);
}




}




