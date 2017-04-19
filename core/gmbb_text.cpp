#include"gmbb_text.hpp"




namespace gmbb{


struct
Text::
Line
{
  std::u16string  string;

  Line*  next=nullptr;

};


Text::
Text(int  col_n, int  row_n):
column_number(col_n),
row_number(row_n)
{
    if(row_n > 0)
    {
      row_n -= 1;

      first = new Line;

      current = first;

        while(row_n--)
        {
          auto  line = new Line;

          current->next = line;

          current = line;
        }


      last = current        ;
             current = first;
    }
}




void
Text::
clear()
{
  auto  next = first;

   while(next)
   {
     next->string.clear();

     next = next->next;
   }


  current = first;
}


void
Text::
rotate()
{
  auto  old_first = first;

  first = old_first->next;

  last->next = old_first;

  last = old_first;

  last->next = nullptr;

  last->string.clear();


  current = last;
}


void
Text::
push(char16_t  c)
{
    if(!is_full())
    {
        if(c == '\n')
        {
          current = current->next;
        }

      else
        {
          current->string.push_back(c);

            if(current->string.size() >= (column_number-1))
            {
              current = current->next;
            }
        }
    }
}



bool
Text::
is_full() const
{
  return !current;
}


void
Text::
render(Image&  dst, int  x, int  y) const
{
  auto  next = first;

    while(next)
    {
      dst.print_tall(next->string.data(),gmbb::font_color,x,y);

      y += font::tall_size;

      next = next->next;
    }
}



}




